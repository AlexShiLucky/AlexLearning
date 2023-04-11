/*
********************************************************************************
* shape.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __SHAPE_H
#define __SHAPE_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#define SHAPE(object)   ((shape_t *)(object))

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

enum shape_type {
    SHAPE_Circle,
    SHAPE_Triangle,
    SHAPE_Rectangle
};

/* 父类接口声明 */
typedef struct _shape_vtbl shape_vtbl_t;
/* 父类声明 */
typedef struct _shape shape_t;

/* 父类结构定义 */
struct _shape {
    int type;
    const char *name;
    const shape_vtbl_t *vtbl;       /* 虚接口,所有子类必须实现 */
    void *child;
};

/* 父类接口定义 */
struct _shape_vtbl {
    /* 计算几何体的面积 */
    float (*area)(shape_t const * const);
    /* 计算几何体的周长 */
    float (*perimeter)(shape_t const * const);
    /* 画出图形 */
    void (*draw)(shape_t const * const);
    /* 销毁形状 */
    void (*distory)(shape_t * const);
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

/* 向下层提供的API */
EXTERN shape_t* shape_create(shape_vtbl_t const *vtbl, int type, const char *name, void *child);

/* 向上层提供的API */
EXTERN float shape_area(shape_t const * const self);
EXTERN float shape_perimeter(shape_t const * const self);
EXTERN void shape_draw(shape_t const * const self);
EXTERN void shape_distory(shape_t * const self);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __SHAPE_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
