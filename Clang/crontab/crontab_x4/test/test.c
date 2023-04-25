/*
********************************************************************************
* test1.c
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
void test_crontab(void)
{
    cronent_desc_t desc;
    char *crontab[] = {
        "* * * * *",
        "43 21 * * *",                      // 21:43 执行
        "15\t05 * * *",                     // 05:15 执行
        "0 17 * * 1",                       // 每周一的 17:00 执行
        "0 17 * * 0",                       // 每周日的 17:00 执行
        "0 17 * * 7",                       // 每周日的 17:00 执行
        "0 8 * * 1-5",                      // 每周一到周五8:00 执行
        "0 17 * * 1-5",                     // 每周一到周五17:00 执行
        "0 8-11,13-17 * * 1-5",             // 每周一到周五17:00 执行
        "0,10 17 * * 0,2,3",                // 每周日,周二,周三的 17:00和 17:10 执行
        "0-10 17 1 * *",                    // 毎月1日从 17:00到7:10 毎隔1分钟 执行
        "0 0 1,15 * 1",                     // 毎月1日和 15日和 一日的 0:00 执行
        "42 4 1 * *",                       // 毎月1日的 4:42分 执行
        "0 21 * * 1-6",                     // 周一到周六 21:00 执行
        "0,10,20,30,40,50 * * * *",         // 每隔10分 执行
        "0,10,20,30,40,50 * * * 2",         // 每隔10分 执行
        "0,10,20,30,40,50 * * * 2-5",       // 每隔10分 执行
        "*/10 * * * *",                     // 每隔10分 执行
        "* 1 * * *",                        // 从1:0到1:59 每隔1分钟 执行
        "0 1 * * *",                        // 1:00 执行
        "0 * * * *",                        // 毎时0分 每隔1小时 执行
        "0 */1 * * *",                      // 毎时0分 每隔1小时 执行
        "0 */3 * * *",                      // 毎时0分 每隔3小时 执行
        "0 8 */3 * *",                      // 1/4/7/10/13/16/19/22/25/28/31号 8:00执行
        "2 8-20/3 * * *",                   // 8:02,11:02,14:02,17:02,20:02 执行
        "2 8-20/3,7 * * *",                 // 8:02,11:02,14:02,17:02,20:02 执行
        "30 20-8/3 * * *",                  // 20:30 23:30 2:30 5:30 8:30执行
        "30 20-29/3 * * *",                 // 错误,超范围
        "30 5 1,15 * *",                    // 1日 和 15日的 5:30 执行
        "0 8 1 2-9 *",                      // 2/3/4/5/6/7/8/9月1号 8:00执行
        "0 8 1,15 1-10/3 *",                // 1/4/7/10月的1/15号 8:0执行
        "0 8 * * 1-5",                      // 每周一到周五 8:00执行
        "0 8 * * Mon-Fri",                  // 每周一到周五 8:00执行
        "0 20 * * 1-5",                     // 每周一到周五 20:00执行
        "0 20 * * Mon-Fri",                 // 每周一到周五 20:00执行
        "0 8 * * 1,3",                      // 周一、周三 8:00执行
        "0 8 * * Mon,Wed",                  // 周一、周三 8:00执行
        "0 8 * 1,3,6,8,10 *",               // 1/3/6/8/10月每天 8:00执行
        "0 8 * Jan,mar,Jun,Aug,oct *",      // 1/3/6/8/10月每天 8:00执行
        "0 8 * 1-8,12 *",                   // 1/2/3/4/5/6/7/8/12月每天 8:00执行
        "0 8 * jan-aug,Dec *",              // 1/2/3/4/5/6/7/8/12月每天 8:00执行
        "0 8 * 8-1 *",                      // 8/9/10/11/12/1月每天 8:00执行
        "0 8 * Aug-Jan *",                  // 8/9/10/11/12/1月每天 8:00执行
        "0 8 * 1-8,12 Mon,Fri",             // 1/2/3/4/5/6/7/8/12月周一/周五 8:00执行
        "0 8 * 1-8,12 1,5",                 // 1/2/3/4/5/6/7/8/12月周一/周五 8:00执行
        "0 8 * jan-aug,Dec Mon,Fri",        // 1/2/3/4/5/6/7/8/12月周一/周五 8:00执行
        "0 8 * 8-1 Mon-Fri",                // 8/9/10/11/12/1月周一到周五 8:00执行
        "0 8 * Aug-Jan 1-5",                // 8/9/10/11/12/1月周一到周五 8:00执行
        "0 8 * 8-1 1-5",                    // 8/9/10/11/12/1月周一到周五 8:00执行
        "0 8 * Aug-Jan Mon-Fri",            // 8/9/10/11/12/1月周一到周五 8:00执行
        "0 8 * Aug-Jan 1-3,Fri",            // 8/9/10/11/12/1月周一、周二、周三、周五 8:00执行
        "0 8 * Aug-Jan 1-Wed,Fri",          // 8/9/10/11/12/1月周一、周二、周三、周五 8:00执行
    };
    CPU_INT08U idx;
    int err;

    for (idx = 0; idx < sizeof(crontab) / sizeof(crontab[0]); idx++) {
        err = cron_parsedesc(crontab[idx], &desc);
        if (!err) {
            LOG_Info("[%2d] - %-32s - Min:[0x%016llX], Hour:[0x%08X], DayOfMonth:[0x%08X], Month:[0x%04X], DayOfWeek:[0x%02X]", \
                idx, crontab[idx], desc.min, desc.hour, desc.dom, desc.mon, desc.dow);
        } else {
            LOG_Info("[%2d] - %-32s - error:%u", idx, crontab[idx], err);
        }
    }
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
#if 0
int main(void)
{
    test_crond();

    return 0;
}
#endif

/*
********************************************************************************
* No More!
********************************************************************************
*/
