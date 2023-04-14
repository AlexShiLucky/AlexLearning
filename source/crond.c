/*
********************************************************************************
* crond.c
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include "common.h"

#include "clock.h"
#include "crond.h"

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/



/*
********************************************************************************
* Shared Types
********************************************************************************
*/



/*
********************************************************************************
* Private Types
********************************************************************************
*/

typedef struct _crond_priv {
    CPU_INT64U shutoff_active_nsecs;
} crond_priv_t;

/*
********************************************************************************
* Private Function Prototypes
********************************************************************************
*/



/*
********************************************************************************
* Shared Data
********************************************************************************
*/



/*
********************************************************************************
* Private Data
********************************************************************************
*/

static crond_priv_t g_crond_priv;

static crond_t  g_crond = {
    .priv = &g_crond_priv
};


/*
********************************************************************************
* Private Functions
********************************************************************************
*/


/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief
 *
 * @param
 *
 * @return
 *
 * @notes
 */



/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief
 *
 * @param
 *
 * @return
 *
 * @notes
 */
crond_t* crond_get(void)
{
    return &g_crond;
}

void crond_autopowerup_calc(crond_t *pcrond)
{
    sys_time_t *nt;
    crontab_t *pct;
    struct _tm *alarmt;
    struct _tm now;

    pct = &pcrond->powerup;
    nt = sys_time_get();
    if (nt->flags & (DEF_FLAGS_TIME_INIT|DEF_FLAGS_TIME_SYNC)) {
        time_to_tm(nt->sync_nsecs, (OSTimeGet()-nt->sync_ticks)/OS_TICKS_PER_SEC+CONFIG_CROND_DLY_SECS, &now);
        alarmt = crontab_search(pct, &now);
        if (alarmt) {
            LOG_Info("AutoPowerup RTCC setting.");
        }
    }
}

void crond_autoshutoff_calc(crond_t *pcrond)
{
    crond_priv_t *priv = (crond_priv_t *)pcrond->priv;
    sys_time_t *nt;
    struct _tm *alarmt;
    struct _tm now;
    CPU_INT64U nsecs;

    nt = sys_time_get();
    if (nt->flags & (DEF_FLAGS_TIME_INIT|DEF_FLAGS_TIME_SYNC)) {
        nsecs = (OSTimeGet()-nt->sync_ticks)/OS_TICKS_PER_SEC+CONFIG_CROND_DLY_SECS;
        time_to_tm(nt->sync_nsecs, nsecs, &now);
        alarmt = crontab_search(&pcrond->shutoff, &now);
        if (alarmt) {
            priv->shutoff_active_nsecs = sys_mktime((const simple_time_t *)alarmt);
            nsecs = nt->sync_nsecs + (OSTimeGet()-nt->sync_ticks)/OS_TICKS_PER_SEC;
            if (nsecs >= priv->shutoff_active_nsecs) {
                pcrond->awake_ticks = OS_TICKS_PER_SEC/4;
            } else {
                CPU_INT32U s;
                s = priv->shutoff_active_nsecs-nsecs;
                if (s >= 60) pcrond->awake_ticks = OS_TICKS_PER_MIN;
                else pcrond->awake_ticks = (CPU_INT16U)(s*OS_TICKS_PER_SEC);
            }
            pcrond->flags |= DEF_FLAGS_CROND_AUTOSHUTOFF_CHECK_ACTIVE;
            LOG_Info("Shutoff Base:%llus, Active:%llus", \
                nt->sync_nsecs, priv->shutoff_active_nsecs);
        } else {
            pcrond->awake_ticks = 0;
            pcrond->flags &= ~DEF_FLAGS_CROND_AUTOSHUTOFF_CHECK_ACTIVE;
        }
    } else {
        pcrond->awake_ticks = 0;
        pcrond->flags &= ~DEF_FLAGS_CROND_AUTOSHUTOFF_CHECK_ACTIVE;
    }
}

void crond_autoshutoff_check(crond_t *pcrond)
{
    crond_priv_t *priv;
    sys_time_t *nt;
    CPU_INT64U nsecs;
    struct _tm rtc;

    if (pcrond->flags&DEF_FLAGS_CROND_AUTOSHUTOFF_CHECK_ACTIVE) {
        if (!(pcrond->flags&DEF_FLAGS_CROND_AUTOSHUTOFF_ACTIVED)) {
            nt = sys_time_get();
            priv = (crond_priv_t *)pcrond->priv;
            nsecs = nt->sync_nsecs + (OSTimeGet()-nt->sync_ticks)/OS_TICKS_PER_SEC;
            if (nsecs >= priv->shutoff_active_nsecs) {
                if (1) {     // 如果USB断开连接,则通知时序自动关机
                    LOG_Print(CONFIG_LINE_ENDING);
                    if (sys_settime(nt, OSTimeGet()) == DEF_Success) {
                        sys_gettime(nt, &rtc);
                        LOG_Print(VTANSI_COLOR_LIGHT_YELLOW"[SHUTDOWN-Alarm!!!] Now:%u-%02u-%02u %s %02u:%02u:%02u"VTANSI_DISPLAY_RESET""CONFIG_LINE_ENDING, \
                                rtc.year+BASE_YEAR, rtc.mon+1, rtc.mday+1,     \
                                &wdays_str[rtc.wday*4], rtc.hour, rtc.min, rtc.sec);
                    }
                    DELIMITER_LINE();
                    LOG_Info("AlarmOFF active!!! Message Post.");
                    DELIMITER_LINE();
                    pcrond->awake_ticks = 0;
                    pcrond->flags |= DEF_FLAGS_CROND_AUTOSHUTOFF_ACTIVED;
                } else {    // 重新寻找最近时间
                    if (sys_settime(nt, OSTimeGet()) == DEF_Success) {
                        sys_gettime(nt, &rtc);
                        LOG_Print(VTANSI_COLOR_LIGHT_YELLOW"[USBConnected-Alarm!!!] Now:%u-%02u-%02u %s %02u:%02u:%02u"VTANSI_DISPLAY_RESET""CONFIG_LINE_ENDING, \
                                rtc.year+BASE_YEAR, rtc.mon+1, rtc.mday+1,     \
                                &wdays_str[rtc.wday*4], rtc.hour, rtc.min, rtc.sec);
                    }
                    LOG_Info("Research next AutoShutoff Alarm.");
                    crond_autoshutoff_calc(pcrond);
                }
            } else {
                CPU_INT32U s;
                s = priv->shutoff_active_nsecs-nsecs;
                if (s >= 60) pcrond->awake_ticks = OS_TICKS_PER_MIN;
                else pcrond->awake_ticks = (CPU_INT16U)(s*OS_TICKS_PER_SEC);
                #if 0
                {
                    CPU_INT32U h, m;
                    h = s/DEF_TIME_NBR_SEC_PER_HR;
                    s %= DEF_TIME_NBR_SEC_PER_HR;
                    m = s/DEF_TIME_NBR_SEC_PER_MIN;
                    s %= DEF_TIME_NBR_SEC_PER_MIN;
                    LOG_Info("Shutoff Current:%llus, Active:%llus, delta:[%u:%02u:%02u]", \
                            nsecs, priv->shutoff_active_nsecs, h, m, s);
                }
                #else
                //LOG_Print("#");
                #endif
            }
        }
    }
}

/*
********************************************************************************
* No More!
********************************************************************************
*/
