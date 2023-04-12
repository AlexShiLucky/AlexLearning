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

typedef struct _circle_priv circle_priv_t;

struct _circle_priv {
    float diameter;
};

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
    circle_priv_t *priv = (circle_priv_t *)self->priv;
    float radius = priv->diameter / 2;

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
    circle_priv_t *priv = (circle_priv_t *)self->priv;

    return (DEF_PI*priv->diameter);
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
    circle_priv_t *priv = (circle_priv_t *)self->priv;

    printf("I'm Circle, diameter:%.3f\n", priv->diameter);
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
    circle_priv_t *priv = (circle_priv_t *)self->priv;

    printf("Distory %s\n", SHAPE(self)->name);
    free(priv);    /* 释放子类私有数据 */
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
    circle_priv_t *priv = NULL;

    self = (circle_t *)malloc(sizeof(circle_t));
    if (!self) {
        printf("It's not enough memory.\n");
        goto _err1;
    }

    priv = (circle_priv_t *)malloc(sizeof(circle_priv_t));
    if (!priv) {
        printf("It's not enough memory.\n");
        goto _err2;
    }

    super = shape_create(&g_circle_vtbl, SHAPE_Circle, "circle", self);
    if (!super) {
        printf("It's not enough memory.\n");
        goto _err3;
    }

    priv->diameter = diameter;
    self->priv = priv;
    self->super = super;
    printf("Create %s OK.\n", super->name);
    return self;

_err3:
    free(priv);
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
