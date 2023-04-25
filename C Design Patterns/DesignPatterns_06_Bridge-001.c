/**
C语言和设计模式-<结构型>-<Bridge>-<桥接模式>
意图:
    将抽象部分与它的实现部分分离,使它们都可以独立地变化.
适用性:
    你不希望在抽象和它的实现部分之间有一个固定的绑定关系.例如这种情况可能是因为,在程序运行时刻实现部分应可以被选择或者切换.
    类的抽象以及它的实现都应该可以通过生成子类的方法加以扩充.这时Bridge 模式使你可以对不同的抽象接口和实现部分进行组合,并分别对它们进行扩充.
    对一个抽象的实现部分的修改应对客户不产生影响,即客户的代码不必重新编译.
    (C++(你想对客户完全隐藏抽象的实现部分.在C++中,类的表示在类接口中是可见的.
    有许多类要生成.这样一种类层次结构说明你必须将一个对象分解成两个部分.Rumbaugh 称这种类层次结构为“嵌套的普化”(nested generalizations (.
    你想在多个对象间共享实现(可能使用引用计数(,但同时要求客户并不知道这一点.一个简单的例子便是Coplien 的String 类[ Cop92 ],在这个类中多个对象可以共享同一个字符串表示(StringRep (.
*/
#include <stdio.h>

typedef enum _dumpling_type {
    TYPE_MEAT   = 0,
    TYPE_NORMAL = 1,
    TYPE_Unknown
} dumpling_type_t;

typedef struct _meat_dumpling {
    void (*make)(void);
} meat_dumpling_t;

typedef struct _normal_dumpling {
    void (*make)(void);
} normal_dumpling_t;

typedef struct _dumpling_reuqest {
    enum _dumpling_type type;
    void *pDumpling;   
} dumpling_request_t;

void buy_dumpling(dumpling_request_t *pDumplingRequest)
{
    //assert(NULL != pDumplingRequest);

    if (TYPE_MEAT == pDumplingRequest->type)
        return ((meat_dumpling_t *)(pDumplingRequest->pDumpling))->make();
    else
        return ((normal_dumpling_t *)(pDumplingRequest->pDumpling))->make();
} 

void make_meat_dumpling(void)
{
    printf("make meat dumpling\n");
}

void make_normal_dumpling(void)
{
    printf("make normal dumpling\n");
}

static dumpling_request_t dumpling_request[] = {
    [0] = {
        .type = TYPE_MEAT,
        .pDumpling = &(meat_dumpling_t){ .make = make_meat_dumpling }
    },
    [1] = {
        .type = TYPE_NORMAL,
        .pDumpling = &(normal_dumpling_t){ .make = make_normal_dumpling }
    }
};

int main (int argc, char * argv[], char * envp[])
{
    dumpling_type_t idx;
    
    for (idx = TYPE_MEAT; idx < TYPE_Unknown; idx++) {
        buy_dumpling(dumpling_request+idx);
    }

    return 0;
}
