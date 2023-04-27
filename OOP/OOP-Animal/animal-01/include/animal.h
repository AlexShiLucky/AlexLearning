/*
********************************************************************************
* animal.h
*
*   Author: AlexShi <shiweining123@gmail.com>
*
********************************************************************************
*/

#ifndef __ANIMAL_H
#define __ANIMAL_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#define ANIMAL(object)   ((animal_t *)(object))

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

enum animal_type {
    ANIMAL_Fish,
    ANIMAL_Dog
};

/* 父类接口声明 */
typedef struct _animal_vtbl animal_vtbl_t;
/* 父类声明 */
typedef struct _animal animal_t;

/* 父类结构定义 */
struct _animal {
    int type;
    int age;
    const char *name;
    const animal_vtbl_t *vtbl;       /* 虚接口,所有子类必须实现 */
};

/* 父类接口定义 */
struct _animal_vtbl {
    /* 设置动物的昵称 */
    void (*set_name)(animal_t const * const, const char *);
    /* 设置动物的年龄 */
    void (*set_age)(animal_t const * const, int);
    /* 动物打招呼 */
    void (*say)(animal_t const * const);
    /* 动物都会吃(抽象方法，由子类实现) */
    void (*eat)(animal_t const * const);
    /* 动物都会呼吸(抽象方法，由子类实现) */
    void (*breathe)(animal_t const * const);
    /* 销毁 */
    void (*distory)(animal_t * const);
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
EXTERN void animal_init(animal_t * const self, animal_vtbl_t const *vtbl, int type, const char *name, int age);

/* 向上层提供的API */
EXTERN void animal_set_name(animal_t * const self, const char *name);
EXTERN void animal_set_age(animal_t * const self, int age);
EXTERN void animal_say(animal_t * const self);
EXTERN void animal_eat(animal_t const * const self);
EXTERN void animal_breathe(animal_t const * const self);
EXTERN void animal_distory(animal_t * const self);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __ANIMAL_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
