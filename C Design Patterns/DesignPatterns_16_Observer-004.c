/**
C���Ժ����ģʽ-<��Ϊ��>-<Observer>-<�۲���ģʽ>
��ͼ:
    ���������һ��һ�Զ��������ϵ, ��һ�������״̬�����ı�ʱ, �������������Ķ��󶼵õ�֪ͨ�����Զ�����.
������:
    ��һ������ģ������������, ����һ��������������һ����.������߷�װ�ڶ����Ķ�������ʹ���ǿ��Ը��Զ����ظı�͸���.
    ����һ������ĸı���Ҫͬʱ�ı���������, ����֪�������ж��ٶ����д��ı�.
    ��һ���������֪ͨ��������, �����ֲ��ܼٶ�����������˭.����֮, �㲻ϣ����Щ�����ǽ�����ϵ�.
*/
#include <stdio.h>

#define MAX_LISTENERS 20
typedef int (*Listener)(void *);

Listener listeners[MAX_LISTENERS];

typedef struct _publisher {
    char *publisher;
    char *name;
} publisher_t;

void register_listener(Listener listen)
{
    int idx;

    for (idx = 0; idx < MAX_LISTENERS; ++idx)
    {
        if (listeners[idx] == NULL) {
            listeners[idx] = listen;
            break;
        }
    }
}

void unregister_listener(Listener listen)
{
    int idx;

    for (idx = 0; idx < MAX_LISTENERS; ++idx)
    {
        if (listeners[idx] == listen) {
            listeners[idx] = NULL;
            break;
        }
    }
}

void dispatcher(publisher_t *p)
{
    int idx;
    
    for (idx = 0; idx < MAX_LISTENERS; ++idx)
    {
        if (listeners[idx ] != NULL && !listeners[idx](p)) { 
            break;
        }
    }
}

int listener1(void *pdata)
{
    publisher_t *p = (publisher_t *)pdata;

    printf("Listener1: %s - %s\n", p->publisher, p->name);
    return 1;
}

int listener2(void* pdata)
{
    publisher_t *p = (publisher_t *)pdata;

    printf("Listener2: %s - %s\n", p->publisher, p->name);
    return 1;
}

int main (int argc, char * argv[], char * envp[])
{
    publisher_t blog;
    blog.publisher = "masefee";
    blog.name = "��GOF���ģʽ֮·��-- Observer";

    register_listener(listener1);
    register_listener(listener2);

    dispatcher(&blog);

    printf("\n");
    unregister_listener(listener1);

    dispatcher(&blog);

    return 0;
}
