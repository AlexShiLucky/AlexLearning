/*
********************************************************************************
* rectangle.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __RECTANGLE_H
#define __RECTANGLE_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include "shape.h"

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#define RECTANGLE(object)   ((rectangle_t *)(object))

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

typedef struct _rectangle rectangle_t;

/* 子类:矩形 */
struct _rectangle {
    /* 指向父类的指针 */
    shape_t *super;
    /* 子类私有属性 */
    void *priv;
};

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

EXTERN rectangle_t* rectangle_create(float width, float height);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __RECTANGLE_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
