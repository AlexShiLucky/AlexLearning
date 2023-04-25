/**
C语言和设计模式-<行为型>-<Strategy>-<策略模式>
意图:
    定义一系列的算法,把它们一个个封装起来,并且使它们可相互替换.本模式使得算法可独立于使用它的客户而变化.
适用性:
    许多相关的类仅仅是行为有异.“策略”提供了一种用多个行为中的一个行为来配置一个类的方法.
    需要使用一个算法的不同变体.例如,你可能会定义一些反映不同的空间/时间权衡的算法.当这些变体实现为一个算法的类层次时[H087] ,可以使用策略模式.
    算法使用客户不应该知道的数据.可使用策略模式以避免暴露复杂的、与算法相关的数据结构.
    一个类定义了多种行为,并且这些行为在这个类的操作中以多个条件语句的形式出现.将相关的条件分支移入它们各自的Strategy类中以代替这些条件语句.
*/
#include <stdio.h>

typedef struct _work_mode {
    void (*work)(void);
} work_mode_t;

void work_power_up(void)
{
    printf("power up init.\n");
}

void work_first_priming(void)
{

}

void work_idle(void)
{

}

void work_testing(void)
{

}

void work_maintain(void)
{

}

void work_error_deal(void)
{

}

void work_drain(void)
{

}

void work_power_down(void)
{

}

typedef struct _quack_behavior {
    void (*quack)(void);
} quack_behavior_t;

void quack(void)
{
    printf("鸭子呱呱叫\n");
}

void squeak(void)
{
    printf("橡皮鸭嘎嘎叫"); 
}

void mule_quack(void)
{

}

typedef struct _duck {
    struct _fly_behavior    fly_behavior;
    struct _quack_behavior  quack_behavior;
    
    void (*swim)(void);
    void (*display)(void);
    void (*perfom_fly)(struct _duck *);
    void (*perfom_quack)(struct _duck *);
    void (*set_fly_behavior)(struct _duck *, struct _fly_behavior *);
    void (*set_quack_behavior)(struct _duck *, struct _quack_behavior *);
} duck_t;

static void _swim(void)
{
    printf("swim\n");
}

static void _display(void)
{
    printf("display\n");
}

static void _perfom_fly(struct _duck *duck)
{
    duck->fly_behavior.fly();
}

static void _perfom_quack(struct _duck *duck)
{
    duck->quack_behavior.quack();
}

static void _set_fly_behavior(struct _duck *duck, struct _fly_behavior *fly_behavior)
{
    duck->fly_behavior = *fly_behavior;
}

static void _set_quack_behavior(struct _duck *duck, struct _quack_behavior *quack_behavior)
{
    duck->quack_behavior = *quack_behavior;
}

static duck_t   duck = {
    {fly_no_way},
    {quack},
    _swim,
    _display,
    _perfom_fly,
    _perfom_quack,
    _set_fly_behavior,
    _set_quack_behavior
};

// Strategy接口的使用
int main (int argc, char * argv[], char * envp[])
{
    duck.swim();
    duck.display();
    duck.perfom_fly(&duck);
    duck.perfom_quack(&duck);
    return 0;
}
