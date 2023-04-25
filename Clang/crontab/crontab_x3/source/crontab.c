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

static const char wdays_str[] = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat\0";
static const char months_str[] = "Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec\0";

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

static void FixDayDow(cronent_desc_t *desc)
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
CPU_INT64U cron_parsepart(char *str, char **end, int modvalue, int off, const char *names)
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
            for (i = 0; names[i]; i += 4) {
                /* was using strncmp before... */
                if (strncasecmp(str, &names[i], 3) == 0) {
                    *end = str + 3;
                    if (n1 < 0) {
                        n1 = i / 4;
                    } else {
                        n2 = i / 4;
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

int cron_parsedesc(char *str, cronent_desc_t *desc)
{
    char *s = str;

    desc->min = (CPU_INT64U)cron_parsepart(s, &s, 60, 0, NULL);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->hour = (CPU_INT32U)cron_parsepart(s + 1, &s, 24, 0, NULL);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->dom = (CPU_INT32U)cron_parsepart(s + 1, &s, 32, -1, NULL);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->mon = (CPU_INT16U)cron_parsepart(s + 1, &s, 12, -1, months_str);
    if (*s != ' ' && *s != '\t') return printf("invalid spec (separator @%ld)\r\n", s - str);

    desc->dow = (CPU_INT08U)cron_parsepart(s + 1, &s, 7, 0, wdays_str);
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

/*
********************************************************************************
* No More!
********************************************************************************
*/
