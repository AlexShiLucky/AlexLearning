/**
C语言和设计模式-<行为型>-<Observer>-<观察者模式>
意图:
    定义对象间的一种一对多的依赖关系, 当一个对象的状态发生改变时, 所有依赖于它的对象都得到通知并被自动更新.
适用性:
    当一个抽象模型有两个方面, 其中一个方面依赖于另一方面.将这二者封装在独立的对象中以使它们可以各自独立地改变和复用.
    当对一个对象的改变需要同时改变其它对象, 而不知道具体有多少对象有待改变.
    当一个对象必须通知其它对象, 而它又不能假定其它对象是谁.换言之, 你不希望这些对象是紧密耦合的.
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
    blog.name = "【GOF设计模式之路】-- Observer";

    register_listener(listener1);
    register_listener(listener2);

    dispatcher(&blog);

    printf("\n");
    unregister_listener(listener1);

    dispatcher(&blog);

    return 0;
}
