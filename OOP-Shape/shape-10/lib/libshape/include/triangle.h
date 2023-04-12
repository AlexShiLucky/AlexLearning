/*
********************************************************************************
* triangle.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __TRIANGLE_H
#define __TRIANGLE_H

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

#define TRIANGLE(object)   ((triangle_t *)(object))

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

typedef struct _triangle triangle_t;

/* 子类:三角形 */
struct _triangle {
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

EXTERN triangle_t* triangle_create(float a, float b, float c);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __TRIANGLE_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
