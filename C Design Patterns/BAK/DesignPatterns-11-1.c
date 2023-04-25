// C语言和设计模式(观察者模式)
#include <stdio.h>

typedef struct _object
{
    struct _observer *pObserverList[MAX_BINDING_NUMBER];
    int number;

    void (*notify)(struct _object *pObject);
    void (*add_observer)(struct _observer *pObserver);
    void (*del_observer)(struct _observer *pObserver);
} object_t;

typedef struct _observer
{
    struct _object *pObject;

    void (*update)(struct _observer *pObserver);
} observer_t;

void bind_observer_to_object(observer_t *pObserver, object_t *pObject)
{
    //assert(NULL != pObserver && NULL != pObject);

    pObserver->pObject = pObject;
    pObject->add_observer(pObserver);
}      

void unbind_observer_from_object(observer_t *pObserver, object_t *pObject)
{
    //assert(NULL != pObserver && NULL != pObject);

    pObject->del_observer(pObserver);
    memset(pObserver, 0, sizeof(observer_t));
}

void notify(object_t *pObject)
{
    observer_t *pObserver;
    int idx;

    //assert(NULL != pObject);
    for(idx = 0; idx < pObject->number; idx++)
    {
        pObserver = pObjecet->pObserverList[index];
        pObserver->update(pObserver);
    }
}

int main(void)
{
    dumpling_type_t idx;
    
    for (idx = TYPE_MEAT; idx < TYPE_Unknown; idx++) {
        buy_dumpling(dumpling_request+idx);
    }

    return 0;
}
