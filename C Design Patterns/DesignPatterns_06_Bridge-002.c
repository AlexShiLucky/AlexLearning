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

static void make_meat_dumpling(void *pdata, int num);
static void make_normal_dumpling(void *pdata, int num);

typedef enum _dumpling_type {
    TYPE_MEAT   = 0,
    TYPE_NORMAL = 1,
    TYPE_Unknown
} dumpling_type_t;

typedef struct _dumpling {
    char *name;
    void (*make)(void *, int);
} dumpling_t;

typedef struct _dumpling_reuqest {
    enum _dumpling_type type;
    void *pDumpling;
} dumpling_request_t;

static const dumpling_request_t dumpling_request[] = {
    [0] = {
        .type = TYPE_MEAT,
        .pDumpling = &(dumpling_t){ .name = "meat", .make = make_meat_dumpling }
    },
    [1] = {
        .type = TYPE_NORMAL,
        .pDumpling = &(dumpling_t){ .name = "normal", .make = make_normal_dumpling }
    }
};

void buy_dumpling(dumpling_type_t type, int num)
{
    dumpling_t *pDumpling;

    pDumpling = (dumpling_t *)dumpling_request[type].pDumpling;
    pDumpling->make(pDumpling, num);
    printf("dumpling ok\n");
}

static void make_meat_dumpling(void *pdata, int num)
{
    dumpling_t *pDumpling;

    pDumpling = (dumpling_t *)pdata;
    printf("make %s dumpling:%d\n", pDumpling->name, num);
}

static void make_normal_dumpling(void *pdata, int num)
{
    dumpling_t *pDumpling;

    pDumpling = (dumpling_t *)pdata;
    printf("make %s dumpling:%d\n", pDumpling->name, num);
}

int main (int argc, char * argv[], char * envp[])
{
    buy_dumpling(TYPE_MEAT, 10);

    buy_dumpling(TYPE_NORMAL, 20);

    return 0;
}
