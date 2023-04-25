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
CPU_INT64S cron_parsepart(char *str, char **end, CPU_INT08U min, CPU_INT08U max, const char *names)
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

int cron_parsedesc(char *str, cronent_desc_t *desc)
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

/*
********************************************************************************
* No More!
********************************************************************************
*/
