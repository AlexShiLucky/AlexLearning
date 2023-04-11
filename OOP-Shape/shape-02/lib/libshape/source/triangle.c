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

/* 对外隐藏子类定义 */
typedef struct _triangle triangle_t;

/* 子类:三角形 */
struct _triangle {
    /* 将父类定义在子类的第一个元素,来继承父类 */
    shape_t super;
    /* 子类特有属性 */
    float a;
    float b;
    float c;
};

/*
********************************************************************************
* Private Function Prototypes
********************************************************************************
*/

static float triangle_area(shape_t const * const super);
static float triangle_perimeter(shape_t const * const super);
static void triangle_draw(shape_t const * const super);
static void triangle_distory(shape_t * const super);

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
    .area = &triangle_area,
    .perimeter = &triangle_perimeter,
    .draw = &triangle_draw,
    .distory = &triangle_distory
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
static float triangle_area(shape_t const * const super)
{
    triangle_t *self = (triangle_t *)super;
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
static float triangle_perimeter(shape_t const * const super)
{
    triangle_t *self = (triangle_t *)super;

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
static void triangle_draw(shape_t const * const super)
{
    triangle_t *self = (triangle_t *)super;

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
static void triangle_distory(shape_t * const super)
{
    triangle_t *self = (triangle_t *)super;

    printf("Distory %s\n", super->name);
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
shape_t* triangle_create(float a, float b, float c)
{
    shape_t *super = NULL;
    triangle_t *self = NULL;

    self = (triangle_t *)malloc(sizeof(triangle_t));
    if (!self) {
        printf("It's not enough memory.\n");
        return NULL;
    }

	super = SHAPE(self);
    shape_init(super, &g_triangle_vtbl, SHAPE_Triangle, "triangle");

    self->a = a;
    self->b = b;
    self->c = c;
    printf("Create %s OK.\n", super->name);

    return super;
}


/*
********************************************************************************
* No More!
********************************************************************************
*/
