#include <stdio.h>

#if ASSERT_EN
#define ASSERT(assertion) do { if(!(assertion)) \
    printf("(%s) assert failed at %s:%d \r\n", #assertion, __FUNCTION__, __LINE__); } while(0)
#else  /* ASSERT_EN */
#define ASSERT(assertion)
#endif /* ASSERT_EN */

#define struct_entry(self, type, member) \
    ((type *)((char *)(self) - (char *)(&((type *)0)->member)))

/*  抽象父类  */
struct parent_class {
    int a;
    /*  反映不同类别属性的方法  */
    void (*vfunc)(struct parent_class* self, int a);
};

/*  抽象父类的方法调用  */
void parent_class_vfunc(struct parent_class *self, int a)
{
    ASSERT(self != NULL);
    ASSERT(slef->vfunc != NULL);

    /*  调用对象本身的虚拟函数  */
    self->vfunc(self, a);
}

/*  抽象父类的虚拟函数的实现  */
static void _parent_vfunc(struct parent_class* self, int a)
{
    ASSERT(self != NULL);

    self->a += a;
    /*  输出相应的信息  */
    printf("parent's a=%d\n", self->a);
}

/*  抽象父类的构造函数,将成员变量赋值和虚拟函数绑定实现  */
void parent_class_init(struct parent_class* self)
{
    ASSERT(self != NULL);

    self->a = 1;
    self->vfunc = _parent_vfunc;
}

/*  继承自 parent_class 的子类  */
struct child_class
{
    int b;
    struct parent_class parent;
};

/*  子类的虚拟函数实现  */
static void _child_class_vfunc(struct parent_class* self, int a)
{
    struct child_class *child = struct_entry(self, struct child_class, parent);

    child->b = a + 10;
    /*  输出相应的信息  */
    printf("child's b=%d\n", child->b);
}

/*  子类的构造函数  */
void child_class_init(struct child_class* self)
{
    struct parent_class* parent;

    /*  强制类型转换获得父类指针  */
    parent = (struct parent_class*) &self->parent;
    ASSERT(parent != NULL);
    /*  设置子类的虚拟函数  */
    parent->vfunc = _child_class_vfunc;
}

void obj_test()
{
    struct parent_class *ptr;

    struct parent_class parent;
    struct child_class  child_a;
    struct child_class  child_b;
    struct child_class  child_c;

    parent_class_init(&parent);
    child_class_init(&child_a);
    child_class_init(&child_b);
    child_class_init(&child_c);

    ptr = (struct parent_class *)&parent;
    parent_class_vfunc(ptr, 10);

    ptr = (struct parent_class *)&child_a.parent;
    parent_class_vfunc(ptr, 20);

    ptr = (struct parent_class *)&child_b.parent;
    parent_class_vfunc(ptr, 30);

    ptr = (struct parent_class *)&child_c.parent;
    parent_class_vfunc(ptr, 40);
}

int main(void)
{
    obj_test();
    return 0;
}


