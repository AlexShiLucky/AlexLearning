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

static const char DowAry[] =
"sun""mon""tue""wed""thu""fri""sat"
;

static const char MonAry[] =
"jan""feb""mar""apr""may""jun""jul""aug""sep""oct""nov""dec"
;

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

static CPU_INT64U cron_parsepart(char *str, char **end, int modvalue, int off,
    const char *names)
    /* 'names' is a pointer to a set of 3-char abbreviations */
{
    CPU_INT64U res = 0;
    //char *base = str;
    int n1 = -1;
    int n2 = -1;
    int skip, i;

    while (1) {
        skip = 0;

        /* Handle numeric digit or symbol or '*' */
        if (*str == '*') {
            n1 = 0;  /* everything will be filled */
            n2 = modvalue - 1;
            skip = 1;
            *end = str + 1;
        } else if (isdigit(*str)) {
            if (n1 < 0) {
                n1 = strtol(str, end, 10) + off;
            } else {
                n2 = strtol(str, end, 10) + off;
            }
            skip = 1;
        } else if (names) {
            for (i = 0; names[i]; i += 3) {
                /* was using strncmp before... */
                if (strncasecmp(str, &names[i], 3) == 0) {
                    *end = str + 3;
                    if (n1 < 0) {
                        n1 = i / 3;
                    } else {
                        n2 = i / 3;
                    }
                    skip = 1;
                    break;
                }
            }
        }

        /* handle optional range '-' */
        if (skip == 0) {
            goto err;
        }
        if (**end == '-' && n2 < 0) {
            str = *end + 1;
            continue;
        }

        /*
         * collapse single-value ranges, handle skipmark, and fill
         * in the character array appropriately.
         */
        if (n2 < 0) {
            n2 = n1;
        }
        if (**end == '/') {
            str = *end + 1;
            skip = strtol(str, end, 10);
        }

        /*
         * fill array, using a failsafe is the easiest way to prevent
         * an endless loop
         */
        {
            int s0 = 1;
            int failsafe = 1024;

            --n1;
            do {
                n1 = (n1 + 1) % modvalue;

                if (--s0 == 0) {
                    res |= (CPU_INT64U)1 << (n1 % modvalue);
                    s0 = skip;
                }
                if (--failsafe == 0) {
                    goto err;
                }
            } while (n1 != n2);
        }
        if (**end != ',') {
            break;
        }
        str = *end + 1;
        n1 = -1;
        n2 = -1;
    }
err:
    return res;
}

static void FixDayDow(struct cronent_desc *desc)
{
    unsigned i;
    int weekUsed = 0;
    int daysUsed = 0;

    for (i = 0; i < 7; ++i) {
        if (!(desc->dow&(1 << i))) {
            weekUsed = 1;
            break;
        }
    }
    for (i = 0; i < 32; ++i) {
        if (!(desc->dom&(1 << i))) {
            daysUsed = 1;
            break;
        }
    }
    if (weekUsed != daysUsed) {
        if (weekUsed)
            desc->dom = 0;
        else /* daysUsed */
            desc->dow = 0;
    }
}

static int cron_parsedesc(char *str, struct cronent_desc *desc)
{
    char *s = str;

    desc->min = (CPU_INT64U)cron_parsepart(s, &s, 60, 0, NULL);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->hour = (CPU_INT32U)cron_parsepart(s + 1, &s, 24, 0, NULL);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->dom = (CPU_INT32U)cron_parsepart(s + 1, &s, 32, -1, NULL);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->mon = (CPU_INT16U)cron_parsepart(s + 1, &s, 12, -1, MonAry);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->dow = (CPU_INT08U)cron_parsepart(s + 1, &s, 7, 0, DowAry);
    while (*s != '\0' && (*s == ' ' || *s == '\t')) {
        s++;
    }
    if (*s != 0) return printf("invalid spec (trailing @%ld)\r\n", s - str);

    return 0;
    /*
     * fix days and dow - if one is not "*" and the other
     * is "*", the other is set to 0, and vise-versa
     */
    FixDayDow(desc);

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
        "0 8 * * mon,wed",
        "0 8 * jan,mar,jun,aug,oct *",
        "0 8 * jan-aug,dec *"
    };
    CPU_INT08U idx;

    for (idx = 0; idx < sizeof(crontab) / sizeof(crontab[0]); idx++) {
        cron_parsedesc(crontab[idx], &desc);
        printf("[%2d] - %-32s - Min:[0x%016llX], Hour:[0x%08X], DayOfMonth:[0x%08X], Month:[0x%04X], DayOfWeek:[0x%02X]\r\n", \
            idx, crontab[idx], desc.min, desc.hour, desc.dom, desc.mon, desc.dow);
    }

    return 0;
}
