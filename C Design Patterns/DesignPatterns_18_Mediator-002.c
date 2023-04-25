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

    void (*request)(void *);
    void (*process)(void *);
} people_t;

void man_request(void *pdata)
{
    //assert(NULL != pdata);
    
    people_t *pMan;
    people_t *pWoman;
    
    pMan = (people_t *)pdata;
    pWoman = pMan->pMediator->pWoman;

    pWoman->process(pWoman);
}

void man_process(void *pdata)
{
    //assert(NULL != pdata);
    
    people_t *pMan;
    people_t *pWoman;
    
    pMan = (people_t *)pdata;
    pWoman = pMan->pMediator->pWoman;

    printf("%s process %s's request.\n", pMan->sex, pWoman->sex);
}

void woman_request(void *pdata)
{
    //assert(NULL != pdata);
    
    people_t *pMan;
    people_t *pWoman;
    
    pWoman = (people_t *)pdata;
    pMan = pWoman->pMediator->pMan;
    
    pMan->process(pMan);
}

void woman_process(void *pdata)
{
    //assert(NULL != pdata);
    
    people_t *pMan;
    people_t *pWoman;
    
    pWoman = (people_t *)pdata;
    pMan = pWoman->pMediator->pMan;
    
    printf("%s process %s's request.\n", pWoman->sex, pMan->sex);
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
