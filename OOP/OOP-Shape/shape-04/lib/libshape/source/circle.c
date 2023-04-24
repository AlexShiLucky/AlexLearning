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

static float circle_area(circle_t const * const self);
static float circle_perimeter(circle_t const * const self);
static void circle_draw(circle_t const * const self);
static void circle_distory(circle_t * const self);

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
    .area = (void *)&circle_area,
    .perimeter = (void *)&circle_perimeter,
    .draw = (void *)&circle_draw,
    .distory = (void *)&circle_distory
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
static float circle_area(circle_t const * const self)
{
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
static float circle_perimeter(circle_t const * const self)
{
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
static void circle_draw(circle_t const * const self)
{
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
static void circle_distory(circle_t * const self)
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
 * @brief 创建圆
 *
 * @param diameter - 直径
 *
 * @return 矩形句柄
 *
 * @notes
 */
circle_t* circle_create(float diameter)
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

    return self;
}

/*
********************************************************************************
* No More!
********************************************************************************
*/
