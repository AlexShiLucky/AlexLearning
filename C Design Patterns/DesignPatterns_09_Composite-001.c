/**
C语言和设计模式-<结构型>-<Composite>-<组合模式>
意图:
    将对象组合成树形结构以表示“部分-整体”的层次结构.C o m p o s i t e 使得用户对单个对象和组合对象的使用具有一致性.
适用性:
    你想表示对象的部分-整体层次结构.
    你希望用户忽略组合对象与单个对象的不同,用户将统一地使用组合结构中的所有对象.
*/
#include <stdio.h>

typedef struct _Object {
    struct _Object** ppObject;
    int number;
    void (*operate)(struct _Object* pObject);
} Object_t;

void operate_of_parent(struct _Object* pObject)
{
    int index;
    assert(NULL != pObject);
    assert(NULL != pObject->ppObject && 0 != pObject->number);

    for(index = 0; index < pObject->number; index++) {
        pObject->ppObject[index]->operate(pObject->ppObject[index]);
    }
}

void operate_of_child(struct _Object* pObject)
{
    assert(NULL != pObject);
    printf("child node!\n");
}

void process(struct Object* pObject)
{
    assert(NULL != pObject);
    pObject->operate(pObject);
}

int main (int argc, char * argv[], char * envp[])
{
    return 0;
}
