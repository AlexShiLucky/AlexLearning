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

#define MAX_BINDING_NUMBER  10

typedef struct _object
{
    struct _observer *pObserverList[MAX_BINDING_NUMBER];
    int number;

    int data;
    void (*notify)(struct _object *pObject);
    int  (*add_observer)(struct _observer *pObserver);
    int  (*del_observer)(struct _observer *pObserver);
} object_t;

typedef struct _observer
{
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
    object_t *pObject = pObserver->pObject;
    
    if (pObject->number + 1 < MAX_BINDING_NUMBER) {
        pObject->pObserverList[pObject->number] = pObserver;
        pObject->number++;
        return 1;
    }

    return 0;
}

// 从观察者队列删除
void unbind_observer_from_object(object_t *pObject, observer_t *pObserver)
{
    //assert(NULL != pObserver && NULL != pObject);

    pObject->del_observer(pObserver);
    memset(pObserver,0,sizeof(observer_t));
}

int del_observer(observer_t *pObserver)
{
    int idx = 0;
    object_t *pObject = pObserver->pObject;
    
    while (idx < pObject->number) {
        if (pObject->pObserverList[idx] == pObserver) {
            while (idx+1 < pObject->number) {
                pObject->pObserverList[idx] = pObject->pObserverList[idx+1];
                idx++;
            }
            pObject->pObserverList[idx] = NULL;
            pObject->number--;
            return 1;
        } else {
            idx++;
        }
    }

    return 0;
}

// 修改被观察数据
void set_data(object_t *pObject, int value)
{
    if (pObject->data != value) {
        pObject->data = value;
        pObject->notify(pObject);
    }
}

// 通知观察者
void notify_observer(object_t *pObject)
{
    int idx = 0;
    observer_t *pObserver;

    //assert(NULL != pObject);
    while (idx < pObject->number) {
        pObserver = pObject->pObserverList[idx++];
        pObserver->update(pObserver);
    }
}

// 初始化主题对象
void init_object(object_t *pObject)
{
    memset(pObject,0,sizeof(object_t));
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
