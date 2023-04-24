#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef  unsigned  char         cpu_bool_t;
typedef  unsigned  char         CPU_INT08U;             /*  8-bit unsigned integer                    */
typedef    signed  char         CPU_INT08S;             /*  8-bit   signed integer                    */
typedef  unsigned  short        CPU_INT16U;             /* 16-bit unsigned integer                    */
typedef    signed  short        CPU_INT16S;             /* 16-bit   signed integer                    */
typedef  unsigned  int          CPU_INT32U;             /* 32-bit unsigned integer                    */
typedef    signed  int          CPU_INT32S;             /* 32-bit   signed integer                    */
typedef  unsigned  long  long   CPU_INT64U;             /* 64-bit unsigned integer                    */
typedef    signed  long  long   CPU_INT64S;             /* 64-bit   signed integer                    */

struct cronent_desc {
    CPU_INT64U min;  // Minutes repeat - bits 0-59
    CPU_INT32U hour; // Hours repeat - bits 0-23
    CPU_INT32U dom;  // Day-of-month repeat - bits 0-30
    CPU_INT16U mon;  // Monthly repeat - bits 0-11
    CPU_INT08U dow;  // Day-of-week repeat - bits 0-6
};

static const char wdays_str[] = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat\0";
static const char months_str[] = "Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec\0";

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
                printf("invalid spec (skip %u)\r\n", skip);
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
                        printf("invalid spec (val %u out of range %u..%u)\r\n", n1, min, max);
                        res = -2;
                        goto _fail;
                    }
                } else {
                    n2 = strtol(str, end, 10);
                    if (n2 < min || n2 > max) {
                        printf("invalid spec (val %u out of range %u..%u)\r\n", n2, min, max);
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
                    printf("invalid spec (skip %u)\r\n", skip);
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

static int cron_parsedesc(char *str, struct cronent_desc *desc)
{
    char *s = str;
    CPU_INT64S tmp;

    do {
        tmp = cron_parsepart(s, &s, 0, 59, NULL);
        if (tmp < 0) break;
        desc->min = (CPU_INT64U)tmp;
        if (*s != ' ' && *s != '\t') {
            printf("invalid spec (separator @%ld)\r\n", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 0, 23, NULL);
        if (tmp < 0) break;
        desc->hour = (CPU_INT32U)tmp;
        if (*s != ' ' && *s != '\t') {
            printf("invalid spec (separator @%ld)\r\n", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 1, 31, NULL);
        if (tmp < 0) break;
        desc->dom = (CPU_INT32U)tmp;
        if (*s != ' ' && *s != '\t') {
            printf("invalid spec (separator @%ld)\r\n", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 1, 12, months_str);
        if (tmp < 0) break;
        desc->mon = (CPU_INT16U)tmp;
        if (*s != ' ' && *s != '\t') {
            printf("invalid spec (separator @%ld)\r\n", s - str);
            break;
        }

        tmp = cron_parsepart(s + 1, &s, 0, 6, wdays_str);
        if (tmp < 0) break;
        desc->dow = (CPU_INT08U)tmp;
        while (*s != '\0' && (*s == ' ' || *s == '\t')) {
            s++;
        }
        if (*s != 0) {
            printf("invalid spec (separator @%ld)\r\n", s - str);
            break;
        }
    } while (0);

    return (tmp < 0)? (int)tmp: 0;
}

int main(int argc, char * argv[])
{
    struct cronent_desc desc;
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
            printf("[%2d] - %-32s - Min:[0x%016llX], Hour:[0x%08X], DayOfMonth:[0x%08X], Month:[0x%04X], DayOfWeek:[0x%02X]\r\n", \
                idx, crontab[idx], desc.min, desc.hour, desc.dom, desc.mon, desc.dow);
        } else {
            printf("[%2d] - %-32s - error:%u\r\n", idx, crontab[idx], err);
        }
    }

    return 0;
}
