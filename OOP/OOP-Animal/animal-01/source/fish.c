/*
********************************************************************************
* fish.c
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
#include "fish.h"

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

static void fish_eat(animal_t const * const super);
static void fish_breathe(animal_t const * const super);
static void fish_distory(animal_t * const super);
static void fish_move(moveable_t const * const super);

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
static const animal_vtbl_t g_fish_vtbl = {
    .eat = &fish_eat,
    .breathe = &fish_breathe,
    .distory = &fish_distory
};

/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief 鱼儿吃的行为
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void fish_eat(animal_t const * const super)
{
    // fish_t *self = (fish_t *)super;

    printf("鱼[%s]吃水草! \n", super->name);
}

/*
 * @brief 鱼儿呼吸的行为
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void fish_breathe(animal_t const * const super)
{
    // fish_t *self = (fish_t *)super;

    printf("鱼[%s]用鳃呼吸! \n", super->name);
}

/*
 * @brief 销毁鱼儿
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void fish_distory(animal_t * const super)
{
    fish_t *self = (fish_t *)super;

    printf("Distory %s\n", super->name);
    free(self);    /* 释放子类数据 */
}

/*
 * @brief 鱼儿移动的行为
 *
 * @param
 *
 * @return 无
 *
 * @notes
 */
static void fish_move(moveable_t const * const super)
{
    fish_t *self = container_of(super, fish_t, moveable);

    printf("鱼[%s]在水里游! \n", ANIMAL(self)->name);
}

/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief 创建鱼儿
 *
 * @param name - 鱼儿名称
 * @param age - 鱼儿年龄
 *
 * @return 动物句柄
 *
 * @notes
 */
fish_t* fish_create(const char *name, int age)
{
	animal_t *super = NULL;
    fish_t *self = NULL;

    self = (fish_t *)malloc(sizeof(fish_t));
    if (!self) {
        printf("It's not enough memory.\n");
        return NULL;
    }
    self->moveable.move = &fish_move;

	super = ANIMAL(self);
    animal_init(super, &g_fish_vtbl, ANIMAL_Fish, name, age);

    printf("Create %s OK.\n", super->name);

    return self;
}

/*
********************************************************************************
* No More!
********************************************************************************
*/
