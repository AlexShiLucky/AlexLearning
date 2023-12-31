/*
********************************************************************************
* crontab.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __CRONTAB_H
#define __CRONTAB_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include "common.h"

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#define DEF_CRONTAB_YEAR_MIN    2000
#define DEF_CRONTAB_YEAR_MAX    2099

/*
********************************************************************************
* Shared Types
********************************************************************************
*/



/*
********************************************************************************
* Public Types
********************************************************************************
*/

enum _crontab_state {
    CRONTAB_STATE_Invalid = 0,
    CRONTAB_STATE_OK = 1,
    CRONTAB_STATE_Err = 2,
    CRONTAB_STATE_Inactive = 3
};

typedef struct _crontab_range {
    char *name;
    char *from;
    char *to;
    char **tabs;
    cpu_size_t nums;
} crontab_range_t;

typedef struct _daterange {
    CPU_INT16U year;
    CPU_INT08U month;
    CPU_INT08U day;
} daterange_t;

/*
# .——————————— minute (0 - 59)
# | .————————— hour (0 - 23)
# | | .——————— day of month (1 - 31)
# | | | .————— month (1 - 12) OR jan，feb，mar，apr……
# | | | | .——— day of week(0-6)(Sunday=0 or 7)OR sun，mon，tue，wed，thu，fri，sat
# | | | | |
# * * * * *    user-name command to be executed
*/

typedef struct _cronent_desc {
    CPU_INT64U min;  // Minutes repeat - bits 0-59
    CPU_INT32U hour; // Hours repeat - bits 0-23
    CPU_INT32U dom;  // Day-of-month repeat - bits 0-30
    CPU_INT16U mon;  // Monthly repeat - bits 0-11
    CPU_INT08U dow;  // Day-of-week repeat - bits 0-6
    struct _cronent_desc *next;
} cronent_desc_t;

typedef struct _crontab {
    CPU_INT08U state;
    daterange_t from;
    daterange_t to;
    cronent_desc_t *phead;
} crontab_t;

/*
********************************************************************************
* Inline Functions
********************************************************************************
*/



/*
********************************************************************************
* Shared Data
********************************************************************************
*/



/*
********************************************************************************
* Public Data
********************************************************************************
*/



/*
********************************************************************************
* Public Function Prototypes
********************************************************************************
*/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

EXTERN cpu_bool_t crontab_parse(crontab_t *pct, crontab_range_t *prange);
EXTERN cpu_bool_t crontab_cancel(crontab_t *pct);
EXTERN struct _tm * crontab_search(crontab_t *pct, struct _tm *pnow);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __CRONTAB_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
