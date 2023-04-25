/**
对指针的应用是C语言编程的精髓所在,而回调函数就是C语言里面对函数指针的高级应用.简而言之,回调函数是一个通过函数指针调用的函数.如果你把函数指针(函数的入口地址)传递给另一个函数,当这个函数指针被用来调用它所指向的函数时,我们就说这个函数是回调函数.
为什么要使用回调函数呢？我们先看一个小例子:
Node * Search_List (Node * node, const int value)
{
    while (node != NULL)
    {
        if (node -> value == value)
        {
            break;
        }
        node = node -> next;
    }
    return node;
}

这个函数用于在一个单向链表中查找一个指定的值,返回保存这个值的节点.它的参数是指向这个链表第一个节点的指针以及要查找的值.这个函数看上去很简单,但是我们考虑一个问题:它只能适用于值为整数的链表,如果查找一个字符串链表,我们不得不再写一个函数,其实大部分代码和现在这个函数相同,只是第二个参数的类型和比较的方法不同.

其实我们更希望令查找函数与类型无关,这样它就能用于查找存放任何类型值的链表了,因此必须改变比较的方式,而借助回调函数就可以达到这个目的.我们编写一个函数(回调函数),用于比较两个同类型的值,然后把一个指向这个函数的指针作为参数传递给查找函数,查找函数调用这个比较函数来执行比较,采用这个方法,任何类型的值得都可以进行比较.

我们还必须给查找函数传递一个指向待比较的值的指针而不是值本身,也就是一个void *类型的形参,这个指针会传递给回调函数,进行最终的比较.这样的修改可以让我们传递指向任何类型的指针到查找函数,从而完成对任何类型的比较,这就是指针的好处,我们无法将字符串、数组或者结构体作为参数传递给函数,但是指向它们的指针却可以.

现在,我们的查找函数就可以这样实现:
NODE *Search_List(NODE *node, int (*compare)(void const *, void const *) , \
void const *desired_value);
{
    while (node != NULL)
    {
        if (compare((node->value_address), desired_value) == 0)
        {
            break;
        }
        node = node->next;
    }
    return node;
}

可以看到,用户将一个函数指针传递给查找函数,后者将回调这个函数.

注意这里我们的链表节点是这样定义的:

typedef struct list
{
    void *value_address;
    struct list *next;
} NODE;

这样定义可以让NODE *类型的指针指向存储任何类型数据的链表节点.而value_address就是指向具体数据的指针,我们把它定义为void *,表示一个指向未知类型的指针,这样链表就可以存储任何类型的数据了,而我们传递给查找函数Search_List的第一个参数就可以统一表示为:NODE *,否则,还是要分别写查找函数以适应存储不同数据类型的链表.

现在,查找函数与类型无关,因为它不进行实际的比较,因此,我们必须编写针对不同类型的比较函数,这是很容易实现的,因为调用者知道链表中所包含的值的类型,如果创建几个分别包含不同类型值的链表,为每种类型编写一个比较函数就允许单个查找函数作用于所有类型的链表.

下面是一个比较函数,用于在一个整型链表中查找:

注意强制类型转换,比较函数的参数必须被声明为void *以匹配查找函数的原型,然后强制转换为(int *)类型用于比较整型.
int int_compare(void const *a, void const *b)
{
    if (*(int *)a == *(int *)b)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

这个函数可以这样被使用:

desired_node = Search_List(root, int_compare, &desired_int_value);

如果你希望在一个字符串链表中进行查找,下面的代码就可以完成任务:

desired_node = Search_List(root, strcmp, "abcdefg");

正好库函数strcmp所执行的比较和我们需要的一样,不过gcc会发出警告信息:因为strcmp的参数被声明为const char *而不是void const *.

上面的例子展示了回调函数的基本原理和用法,回调函数的应用是非常广泛的.通常,当我们想通过一个统一接口实现不同内容的时候,用回调函数来实现就非常合适.任何时候,如果你所编写的函数必须能够在不同的时刻执行不同的类型的工作或者执行只能由函数调用者定义的工作,你都可以用回调函数来实现.许多窗口系统就是使用回调函数连接多个动作,如拖拽鼠标和点击按钮来指定调用用户程序中的某个特定函数.
*/
/* main.c */
#include <stdio.h>

typedef int  (*cmp_t)(void*, void*);
typedef void (*tbl_t)(void*);

int cmp_int(int a, int b)
{
    if (a > b) return 1;
    else if (a == b) return 0;
    else return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
    const char *name;
    int id;
    int score;
} student_t;

int cmp_student(void* a, void* b)
{
    return cmp_int(((student_t *)a)->score, ((student_t *)b)->score);
}

void tbl_student(void *dat)
{
    printf("%d\t%s\t%d\r\n", ((student_t *)dat)->id, ((student_t *)dat)->name, ((student_t *)dat)->score);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
    const char *name;
    int id;
    int bonus;
} worker_t;

int cmp_worker(void* a, void* b)
{
    return cmp_int(((worker_t *)a)->bonus, ((worker_t *)b)->bonus);
}

void tbl_worker(void *dat)
{
    printf("%d\t%s\t%d\r\n", ((worker_t *)dat)->id, ((worker_t *)dat)->name, ((worker_t *)dat)->bonus);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void* max(void* data[], int num, cmp_t cmp)
{
    int   idx;
    void* temp = data[0];
    for (idx = 1; idx < num; idx++) {
        if (cmp(temp, data[idx]) < 0)
            temp = data[idx];
    }
    return temp;
}

void* min(void* data[], int num, cmp_t cmp)
{
    int   idx;
    void* temp = data[0];
    for (idx = 1; idx < num; idx++) {
        if (cmp(temp, data[idx]) > 0)
            temp = data[idx];
    }
    return temp;
}

void show_tbl(void *data[], int num, tbl_t tbl_ptf)
{
    int idx;
    for (idx = 0; idx < num; idx++) {
        tbl_ptf(data[idx]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ARR_SIZE(arr)   (sizeof(arr)/sizeof((arr)[0]))
int main(void)
{
    int idx;

    student_t   student_list[] = {{"Tom", 0, 68}, {"Jerry", 0, 98}, {"Moby", 0, 60}, {"Kirby", 0, 89}, {"Jim", 0, 72}};
    student_t *pstudent_list[ARR_SIZE(student_list)];

    for (idx = 0; idx < ARR_SIZE(student_list); idx++) {
        pstudent_list[idx] = &student_list[idx];
        pstudent_list[idx]->id = idx + 1;
    }

    printf("id\tname\tscore\r\n");
    printf("==\t====\t=====\r\n");
    show_tbl((void **)pstudent_list, ARR_SIZE(student_list), tbl_student);

    student_t *pstuent_max = max((void **)pstudent_list, ARR_SIZE(student_list), cmp_student);
    printf("%s(id:%d) gets the highest score %d.\r\n", pstuent_max->name, pstuent_max->id, pstuent_max->score);

    student_t *pstuent_min = min((void **)pstudent_list, ARR_SIZE(student_list), cmp_student);
    printf("%s(id:%d) gets the lowest score %d.\r\n",  pstuent_min->name, pstuent_min->id, pstuent_min->score);

    printf("============================================\r\n");

    worker_t   worker_list[] = {{"Tom", 0, 6800}, {"Jerry", 0, 9800}, {"Moby", 0, 6000}, {"Kirby", 0, 8900}, {"Jim", 0, 7200}, {"John", 0, 10000}};
    worker_t *pworker_list[ARR_SIZE(worker_list)];

    for (idx = 0; idx < ARR_SIZE(worker_list); idx++) {
        pworker_list[idx] = &worker_list[idx];
        pworker_list[idx]->id = idx + 1;
    }

    printf("id\tname\tbonus\r\n");
    printf("==\t====\t=====\r\n");
    show_tbl((void **)pworker_list, ARR_SIZE(worker_list), tbl_worker);

    worker_t *pworker_max = max((void **)pworker_list, ARR_SIZE(worker_list), cmp_worker);
    printf("%s(id:%d) gets the highest bonus %d.\r\n", pworker_max->name, pworker_max->id, pworker_max->bonus);

    worker_t *pworker_min = min((void **)pworker_list, ARR_SIZE(worker_list), cmp_worker);
    printf("%s(id:%d) gets the lowest bonus %d.\r\n",  pworker_min->name, pworker_min->id, pworker_min->bonus);

	getchar();
    return 0;
}
