/**
C语言和设计模式-<行为型>-<State>-<状态模式>
意图:
    允许一个对象在其内部状态改变时改变它的行为.对象看起来似乎修改了它的类.
适用性:
    一个对象的行为取决于它的状态,并且它必须在运行时刻根据状态改变它的行为.
    一个操作中含有庞大的多分支的条件语句,且这些分支依赖于该对象的状态.
    这个状态通常用一个或多个枚举常量表示.
    通常,有多个操作包含这一相同的条件结构.
    State模式将每一个条件分支放入一个独立的类中.
    这使得你可以根据对象自身的情况将对象的状态作为一个对象,这一对象可以不依赖于其他对象而独立变化.
*/
#include <stdio.h>

// 人生状态
typedef enum _person_state {
    PSTATE_BABY     = 0,    // 婴儿
    PSTATE_YOUNG    = 1,    // 青少年
    PSTATE_MIDDLE   = 2,    // 中年
    PSTATE_OLD      = 3,    // 老年
    PSTATE_TOTAL            // 状态个数
} person_state_t;

// 人类:结构体
typedef struct _person {
    int (*action)(void);     // 状态对应的行为
} person_t;

// 婴儿状态:喝奶,etc.
int drink(void)
{
    printf("I am drinking milk!\n");

    return 0;
}

// 青少年状态:学习,etc.
int study(void)
{
    printf("I am study!\n");

    return 0;
}

// 中年状态:工作,etc.
int work(void)
{
    printf("I am working!\n");

    return 0;
}

// 老年状态:退休,etc.
int retire(void)
{
    printf("I am have been retired!\n");

    return 0;
}

void set_state(person_t *pPerson, person_state_t state)
{
    int (* const action_tbl[])(void) = { drink, study, work, retire };

    pPerson->action = action_tbl[state];
}

int main (int argc, char * argv[], char * envp[])
{
    person_state_t state;
    person_t person;

    for (state = 0; state < PSTATE_TOTAL; state++) {
        set_state(&person, state);
        person.action();
    }

    return 0;
}
