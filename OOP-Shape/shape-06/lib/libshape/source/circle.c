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
    circle_t *self = (circle_t *)super->child;
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
    circle_t *self = (circle_t *)super->child;

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
    circle_t *self = (circle_t *)super->child;

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
    circle_t *self = (circle_t *)super->child;

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
        goto _err1;
    }

	super = shape_create(&g_circle_vtbl, SHAPE_Circle, "circle", self);
    if (!super) {
        printf("It's not enough memory.\n");
        goto _err2;
    }

    self->diameter = diameter;
    self->super = super;
    printf("Create %s OK.\n", super->name);
    return super;

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
