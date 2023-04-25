/**
C语言和设计模式-<行为型>-<Observer>-<观察者模式>
意图:
    定义对象间的一种一对多的依赖关系,当一个对象的状态发生改变时,所有依赖于它的对象都得到通知并被自动更新.
适用性:
    当一个抽象模型有两个方面,其中一个方面依赖于另一方面.将这二者封装在独立的对象中以使它们可以各自独立地改变和复用.
    当对一个对象的改变需要同时改变其它对象,而不知道具体有多少对象有待改变.
    当一个对象必须通知其它对象,而它又不能假定其它对象是谁.换言之,你不希望这些对象是紧密耦合的.
*/
#include <stdio.h>

typedef struct _list {
    struct _list *next;
} list_t;

#define list_entry(list, type, member) \
    ((type *)((char *)(list) - (char *)(&((type *)0)->member)))

struct _observer;

typedef struct _object {
    struct _list *head;

    int data;
    void (*notify)(struct _object *pObject);
    int  (*add_observer)(struct _observer *pObserver);
    int  (*del_observer)(struct _observer *pObserver);
} object_t;

typedef struct _observer {
    struct _list    list;
    struct _object *pObject;

    void (*update)(void *pdata);
} observer_t;

/*=========== 更新统计(观察者更新) ===========*/
// 1.更新 表格统计显示
void update_form(void *pdata)
{
    object_t *pObject = ((observer_t *)pdata)->pObject;

    printf("Update Form:%d\n", pObject->data);
}

// 2.更新 柱状图统计显示
void update_cylinder(void *pdata)
{
    object_t *pObject = ((observer_t *)pdata)->pObject;

    printf("Update Cylinder:%d\n", pObject->data);
}

// 3.更新 百分比统计显示
void update_percent(void *pdata)
{
    object_t *pObject = ((observer_t *)pdata)->pObject;

    printf("Update Percent:%d\n", pObject->data);
}

// 初始化观察者
void init_observer(observer_t *pObserver, void (*update)(void *))
{
    memset(pObserver, 0, sizeof(observer_t));
    pObserver->update = update;
}

// 加入观察者队列
void bind_observer_to_object(object_t *pObject, observer_t *pObserver)
{
    //assert(NULL != pObserver && NULL != pObject);

    pObserver->pObject = pObject;
    pObject->add_observer(pObserver);
}

int add_observer(observer_t *pObserver)
{
    list_t *pList = pObserver->pObject->head;

    if (NULL == pList) {
        pObserver->pObject->head = &pObserver->list;
        pObserver->list.next = NULL;
    } else {
        while (NULL != pList->next) {
            pList = pList->next;
        }
        pObserver->list.next = NULL;
        pList->next = &pObserver->list;
    }

    return 1;
}

// 从观察者队列删除
void unbind_observer_from_object(object_t *pObject, observer_t *pObserver)
{
    //assert(NULL != pObserver && NULL != pObject);

    pObject->del_observer(pObserver);
    memset(pObserver, 0, sizeof(observer_t));
}

int del_observer(observer_t *pObserver)
{
    list_t *pList = pObserver->pObject->head;
    list_t **ppList = &pObserver->pObject->head;

    while (NULL != pList) {
        if (list_entry(pList, observer_t, list) != pObserver) {
            ppList = &pList->next;
            pList  = pList->next;
        } else {
            *ppList = pList->next;
            break;
        }
    }

    return 1;
}

// 修改被观察数据
void set_data(object_t *pObject, int value)
{
    pObject->data = value;
    pObject->notify(pObject);
}

// 通知观察者
void notify_observer(object_t *pObject)
{
    list_t *pList = pObject->head;
    observer_t *pObserver;

    //assert(NULL != pObject);
    while (NULL != pList) {
        pObserver = list_entry(pList, observer_t, list);
        pObserver->update(pObserver);
        pList = pList->next;
    }
}

// 初始化主题对象
void init_object(object_t *pObject)
{
    memset(pObject, 0, sizeof(object_t));
    pObject->notify = notify_observer;
    pObject->add_observer = add_observer;
    pObject->del_observer = del_observer;
}

int main (int argc, char * argv[], char * envp[])
{
    observer_t form;        // 表格对象
    observer_t cylinder;    // 柱状图对象
    observer_t percent;     // 百分比对象
    object_t   object;      // 统计数据

    // 初始化观察者
    init_observer(&form,    update_form);
    init_observer(&cylinder,update_cylinder);
    init_observer(&percent, update_percent);

    // 初始化被观察者
    init_object(&object);

    // 观察者关注object
    bind_observer_to_object(&object, &form);
    bind_observer_to_object(&object, &cylinder);
    bind_observer_to_object(&object, &percent);

    // 修改状态,并通知观察者
    set_data(&object, 1);

    set_data(&object, 2);

    //unbind_observer_from_object(&object, &form);
    unbind_observer_from_object(&object, &cylinder);
    //unbind_observer_from_object(&object, &percent);

    set_data(&object, 1);
    return 0;
}
