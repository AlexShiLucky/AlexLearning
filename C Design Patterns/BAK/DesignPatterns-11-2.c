#include <stdio.h>

/*=========== 类型定义(Observer和Subject) ===========*/
// 观察者回调
typedef struct _observer {
    void (*update)(int);
} observer_t;

// 观察者链表
typedef struct _observer_link {
    struct _observer_link *next;
    struct _observer *observer;
} observer_link_t;

// 被观察者
typedef struct _subject {
    int data;                        // 被观察数据
    struct _observer_link *list;     // 观察者链表(队列)
} subject_t;

/*=========== 更新统计(观察者更新) ===========*/
// 1.更新 表格统计显示
void update_form(int data)
{
    printf("Update Form:%d\n", data);
}

// 2.更新 柱状图统计显示
void update_cylinder(int data)
{
    printf("Update Cylinder:%d\n", data);
}

// 3.更新 百分比统计显示
void update_percent(int data)
{
    printf("Update Percent:%d\n", data);
}

// 初始化观察者
void init_observer(observer_t *observer, void (*update)(int))
{
    observer->update = update;
}

// 加入观察者队列
int attach_observer(subject_t *subject, observer_t *observer)
{
    // 将observer加入subject中的observer链表
    observer_link_t *node = subject->list;
    observer_link_t *new_node = (observer_link_t *)malloc(sizeof(observer_link_t));

    if (NULL == new_node) return 0;
    printf("new_node addr:0x%08X\n", (unsigned int)new_node);
    new_node->observer = observer;
    new_node->next = NULL;

    if (NULL == node) {
        subject->list = new_node;
    } else {
        while (NULL != node->next) {
            node = node->next;
        }
        node->next = new_node;
    }

    return 1;
}

// 从观察者队列删除
int detach_observer(subject_t *subject, observer_t *observer)
{
    // 将observer踢出subject中的observer链表
    #if 0
    observer_link_t *node = subject->list;
    observer_link_t **node_bak = &subject->list;
    
    while (NULL != node) {
        if (node->observer != observer) {
            node_bak = &node->next;
            node = node->next;
        } else {
            *node_bak = node->next;
            printf("free_node addr:0x%08X\n", (unsigned int)node);
            free(node);
            return 1;
        }
    }
    #else
    observer_link_t **node = &subject->list;
    
    if (NULL == *node) return 0;
    
    while (NULL != *node) {
        if ((*node)->observer != observer) {
            node = &(*node);
        } else {
            *node = (*node)->next;
            printf("free_node addr:0x%08X\n", (unsigned int)(*node));
            free(*node);
            return 1;
        }
    }
    #endif

    return 0;
}

// 修改被观察数据
int set_data(subject_t *subject, int value)
{
    subject->data = value;
}

// 通知观察者
void notify_observer(subject_t *subject)
{
    observer_link_t *node = subject->list;

    while (NULL != node)
    {
        node->observer->update(subject->data);
        node = node->next;
    }
}

// 初始化主题对象
void init_subject(subject_t *subject)
{
    memset(subject, 0, sizeof(subject_t));
    subject->list = NULL;
}

/*=========== Observer模式使用 ===========*/
int main(int argc, const char *agrc[])
{
    observer_t form;        // 表格对象
    observer_t cylinder;    // 柱状图对象
    observer_t percent;     // 百分比对象
    subject_t  subject;     // 统计数据

    // 初始化观察者
    init_observer(&form,     update_form);
    init_observer(&cylinder, update_cylinder);
    init_observer(&percent,  update_percent);

    // 初始化被观察者
    init_subject(&subject);

    // 观察者关注subject
    attach_observer(&subject, &form);
    attach_observer(&subject, &cylinder);
    attach_observer(&subject, &percent);

    // 修改状态,并通知观察者
    set_data(&subject, 1);
    notify_observer(&subject);

    set_data(&subject, 2);
    notify_observer(&subject);
    
    //detach_observer(&subject, &form);
    //detach_observer(&subject, &cylinder);
    detach_observer(&subject, &percent);
    
    set_data(&subject, 1);
    notify_observer(&subject);

    return 0;
}
