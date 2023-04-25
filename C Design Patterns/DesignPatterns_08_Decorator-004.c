/**
C语言和设计模式-<结构型>-<Decorator>-<装饰者模式>
意图:
    动态地给一个对象添加一些额外的职责.就增加功能来说,Decorator 模式相比生成子类更为灵活.
适用性:
    在不影响其他对象的情况下,以动态、透明的方式给单个对象添加职责.
    处理那些可以撤消的职责.
    当不能采用生成子类的方法进行扩充时.一种情况是,可能有大量独立的扩展,为支持每一种组合将产生大量的子类,使得子类数目呈爆炸性增长.另一种情况可能是因为类定义被隐藏,或类定义不能用于生成子类.
*/
#include <stdio.h>

typedef struct _object {
    struct _object *prev;

    void (*Method)(struct _object *pObject);
} object_t;

typedef struct _object1 {
    struct _object  object;
    void (*Method)(struct _object *pObject);
} object1_t;

typedef struct _object2 {
    struct _object  object;
    void (*Method)(struct _object *pObject);
} object2_t;

typedef struct _decorator {
    struct _object  object;
    void (*Method)(struct _object *pObject);
} decorator_t;



int main (int argc, char * argv[], char * envp[])
{
    return 0;
}
