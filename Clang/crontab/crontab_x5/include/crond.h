/*
********************************************************************************
* crond.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __CROND_H
#define __CROND_H

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

#define CONFIG_CROND_DLY_SECS           60


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

typedef struct _onoff_info {
    CPU_INT08U  isclr:1;
    CPU_INT08U  isonset:1;
    CPU_INT08U  isoffset:1;
    CPU_INT08U  ontype;
    CPU_INT08U  offtype;
    cpu_size_t  len;
    CPU_INT08U *pinfo;
} onoff_info_t;

#define DEF_FLAGS_CROND_AUTOSHUTOFF_CHECK_ACTIVE    DEF_BIT00_MASK
#define DEF_FLAGS_CROND_AUTOSHUTOFF_ACTIVED         DEF_BIT01_MASK
struct _crond {
    cpu_flag_t   flags;
    crontab_t    powerup;
    crontab_t    shutoff;
    onoff_info_t info;
    CPU_INT16U   awake_ticks;
    void        *priv;
};

typedef struct _crond crond_t;


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

EXTERN crond_t* crond_get(void);
EXTERN cpu_bool_t crond_autopowerup_calc(crond_t *pcrond);
EXTERN cpu_bool_t crond_autoshutoff_calc(crond_t *pcrond);
EXTERN void crond_autoshutoff_check(crond_t *pcrond);


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __CROND_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
