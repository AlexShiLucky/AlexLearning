/**
C���Ժ����ģʽ-<��Ϊ��>-<Chain of Responsibility>-<������ģʽ>
��ͼ:
    ʹ��������л��ᴦ������,�Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ.
    ����Щ��������һ����,���������������ݸ�����,ֱ����һ����������Ϊֹ.
������:
    �ж���Ķ�����Դ���һ������,�ĸ����������������ʱ���Զ�ȷ��.
    �����ڲ���ȷָ�������ߵ������,���������е�һ���ύһ������.
    �ɴ���һ������Ķ��󼯺�Ӧ����ָ̬��.
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
    {"Ů��", "����"},
    {"����", "�ɷ�"},
    {"ĸ��", "����"}
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
    printf("------ %s��%s��ʾ ------\n", type_tbl[pWoman->type].woman, type_tbl[pWoman->type].man);
    printf("%s��������: %s\n", type_tbl[pWoman->type].woman, pWoman->request);
    printf("%s�Ĵ���: ͬ��\n", type_tbl[pWoman->type].man);
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

    woman_init(&woman, TYPE_Wife, "��Ҫ��ȥ���");
    handle_message(&father, &woman);

    woman_init(&woman, TYPE_Daughter, "��Ҫ�����");
    handle_message(&father, &woman);

    woman_init(&woman, TYPE_Mother, "��Ҫ���緹");
    handle_message(&father, &woman);

    return 0;
}
