/**
C语言和设计模式-<行为型>-<Mediator>-<中介者模式>
意图:
    用一个中介对象来封装一系列的对象交互.中介者使各对象不需要显式地相互引用,从而使其耦合松散,而且可以独立地改变它们之间的交互.

适用性:
    一组对象以定义良好但是复杂的方式进行通信.产生的相互依赖关系结构混乱且难以理解.
    一个对象引用其他很多对象并且直接与这些对象通信,导致难以复用该对象.
    想定制一个分布在多个类中的行为,而又不想生成太多的子类.
*/
#include <stdio.h>

struct _people;

typedef struct _mediator {
    struct _people *pMan;
    struct _people *pWoman; 
} mediator_t;

typedef struct _people {
    const char *sex;
    struct _mediator *pMediator;

    void (*request)(struct _people *pPeople);
    void (*process)(struct _people *pPeople);
} people_t;

void man_request(people_t *pPeople)
{
    //assert(NULL != pPeople);
    people_t *pWoman = pPeople->pMediator->pWoman;

    pWoman->process(pWoman);
}

void man_process(people_t *pPeople)
{
    //assert(NULL != pPeople);
    
    printf("%s process %s's request.\n", pPeople->sex, pPeople->pMediator->pWoman->sex);
}

void woman_request(people_t *pPeople)
{
    //assert(NULL != pPeople);
    people_t *pMan = pPeople->pMediator->pMan;
    pMan->process(pMan);
}

void woman_process(people_t *pPeople)
{
    //assert(NULL != pPeople);
    
    printf("%s process %s's request.\n", pPeople->sex, pPeople->pMediator->pMan->sex);
}

static mediator_t mediator;

static people_t man = {
    .sex = "Man",
    .pMediator = &mediator,
    .request = man_request,
    .process = man_process
};

static people_t woman = {
    .sex = "Woman",
    .pMediator = &mediator,
    .request = woman_request,
    .process = woman_process
};

int main (int argc, char * argv[], char * envp[])
{
    mediator.pMan = &man;
    mediator.pWoman = &woman;
    
    man.request(&man);
    
    woman.request(&woman);

    return 0;
}
