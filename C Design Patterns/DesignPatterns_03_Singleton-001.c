/**
C语言和设计模式-<创建型>-<Singleton>-<单件模式>
意图:
    保证一个类仅有一个实例,并提供一个访问它的全局访问点.
适用性:
    当类只能有一个实例而且客户可以从一个众所周知的访问点访问它时.
    当这个唯一实例应该是通过子类化可扩展的,并且客户应该无需更改代码就能使用一个扩展的实例时.
*/
#include <stdio.h>

typedef struct _Singleton {
    int value;
} Singleton_t;

Singleton_t *getInstance(void)
{
    static Singleton_t *p = NULL;
    
    if (NULL != p) {
        return p;
    }
    
    p = (Singleton_t *)malloc(sizeof(Singleton_t));
    memset(p, 0, sizeof(Singleton_t));
    assert(NULL != p);
    return p;
}

int main (int argc, char * argv[], char * envp[])
{
    Singleton_t *pSingleton;
    
    pSingleton = getInstance();
    return 0;
}
