/*
********************************************************************************
* shape.c
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

#include "shape.h"

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



/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief
 *
 * @param
 *
 * @return
 *
 * @notes
 */



/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief 形状初始化
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
shape_t* shape_create(shape_vtbl_t const *vtbl, int type, const char *name, void *child)
{
    shape_t *self = NULL;

    self = (shape_t *)malloc(sizeof(shape_t));
    if (!self) {
        printf("It's not enough memory.\n");
        return NULL;
    }

    self->type = type;
    self->name = name;
    self->vtbl  = vtbl;
    self->child = child;

    return self;
}

/*
 * @brief 计算形状面积
 *
 * @param
 *
 * @return 面积值
 *
 * @notes
 */
float shape_area(shape_t const * const self)
{
    const shape_vtbl_t *vtbl = self->vtbl;

    return vtbl->area(self->child);
}

/*
 * @brief 计算形状的周长
 *
 * @param
 *
 * @return 周长值
 *
 * @notes
 */
float shape_perimeter(shape_t const * const self)
{
    const shape_vtbl_t *vtbl = self->vtbl;

    return vtbl->perimeter(self->child);
}

/*
 * @brief 画出形状
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
void shape_draw(shape_t const * const self)
{
    const shape_vtbl_t *vtbl = self->vtbl;

    return vtbl->draw(self->child);
}

/*
 * @brief 销毁形状
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
void shape_distory(shape_t * const self)
{
    const shape_vtbl_t *vtbl = self->vtbl;

    vtbl->distory(self->child);

    free(self);
}

/*
********************************************************************************
* No More!
********************************************************************************
*/
