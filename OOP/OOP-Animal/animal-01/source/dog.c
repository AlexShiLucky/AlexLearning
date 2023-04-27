/*
********************************************************************************
* dog.c
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

#include "common.h"
#include "dog.h"

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

static void dog_eat(animal_t const * const super);
static void dog_breathe(animal_t const * const super);
static void dog_distory(animal_t * const super);
static void dog_move(moveable_t const * const super);

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
static const animal_vtbl_t g_dog_vtbl = {
    .eat = &dog_eat,
    .breathe = &dog_breathe,
    .distory = &dog_distory
};

/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief 狗的吃行为
 *
 * @param
 *
 * @return 周长值
 *
 * @notes
 */
static void dog_eat(animal_t const * const super)
{
    // dog_t *self = (dog_t *)super;

    printf("狗[%s]吃骨头! \n", super->name);
}

/*
 * @brief 狗的呼吸行为
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void dog_breathe(animal_t const * const super)
{
    // dog_t *self = (dog_t *)super;

    printf("狗[%s]用肺呼吸! \n", super->name);
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
static void dog_distory(animal_t * const super)
{
    dog_t *self = (dog_t *)super;

    printf("Distory %s\n", super->name);
    free(self);    /* 释放子类数据 */
}

/*
 * @brief 狗移动的行为
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void dog_move(moveable_t const * const super)
{
    dog_t *self = container_of(super, dog_t, moveable);

    printf("狗[%s]在地上跑! \n", ANIMAL(self)->name);
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
dog_t* dog_create(const char *name, int age)
{
	animal_t *super = NULL;
    dog_t *self = NULL;

    self = (dog_t *)malloc(sizeof(dog_t));
    if (!self) {
        printf("It's not enough memory.\n");
        return NULL;
    }
    self->moveable.move = &dog_move;

	super = ANIMAL(self);
    animal_init(super, &g_dog_vtbl, ANIMAL_Dog, name, age);

    printf("Create %s OK.\n", super->name);

    return self;
}


/*
********************************************************************************
* No More!
********************************************************************************
*/
