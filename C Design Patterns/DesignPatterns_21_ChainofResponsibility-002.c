/**
C语言和设计模式-<行为型>-<Chain of Responsibility>-<责任链模式>
意图:
    使多个对象都有机会处理请求,从而避免请求的发送者和接收者之间的耦合关系.
    将这些对象连成一条链,并沿着这条链传递该请求,直到有一个对象处理它为止.
适用性:
    有多个的对象可以处理一个请求,哪个对象处理该请求运行时刻自动确定.
    你想在不明确指定接收者的情况下,向多个对象中的一个提交一个请求.
    可处理一个请求的对象集合应被动态指定.
*/
#include <stdio.h>

typedef enum _woman_type {
    TYPE_Daughter   = 0,
    TYPE_Wife       = 1,
    TYPE_Mother     = 2
} woman_type;

static const struct {
    char *woman;
    char *man;
} type_tbl[] = {
    {"女儿", "父亲"},
    {"妻子", "丈夫"},
    {"母亲", "儿子"}
};

struct _woman;

typedef struct _handler {
    struct _handler *next;
    int level;

    void (*response)(struct _handler *, struct _woman *);
} handler_t;

typedef struct _woman {
    int   type;
    char *request;
} woman_t;

int handle_message(handler_t *pHandler, woman_t *pWoman)
{
    if (pWoman->type == pHandler->level) {
        pHandler->response(pHandler, pWoman);
        return 1;
    } else if (NULL != pHandler->next) {
        return handle_message(pHandler->next, pWoman);
    } else {
        return 0;
    }
}

void set_next(handler_t *pHandler, handler_t *next)
{
    pHandler->next = next;
}

void response(handler_t *pHandler, woman_t *pWoman)
{
    printf("------ %s向%s请示 ------\n", type_tbl[pWoman->type].woman, type_tbl[pWoman->type].man);
    printf("%s的请求是: %s\n", type_tbl[pWoman->type].woman, pWoman->request);
    printf("%s的答复是: 同意\n", type_tbl[pWoman->type].man);
}

void woman_init(woman_t *pWoman, int type, char *request)
{
    pWoman->type    = type;
    pWoman->request = request;
}

void handler_init(handler_t *pHandler, int level, void (*response)(struct _handler *, struct _woman *))
{
    pHandler->level    = level;
    pHandler->response = response;
}

int main (int argc, char * argv[], char * envp[])
{
    woman_t woman;
    handler_t father, husband, son;
    
    handler_init(&father,  TYPE_Daughter, response);
    handler_init(&husband, TYPE_Wife,     response);
    handler_init(&son,     TYPE_Mother,   response);
    
    set_next(&father,  &husband);
    set_next(&husband, &son);
    set_next(&son,     NULL);

    woman_init(&woman, TYPE_Wife, "我要出去逛街");
    handle_message(&father, &woman);

    woman_init(&woman, TYPE_Daughter, "我要买玩具");
    handle_message(&father, &woman);

    woman_init(&woman, TYPE_Mother, "我要烧午饭");
    handle_message(&father, &woman);

    return 0;
}
