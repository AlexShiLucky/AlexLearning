/**
C语言和设计模式-<结构型>-<Proxy>-<代理模式>
意图:
    为其他对象提供一种代理以控制对这个对象的访问.
适用性:
    在需要用比较通用和复杂的对象指针代替简单的指针的时候,使用Proxy模式.下面是一 些可以使用Proxy 模式常见情况:
    1) 远程代理(Remote Proxy (为一个对象在不同的地址空间提供局部代表. NEXTSTEP[Add94] 使用NXProxy 类实现了这一目的.Coplien[Cop92] 称这种代理为“大使” (Ambassador (.
    2) 虚代理(Virtual Proxy (根据需要创建开销很大的对象.在动机一节描述的ImageProxy 就是这样一种代理的例子.
    3) 保护代理(Protection Proxy (控制对原始对象的访问.保护代理用于对象应该有不同 的访问权限的时候.例如,在Choices 操作系统[ CIRM93]中KemelProxies为操作系统对象提供 了访问保护.
    4) 智能指引(Smart Reference (取代了简单的指针,它在访问对象时执行一些附加操作. 它的典型用途包括:
    对指向实际对象的引用计数,这样当该对象没有引用时,可以自动释放它(也称为SmartPointers[Ede92 ] ).
    当第一次引用一个持久对象时,将它装入内存.
    在访问一个实际对象前,检查是否已经锁定了它,以确保其他对象不能改变它.
*/
#include <stdio.h>

typedef struct _kind_woman {
    void (*make_eyes_with_man)(void);
    void (*happy_with_man)(void);
} kind_woman_t;

typedef struct _woman {
    struct _kind_woman woman;
} woman_t;

void pjl_make_eyes_with_man(void)
{
    printf("pan jin lian pao mei yan\n");
}

void pjl_happy_with_man(void)
{
    printf("pan jin lian happy with man\n");
}

void js_make_eyes_with_man(void)
{
    printf("jia shi pao mei yan\n");
}

void js_happy_with_man(void)
{
    printf("jia shi happy with man\n");
}

typedef struct _wang_po {
    struct _kind_woman *woman;
} wang_po_t;

void pan_jin_lian_init(woman_t *pPJL)
{
    memset(pPJL, 0, sizeof(woman_t));
    pPJL->woman.make_eyes_with_man = pjl_make_eyes_with_man;
    pPJL->woman.happy_with_man = pjl_happy_with_man;
}

void jia_shi_init(woman_t *pJS)
{
    memset(pJS, 0, sizeof(woman_t));
    pJS->woman.make_eyes_with_man = js_make_eyes_with_man;
    pJS->woman.happy_with_man = js_happy_with_man;
}

void wang_po_proxy(wang_po_t *pWP, kind_woman_t *pKW)
{
    pWP->woman = pKW;
}

int main (int argc, char * argv[], char * envp[])
{
    woman_t pan_jin_lian;
    woman_t jia_shi;
    wang_po_t wang_po;
    
    pan_jin_lian_init(&pan_jin_lian);
    wang_po_proxy(&wang_po, (kind_woman_t *)&pan_jin_lian);
    
    wang_po.woman->make_eyes_with_man();
    wang_po.woman->happy_with_man();
    
    jia_shi_init(&jia_shi);
    wang_po_proxy(&wang_po, (kind_woman_t *)&jia_shi);
    
    wang_po.woman->make_eyes_with_man();
    wang_po.woman->happy_with_man();
    return 0;
}
