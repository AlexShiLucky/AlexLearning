/*
********************************************************************************
* clock.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __CLOCK_H
#define __CLOCK_H

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

#define BASE_YEAR       2000

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

struct _simple_time {
    CPU_INT08U sec;           /* Seconds. [0-60] (1 leap second) */
    CPU_INT08U min;           /* Minutes. [0-59] */
    CPU_INT08U hour;          /* Hours.   [0-23] */
    CPU_INT08U mday;          /* Day.     [0-30] */
    CPU_INT08U mon;           /* Month.   [0-11] */
    CPU_INT08U year;          /* Year - 2000. */
};
typedef struct _simple_time simple_time_t;

struct _tm {
    CPU_INT08U sec;           /* Seconds. [0-60] (1 leap second) */
    CPU_INT08U min;           /* Minutes. [0-59] */
    CPU_INT08U hour;          /* Hours.   [0-23] */
    CPU_INT08U mday;          /* Day.     [0-30] */
    CPU_INT08U mon;           /* Month.   [0-11] */
    CPU_INT08U year;          /* Year - 2000. */
    CPU_INT08U wday;          /* Day of week. [0-6] (Sun..Sat) */
    CPU_INT08S isdst;         /* DST.     [-1/0/1]*/
    CPU_INT16U yday;          /* Days in year.[0-365] */
};
typedef struct _tm tm_t;

#define DEF_FLAGS_TIME_INIT     DEF_BIT00_MASK
#define DEF_FLAGS_TIME_SYNC     DEF_BIT01_MASK
typedef struct _sys_time {
    CPU_INT32U flags;
    CPU_INT32U sync_ticks;
    CPU_INT64S sync_nsecs;
    struct _tm now;
} sys_time_t;


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

extern const char wdays_str[];
extern const char months_str[];

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

EXTERN CPU_INT64U sys_mktime(const simple_time_t *t);
EXTERN void time_to_tm(CPU_INT64U totalsecs, CPU_INT64S offset, struct _tm *result);
EXTERN cpu_bool_t sys_synctime(sys_time_t *nt, simple_time_t *t, cpu_bool_t isforce);
EXTERN cpu_bool_t sys_inittime(sys_time_t *nt, simple_time_t *t);
EXTERN cpu_bool_t sys_settime(sys_time_t *nt, CPU_INT32U ticks);
EXTERN cpu_bool_t sys_gettime(sys_time_t *nt, struct _tm *t);
EXTERN sys_time_t* sys_time_get(void);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __CLOCK_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
