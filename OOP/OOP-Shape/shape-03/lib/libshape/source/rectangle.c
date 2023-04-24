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

typedef struct _rectangle_priv rectangle_priv_t;

/* 子类:矩形私有数据 */
struct _rectangle_priv {
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
    rectangle_t *self = RECTANGLE(super);
    rectangle_priv_t *priv = (rectangle_priv_t *)self->priv;

    return (priv->width * priv->height);
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
    rectangle_t *self = RECTANGLE(super);
    rectangle_priv_t *priv = (rectangle_priv_t *)self->priv;

    return (priv->width + priv->height)*2;
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
    rectangle_t *self = RECTANGLE(super);
    rectangle_priv_t *priv = (rectangle_priv_t *)self->priv;

    printf("I'm Rectangele, width:%.3f, height:%.3f\n", priv->width, priv->height);
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
    rectangle_t *self = RECTANGLE(super);
    rectangle_priv_t *priv = (rectangle_priv_t *)self->priv;

    printf("Distory %s\n", super->name);
    free(priv);    /* 释放子类私有数据 */
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
    rectangle_priv_t *priv = NULL;

    self = (rectangle_t *)malloc(sizeof(rectangle_t));
    if (!self) {
        printf("It's not enough memory.\n");
        goto _err1;
    }

    priv = (rectangle_priv_t *)malloc(sizeof(rectangle_priv_t));
    if (!priv) {
        printf("It's not enough memory.\n");
        goto _err2;
    }
    priv->height = height;
    priv->width  = width;
    self->priv   = priv;

    super = SHAPE(self);
    shape_init(super, &g_rectangle_vtbl, SHAPE_Rectangle, "rectangle");
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
