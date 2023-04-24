#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

static CPU_INT64U cron_parsepart(char *str, char **end, CPU_INT08U min, CPU_INT08U max)
{
    CPU_INT64U res = 0;
    CPU_INT08U each;
    CPU_INT08U n1, n2;
    CPU_INT08U i;

    /* Gobble whitespace before potential stars; no strtol on that path */
    while (*str != '\0' && (*str == ' ' || *str == '\t')) {
        str++;
    }

    if (str[0] == '*') {
        each = 1;
        *end = str + 1;
        if (str[1] == '/') {
            each = strtol(str + 2, end, 10);
            if (each == 0 || each >= max - min) {
                return printf("invalid spec (each %u)\r\n", each);
            }
        }

        for (i = 0; i <= (max - min); i++) {
            if ((i % each) == 0) res |= (CPU_INT64U)1 << i;
        }
    } else {
        while (1) {
            n1 = strtol(str, end, 10);
            if (n1 < min || n1 > max) {
                return printf("invalid spec (val %u out of range %u..%u)\r\n", n1, min, max);
            }
            if (**end == '-') {
                each = 1;
                str = *end + 1;
                n2 = strtol(str, end, 10);
                if (n2 < min || n2 > max) {
                    return printf("invalid spec (val %u out of range %u..%u)\r\n", n2, min, max);
                }
                str = *end;
                if (str[0] == '/') {
                    each = strtol(str + 1, end, 10);
                    if (each == 0 || each >= max - min) {
                        return printf("invalid spec (each %u)\r\n", each);
                    }
                }
                if (n1 < n2) {
                    for (i = (n1-min); i <= (n2-min); i+=each) {
                        res |= (CPU_INT64U)1 << i;
                    }
                } else {
                    for (i = (n1-min); i <= (n2+max-2*min); i += each) {
                        res |= (CPU_INT64U)1 << (i%(max-min));
                    }
                }
            }
            else {
                res |= (CPU_INT64U)1 << (n1 - min);
            }
            if (**end != ',') break;
            str = *end + 1;
        }
    }

    return res;
}

static int cron_parsedesc(char *str, struct cronent_desc *desc)
{
    char *s = str;

    desc->min = (CPU_INT64U)cron_parsepart(s, &s, 0, 59);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->hour = (CPU_INT32U)cron_parsepart(s + 1, &s, 0, 23);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->dom = (CPU_INT32U)cron_parsepart(s + 1, &s, 1, 31);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->mon = (CPU_INT16U)cron_parsepart(s + 1, &s, 1, 12);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->dow = (CPU_INT08U)cron_parsepart(s + 1, &s, 0, 6);
    while (*s != '\0' && (*s == ' ' || *s == '\t')) {
        s++;
    }
    if (*s != 0) return printf("invalid spec (trailing @%ld)\r\n", s - str);

    return 0;
}

int main(int argc, char * argv[])
{
    struct cronent_desc desc;
    char *crontab[] = {
        "* * * * *",
        "43 21 * * *",                // 21:43 执行
        "15 05 * * *",                // 05:15 执行
        "0 17 * * 1",                 // 每周一的 17:00 执行
        "0 8 * * 1-5",                // 每周一到周五8:00 执行
        "0 17 * * 1-5",               // 每周一到周五17:00 执行
        "0 8-11,13-17 * * 1-5",       // 每周一到周五17:00 执行
        "0,10 17 * * 0,2,3",          // 每周日,周二,周三的 17:00和 17:10 执行
        "0-10 17 1 * *",              // 毎月1日从 17:00到7:10 毎隔1分钟 执行
        "0 0 1,15 * 1",               // 毎月1日和 15日和 一日的 0:00 执行
        "42 4 1 * *",                 // 毎月1日的 4:42分 执行
        "0 21 * * 1-6",               // 周一到周六 21:00 执行
        "0,10,20,30,40,50 * * * *",   // 每隔10分 执行
        "0,10,20,30,40,50 * * * 2",   // 每隔10分 执行
        "0,10,20,30,40,50 * * * 2-5", // 每隔10分 执行
        "*/10 * * * *",               // 每隔10分 执行
        "* 1 * * *",                  // 从1:0到1:59 每隔1分钟 执行
        "0 1 * * *",                  // 1:00 执行
        "0 * * * *",                  // 毎时0分 每隔1小时 执行
        "0 */1 * * *",                // 毎时0分 每隔1小时 执行
        "0 */3 * * *",                // 毎时0分 每隔3小时 执行
        "0 8 */3 * *",
        "2 8-20/3 * * *",             // 8:02,11:02,14:02,17:02,20:02 执行
        "2 8-20/3,7 * * *",           // 8:02,11:02,14:02,17:02,20:02 执行
        "30 5 1,15 * *",              // 1日 和 15日的 5:30 执行
    };
    CPU_INT08U idx;

    for (idx = 0; idx < sizeof(crontab) / sizeof(crontab[0]); idx++) {
        cron_parsedesc(crontab[idx], &desc);
        printf("[%2d] - %-32s - Min:[0x%016llX], Hour:[0x%08X], DayOfMonth:[0x%08X], Month:[0x%04X], DayOfWeek:[0x%02X]\r\n", \
            idx, crontab[idx], desc.min, desc.hour, desc.dom, desc.mon, desc.dow);
    }

    return 0;
}
