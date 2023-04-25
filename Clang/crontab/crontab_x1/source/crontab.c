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



/*
********************************************************************************
* Private Functions
********************************************************************************
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
CPU_INT64U cron_parsepart(char *str, char **end, CPU_INT08U min, CPU_INT08U max)
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

int cron_parsedesc(char *str, cronent_desc_t *desc)
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

/*
********************************************************************************
* No More!
********************************************************************************
*/
