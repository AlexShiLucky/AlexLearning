/*
********************************************************************************
* crontab.c
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

#include "clock.h"
#include "crontab.h"

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

struct _alarm_tm {
    CPU_INT08U min;           /* Minutes. [0-59] */
    CPU_INT08U hour;          /* Hours.   [0-23] */
    CPU_INT08U wday;          /* Day of week. [0-6] (Sun..Sat) */
    CPU_INT32U nsecs;         /* 相对于Sun,00:00走过的秒数 */
};

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

static struct _tm g_alarm_tm;

/*
********************************************************************************
* Private Functions
********************************************************************************
*/

#ifndef __GNUC__
/*****************************************************************************/
/* STRCASECMP() - Case-insensitive strcmp.                                   */
/*****************************************************************************/
static int strcasecmp(const char* s1, const char* s2)
{
    char c1, c2;
    do { c1 = *s1++; c2 = *s2++; } while (c1 && c2 && (tolower(c1) == tolower(c2)));

    return tolower(c1) - tolower(c2);
}

/*****************************************************************************/
/* STRNCASECMP() - Case-insensitive strncmp.                                 */
/*****************************************************************************/
static int strncasecmp(const char* s1, const char* s2, size_t n)
{
    char c1, c2;

    if (!n) return 0;

    do { c1 = *s1++; c2 = *s2++; } while (--n && c1 && c2 && (tolower(c1) == tolower(c2)));

    return tolower(c1) - tolower(c2);
}
#endif

static CPU_INT64S cron_parsepart(char *str, char **end, CPU_INT08U min, CPU_INT08U max, const char *names)
{
    CPU_INT64S res = 0;
    CPU_INT08U skip;
    CPU_INT08U mod;
    CPU_INT08U i;
    CPU_INT08S n1;
    CPU_INT08S n2;

    /* Gobble whitespace before potential stars; no strtol on that path */
    while (*str != '\0' && (*str == ' ' || *str == '\t')) {
        str++;
    }

    mod = max - min + 1;
    if (str[0] == '*') {
        skip = 1;
        *end = str + 1;
        if (str[1] == '/') {
            skip = strtol(str + 2, end, 10);
            if (skip == 0 || skip >= (max - min)) {
                LOG_Trace("invalid spec (skip %d)", skip);
                res = -1;
                goto _fail;
            }
        }

        for (i = 0; i <= (max - min); i++) {
            if ((i % skip) == 0) res |= (CPU_INT64U)1 << i;
        }
    } else {
        n1 = n2 = -1;
        while (1) {
            skip = 0;
            if (isdigit(*str)) {
                if (n1 < 0) {
                    n1 = strtol(str, end, 10);
                    if (n1 < min || n1 > max) {
                        LOG_Trace("invalid spec (val %d out of range %d..%d)", n1, min, max);
                        res = -2;
                        goto _fail;
                    }
                } else {
                    n2 = strtol(str, end, 10);
                    if (n2 < min || n2 > max) {
                        LOG_Trace("invalid spec (val %d out of range %d..%d)", n2, min, max);
                        res = -3;
                        goto _fail;
                    }
                }
                skip = 1;
            } else if (names) {
                for (i = 0; names[i]; i += 4) {
                    if (strncasecmp(str, &names[i], 3) == 0) {
                        *end = str + 3;
                        if (n1 < 0) {
                            n1 = i / 4 + min;
                        } else {
                            n2 = i / 4 + min;
                        }
                        skip = 1;
                        break;
                    }
                }
            }

            if (skip == 0) {
                res = -4;
                goto _fail;
            }
            if (**end == '-' && n2 < 0) {
                str = *end + 1;
                continue;
            }

            if (**end == '/') {
                str = *end + 1;
                skip = strtol(str, end, 10);
                if (skip == 0 || skip >= (max - min)) {
                    LOG_Trace("invalid spec (skip %d)", skip);
                    res = -5;
                    goto _fail;
                }
            }

            if (n2 < 0) {
                n2 = n1;
            } else if (n1 > n2) {
                n2 += mod;
            }

            for (i = (n1 - min); i <= (n2 - min); i += skip) {
                res |= (CPU_INT64U)1 << (i % mod);
            }

            if (**end != ',') break;
            str = *end + 1;
            n1 = n2 = -1;
        }
    }

_fail:
    return res;
}

static int cron_parsedesc(char *str, cronent_desc_t *desc)
{
    char *s = str;
    CPU_INT64S tmp;

    do {
        tmp = cron_parsepart(s, &s, 0, 59, NULL);
        if (tmp < 0) break;
        desc->min = (CPU_INT64U)tmp;
        if (*s != ' ' && *s != '\t') {
            LOG_Trace("invalid spec (separator @%ld)", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 0, 23, NULL);
        if (tmp < 0) break;
        desc->hour = (CPU_INT32U)tmp;
        if (*s != ' ' && *s != '\t') {
            LOG_Trace("invalid spec (separator @%ld)", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 1, 31, NULL);
        if (tmp < 0) break;
        desc->dom = (CPU_INT32U)tmp;
        if (*s != ' ' && *s != '\t') {
            LOG_Trace("invalid spec (separator @%ld)", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 1, 12, months_str);
        if (tmp < 0) break;
        desc->mon = (CPU_INT16U)tmp;
        if (*s != ' ' && *s != '\t') {
            LOG_Trace("invalid spec (separator @%ld)", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 0, 6, wdays_str);
        if (tmp < 0) break;
        desc->dow = (CPU_INT08U)tmp;
        while (*s != '\0' && (*s == ' ' || *s == '\t')) {
            s++;
        }
        if (*s != 0) {
            LOG_Trace("invalid spec (separator @%ld)", s - str);
            break;
        }
    } while (0);

    return (tmp < 0)? (int)tmp: 0;
}

static cpu_bool_t crontab_daterange_parse(daterange_t *pdr, const char *str)
{
    char *sbuf;
    char *pstr;
    int tmp;
    cpu_bool_t isok = DEF_No;

    sbuf = (char *)malloc(strlen(str) + 1);     // 注意:不能使用系统函数strdup,该函数会从系统堆中申请内存,导致内存泄漏
    //LOG_Info("sbuf=%p", sbuf);
    if (sbuf) {
        strcpy(sbuf, str);
        do {
            pstr = strtok(sbuf, " \t");
            tmp = atoi(pstr);
            if ((tmp >= DEF_CRONTAB_YEAR_MIN) && (tmp <= DEF_CRONTAB_YEAR_MAX)) {
                pdr->year = tmp;
            } else break;

            pstr = strtok(NULL, " \t");
            tmp = atoi(pstr);
            if ((tmp >= 1) && (tmp <= 12)) {
                pdr->month = tmp;
            } else break;

            pstr = strtok(NULL, " \t");
            tmp = atoi(pstr);
            if ((tmp >= 1) && (tmp <= 31)) {
                pdr->day = tmp;
            } else break;

            isok = DEF_Yes;
        } while (0);
        free(sbuf);
    }

    return isok;
}

static void cronent_desc_list_free(cronent_desc_t *phead)
{
    cronent_desc_t *pnext;

    while (phead) {
        pnext = phead->next;
        free(phead);
        phead = pnext;
    }
}

static CPU_INT08U mask_search(CPU_INT08U start, CPU_INT08U end, CPU_INT08U mod, CPU_INT64U mask)
{
    CPU_INT08U idx, pos;

    for (idx = start; idx < end; idx++) {
        pos = idx % mod;
        if (mask&(1ull<<pos)) return pos;
    }

    return idx;
}

/* 计算相对于Sunday,00:00的时间间隔 */
static CPU_INT32U crontab_second_calc(CPU_INT08U wday, CPU_INT08U hr, CPU_INT08U min)
{
    CPU_INT32U nsecs;

    nsecs = (wday * DEF_TIME_NBR_SEC_PER_DAY) \
          + (hr * DEF_TIME_NBR_SEC_PER_HR) \
          + (min * DEF_TIME_NBR_SEC_PER_MIN);

    return nsecs;
}

static struct _tm * crontab_pattern_match(crontab_t *pct, CPU_INT64U cstart)
{
    struct _tm *pmin = NULL;
    cronent_desc_t *pnext;
    tm_t tm_start;
    struct _alarm_tm mint;  // 满足全部规则的最近时间
    struct _alarm_tm curt;  // 满足当前规则的最近时间
    CPU_INT32U nsecs_start;
    CPU_INT08U idx;
    cpu_bool_t isok = DEF_Yes;
    cpu_bool_t isinit = DEF_No;

    time_to_tm(cstart, 0, &tm_start);
    nsecs_start = crontab_second_calc(tm_start.wday, tm_start.hour, tm_start.min);

    pnext = pct->phead; // 规则链表
    while (pnext) {
        curt.wday = tm_start.wday;
        curt.hour = tm_start.hour;
        curt.min  = tm_start.min;
    _next1:
        curt.wday %= 7;
        /* 搜索最近的星期规则 */
        idx = mask_search(curt.wday, curt.wday+7, 7, pnext->dow);
        if (curt.wday != idx) { // 如果当前星期与搜索到的不一致,则以搜索到的为准
            curt.wday = idx;
            curt.hour = 0;
            curt.min  = 0;
        }
    _next2:
        /* 搜索最近的小时规则 */
        idx = mask_search(curt.hour, 24, 24, pnext->hour);
        if (idx == 24) {    // 搜索到结尾未搜到匹配
            if (curt.hour) {// 如果不是从0时开始搜索,则+1天从0时重新搜索
                curt.min = 0;
                curt.hour = 0;
                curt.wday++;
                goto _next1;
            } else {        // 如果从0时开始搜索都没有搜索到
                LOG_Warn("ERROR-1");
                isok = DEF_No;
                break;
            }
        }
        if (curt.hour != idx) { // 如果当前小时与搜索到的不一致,则以搜索到的为准
            curt.hour = idx;
            curt.min = 0;
        }

        /* 搜索最近的分钟规则 */
        idx = mask_search(curt.min, 60, 60, pnext->min);
        if (idx == 60) {    // 搜索到结尾未搜到匹配
            if (curt.min) { // 如果不是从0分开始搜索,则+1小时从0分重新搜索
                curt.min = 0;
                curt.hour++;
                goto _next2;
            } else {        // 如果从0分开始搜索都没有搜索到
                LOG_Warn("ERROR-2");
                isok = DEF_No;
                break;
            }
        } else {    // 以搜索到的分钟为准
            curt.min = idx;
        }
        LOG_Info("+%s, %02u:%02u", &wdays_str[curt.wday*4], curt.hour, curt.min);

        curt.nsecs = crontab_second_calc(curt.wday, curt.hour, curt.min);
        if (curt.nsecs < nsecs_start) curt.nsecs += DEF_TIME_NBR_SEC_PER_WK;
        if (isinit) {
            if (curt.nsecs < mint.nsecs) mint = curt;
        } else {
            /* 还未初始化过 */
            isinit = DEF_Yes;
            mint = curt;
        }
        LOG_Info("*%s, %02u:%02u", &wdays_str[mint.wday*4], mint.hour, mint.min);

        pnext = pnext->next;
    }

    if (isinit && isok) {
        if (mint.nsecs >= nsecs_start) {
            /* mint表示将来最近的关机时间,所有该值必须大于等于当前值 */
            time_to_tm(cstart, mint.nsecs - nsecs_start, &g_alarm_tm);
            pmin = &g_alarm_tm;
        } else {
            LOG_Trace("mint.nsecs[%ul] < nsecs_start[%ul]", mint.nsecs, nsecs_start);
        }
    }

    return pmin;
}


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
cpu_bool_t crontab_parse(crontab_t *pct, crontab_range_t *prange)
{
    cronent_desc_t *phead = NULL;
    cronent_desc_t *pdesc;
    char *pstr;
    cpu_size_t idx;
    CPU_INT08U state = CRONTAB_STATE_Invalid;
    cpu_bool_t isok = DEF_No;

    do {
        if (!crontab_daterange_parse(&pct->from, prange->from)) {
            LOG_Warn("Parse [%s] crontab date[%s] from error!", \
                    prange->name, prange->from);
            state = CRONTAB_STATE_Err;
            break;
        }

        if (!crontab_daterange_parse(&pct->to, prange->to)) {
            LOG_Warn("Parse [%s] crontab date[%s] to error!", \
                    prange->name, prange->to);
            state = CRONTAB_STATE_Err;
            break;
        }

        LOG_Info("[%s] Date range: [%u/%02u/%02u - %u/%02u/%02u]", \
            prange->name, \
            pct->from.year, pct->from.month, pct->from.day, \
            pct->to.year, pct->to.month, pct->to.day);

        for (idx = 0; idx < prange->nums; idx++) {
            pdesc = (cronent_desc_t *)calloc(1, sizeof(cronent_desc_t));
            pstr = prange->tabs[idx];
            if (!pdesc || cron_parsedesc(pstr, pdesc)) {
                state = CRONTAB_STATE_Err;
                free(pdesc);
                break;
            }
            pdesc->next = phead;
            phead = pdesc;
        }
        /* 创建新链表失败,需将其释放 */
        if (state == CRONTAB_STATE_Err) {
            LOG_Warn("Parse error & Free crontab list.");
            cronent_desc_list_free(phead);
            break;
        }

        /* 释放原先的列表 */
        LOG_Info("Free old crontab list[%p].", pct->phead);
        cronent_desc_list_free(pct->phead);
        /* 挂接新的列表 */
        pct->phead = phead;

        state = CRONTAB_STATE_OK;
        isok = DEF_Yes;
    } while (0);

    pct->state = state;

    return isok;
}

cpu_bool_t crontab_cancel(crontab_t *pct)
{
    memset(&pct->from, 0, sizeof(daterange_t));
    memset(&pct->to, 0, sizeof(daterange_t));
    cronent_desc_list_free(pct->phead);
    pct->state = CRONTAB_STATE_Invalid;
    pct->phead = NULL;

    return DEF_Yes;
}

struct _tm * crontab_search(crontab_t *pct, struct _tm *pnow)
{
    struct _tm *pmin = NULL;
    CPU_INT64U cfrom, cto, ctmp;

    do {
        if (pct->state != CRONTAB_STATE_OK) break;

        {
            tm_t tm;

            tm.year = pct->from.year - BASE_YEAR;
            tm.mon  = pct->from.month - 1;
            tm.mday = pct->from.day - 1;
            tm.hour = 0;
            tm.min  = 0;
            tm.sec  = 0;
            cfrom = sys_mktime((simple_time_t *)&tm);
            LOG_Info("From:%u-%02u-%02u[%llu]", tm.year+BASE_YEAR, tm.mon+1, tm.mday+1, cfrom);

            tm.year = pct->to.year - BASE_YEAR;
            tm.mon  = pct->to.month - 1;
            tm.mday = pct->to.day - 1;
            tm.hour = 23;
            tm.min  = 59;
            tm.sec  = 59;
            cto = sys_mktime((simple_time_t *)&tm);
            LOG_Info("To:%u-%02u-%02u[%llu]", tm.year+BASE_YEAR, tm.mon+1, tm.mday+1, cto);

            ctmp = sys_mktime((simple_time_t *)pnow);
            LOG_Info("Now:%u-%02u-%02u[%llu]", pnow->year+BASE_YEAR, pnow->mon+1, pnow->mday+1, ctmp);
        }

        if (ctmp < cfrom) {
            pmin = crontab_pattern_match(pct, cfrom);
        } else if (ctmp < cto) {
            pmin = crontab_pattern_match(pct, ctmp);
        } else {
            LOG_Info("Out of date range1.");
            break;
        }
        if (pmin) {
            ctmp = sys_mktime((simple_time_t *)pmin);
            if (ctmp >= cto) {
                pmin = NULL;
                LOG_Info("Out of date range2.");
            } else {
                LOG_Info("Alarm Time:%u-%02u-%02u %02u:%02u %s", pmin->year+BASE_YEAR,\
                        pmin->mon+1, pmin->mday+1, pmin->hour, pmin->min,\
                        &wdays_str[pmin->wday*4]);
            }
        }
    } while (0);

    return pmin;
}

/*
********************************************************************************
* No More!
********************************************************************************
*/
