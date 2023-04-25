/**
C语言和设计模式-<创建型>-<Prototype>-<原型模式>
意图:
    用原型实例指定创建对象的种类,并且通过拷贝这些原型创建新的对象.
适用性:
    当要实例化的类是在运行时刻指定时,例如,通过动态装载；或者
    为了避免创建一个与产品类层次平行的工厂类层次时；或者
    当一个类的实例只能有几个不同状态组合中的一种时.建立相应数目的原型并克隆它们可能比每次用合适的状态手工实例化该类更方便一些.
*/
#include <stdio.h>

typedef struct _DATA {
    int value;
    struct _DATA *(copy)(struct _DATA *);
} DATA_t;

struct _DATA *data_copy_A(struct _DATA * pData)
{
    DATA_t *pResult = (DATA_t *)malloc(sizeof(DATA_t));
    assert(NULL != pResult);
    memmove(pResult, pData, sizeof(DATA_t));
    return pResult;
}

DATA_t data_A = {'A', data_copy_A};

struct _DATA *data_copy_B(struct _DATA * pData)
{
    DATA_t *pResult = (DATA_t *)malloc(sizeof(DATA_t));
    assert(NULL != pResult);
    memmove(pResult, pData, sizeof(DATA_t));
    return pResult;
}

DATA_t data_B = {'B', data_copy_B};

struct _DATA *clone(struct _DATA *pData)
{
    pData->copy(pData);
}

void destory(struct _DATA *pData)
{
    free(pData);
}

int main (int argc, char * argv[], char * envp[])
{
    DATA_t *pClone = NULL;
    
    pClone = clone(&data_A);
    pClone->value = 'X';
    printf("data_A value:%c\n", data_A.value);
    printf("cloneA value:%c\n", pClone->value);
    destory(pClone);

    pClone = clone(&data_B);
    printf("data_B value:%c\n", data_B.value);
    printf("cloneB value:%c\n", pClone->value);
    destory(pClone);

    return 0;
}
