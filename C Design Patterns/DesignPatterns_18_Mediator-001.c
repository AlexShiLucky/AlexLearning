/**
C���Ժ����ģʽ-<��Ϊ��>-<Mediator>-<�н���ģʽ>
��ͼ:
    ��һ���н��������װһϵ�еĶ��󽻻�.�н���ʹ��������Ҫ��ʽ���໥����,�Ӷ�ʹ�������ɢ,���ҿ��Զ����ظı�����֮��Ľ���.

������:
    һ������Զ������õ��Ǹ��ӵķ�ʽ����ͨ��.�������໥������ϵ�ṹ�������������.
    һ���������������ܶ������ֱ������Щ����ͨ��,�������Ը��øö���.
    �붨��һ���ֲ��ڶ�����е���Ϊ,���ֲ�������̫�������.
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
