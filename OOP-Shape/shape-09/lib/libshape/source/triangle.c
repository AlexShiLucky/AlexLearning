/*
********************************************************************************
* triangle.c
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

#include "triangle.h"

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

static float triangle_area(triangle_t const * const self);
static float triangle_perimeter(triangle_t const * const self);
static void triangle_draw(triangle_t const * const self);
static void triangle_distory(triangle_t * const self);

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

/* 子类实现父类的虚表 */
static const shape_vtbl_t g_triangle_vtbl = {
    .area = (void *)&triangle_area,
    .perimeter = (void *)&triangle_perimeter,
    .draw = (void *)&triangle_draw,
    .distory = (void *)&triangle_distory
};

/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief 计算三角形面积
 *
 * @param
 *
 * @return 面积值
 *
 * @notes
 */
static float triangle_area(triangle_t const * const self)
{
    float a = self->a;
    float b = self->b;
    float c = self->c;
    float p = (a + b + c) / 2;

    return sqrt(p*(p-a)*(p-b)*(p-c));
}

/*
 * @brief 计算三角形周长
 *
 * @param
 *
 * @return 周长值
 *
 * @notes
 */
static float triangle_perimeter(triangle_t const * const self)
{
    float a = self->a;
    float b = self->b;
    float c = self->c;

    return (a+b+c);
}

/*
 * @brief 画出矩形
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void triangle_draw(triangle_t const * const self)
{
    printf("I'm Triangle, a:%.3f, b:%.3f, c:%.3f\n", self->a, self->b, self->c);
}

/*
 * @brief 销毁三角形
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void triangle_distory(triangle_t * const self)
{
    printf("Distory %s\n", SHAPE(self)->name);
    free(self);    /* 释放子类数据 */
}


/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief 创建三角形
 *
 * @param a - 三角形一边
 * @param b - 三角形一边
 * @param c - 三角形一边
 *
 * @return 三角形句柄
 *
 * @notes
 */
triangle_t* triangle_create(float a, float b, float c)
{
    shape_t *super = NULL;
    triangle_t *self = NULL;

    self = (triangle_t *)malloc(sizeof(triangle_t));
    if (!self) {
        printf("It's not enough memory.\n");
        goto _err1;
    }

    super = shape_create(&g_triangle_vtbl, SHAPE_Triangle, "triangle", self);
    if (!super) {
        printf("It's not enough memory.\n");
        goto _err2;
    }

    self->a = a;
    self->b = b;
    self->c = c;
    self->super = super;
    printf("Create %s OK.\n", super->name);
    return self;

_err2:
    free(self);
_err1:
    return NULL;
}


/*
********************************************************************************
* No More!
********************************************************************************
*/
