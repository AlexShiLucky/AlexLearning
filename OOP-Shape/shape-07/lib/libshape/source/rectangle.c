/*
********************************************************************************
* rectangle.c
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

#include "rectangle.h"

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
typedef struct _rectangle rectangle_t;

/* 子类:矩形 */
struct _rectangle {
    /* 指向父类的指针 */
    shape_t *super;
    /* 子类特有属性 */
    float width;
    float height;
};

/*
********************************************************************************
* Private Function Prototypes
********************************************************************************
*/

static float rectangle_area(shape_t const * const super);
static float rectangle_perimeter(shape_t const * const super);
static void rectangle_draw(shape_t const * const super);
static void rectangle_distory(shape_t * const super);

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
static const shape_vtbl_t g_rectangle_vtbl = {
    .area = &rectangle_area,
    .perimeter = &rectangle_perimeter,
    .draw = &rectangle_draw,
    .distory = &rectangle_distory
};

/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief 计算矩形面积
 *
 * @param
 *
 * @return 面积值
 *
 * @notes
 */
static float rectangle_area(shape_t const * const super)
{
    rectangle_t *self = (rectangle_t *)super->child;

    return (self->width * self->height);
}

/*
 * @brief 计算矩形周长
 *
 * @param
 *
 * @return 周长值
 *
 * @notes
 */
static float rectangle_perimeter(shape_t const * const super)
{
    rectangle_t *self = (rectangle_t *)super->child;

    return (self->width + self->height)*2;
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
static void rectangle_draw(shape_t const * const super)
{
    rectangle_t *self = (rectangle_t *)super->child;

    printf("I'm Rectangele, width:%.3f, height:%.3f\n", self->width, self->height);
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
static void rectangle_distory(shape_t * const super)
{
    rectangle_t *self = (rectangle_t *)super->child;

    printf("Distory %s\n", super->name);
    free(self);    /* 释放子类数据 */
}


/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief 创建矩形
 *
 * @param width - 矩形宽度
 * @param height - 矩形高度
 *
 * @return 矩形句柄
 *
 * @notes
 */
shape_t* rectangle_create(float width, float height)
{
    shape_t *super = NULL;
    rectangle_t *self = NULL;

    self = (rectangle_t *)malloc(sizeof(rectangle_t));
    if (!self) {
        printf("It's not enough memory.\n");
        goto _err1;
    }

	super = shape_create(&g_rectangle_vtbl, SHAPE_Rectangle, "rectangle", self);
    if (!super) {
        printf("It's not enough memory.\n");
        goto _err2;
    }

    self->height = height;
    self->width  = width;
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
