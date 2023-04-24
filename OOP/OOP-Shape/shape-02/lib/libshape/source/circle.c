/*
********************************************************************************
* circle.c
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

#include "circle.h"

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
typedef struct _circle circle_t;

/* 子类:圆 */
struct _circle {
    /* 将父类定义在子类的第一个元素,来继承父类 */
    shape_t super;
    /* 子类特有属性 */
    float diameter;
};

/*
********************************************************************************
* Private Function Prototypes
********************************************************************************
*/

static float circle_area(shape_t const * const super);
static float circle_perimeter(shape_t const * const super);
static void circle_draw(shape_t const * const super);
static void circle_distory(shape_t * const super);

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
static const shape_vtbl_t g_circle_vtbl = {
    .area = &circle_area,
    .perimeter = &circle_perimeter,
    .draw = &circle_draw,
    .distory = &circle_distory
};

/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief 计算圆面积
 *
 * @param
 *
 * @return 面积值
 *
 * @notes
 */
static float circle_area(shape_t const * const super)
{
    circle_t *self = (circle_t *)super;
    float radius = self->diameter / 2;

    return (DEF_PI * radius * radius);
}

/*
 * @brief 计算圆周长
 *
 * @param
 *
 * @return 周长值
 *
 * @notes
 */
static float circle_perimeter(shape_t const * const super)
{
    circle_t *self = (circle_t *)super;

    return (DEF_PI*self->diameter);
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
static void circle_draw(shape_t const * const super)
{
    circle_t *self = (circle_t *)super;

    printf("I'm Circle, diameter:%.3f\n", self->diameter);
}

/*
 * @brief 销毁矩形
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void circle_distory(shape_t * const super)
{
    circle_t *self = (circle_t *)super;

    printf("Distory %s\n", super->name);
    free(self);    /* 释放子类数据 */
}

/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief 创建圆
 *
 * @param diameter - 直径
 *
 * @return 矩形句柄
 *
 * @notes
 */
shape_t* circle_create(float diameter)
{
	shape_t *super = NULL;
    circle_t *self = NULL;

    self = (circle_t *)malloc(sizeof(circle_t));
    if (!self) {
        printf("It's not enough memory.\n");
        return NULL;
    }

	super = SHAPE(self);
    shape_init(super, &g_circle_vtbl, SHAPE_Circle, "circle");

    self->diameter = diameter;
    printf("Create %s OK.\n", super->name);

    return super;
}

/*
********************************************************************************
* No More!
********************************************************************************
*/
