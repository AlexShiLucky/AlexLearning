/**
C���Ժ����ģʽ-<��Ϊ��>-<Observer>-<�۲���ģʽ>
��ͼ:
    ���������һ��һ�Զ��������ϵ,��һ�������״̬�����ı�ʱ,�������������Ķ��󶼵õ�֪ͨ�����Զ�����.
������:
    ��һ������ģ������������,����һ��������������һ����.������߷�װ�ڶ����Ķ�������ʹ���ǿ��Ը��Զ����ظı�͸���.
    ����һ������ĸı���Ҫͬʱ�ı���������,����֪�������ж��ٶ����д��ı�.
    ��һ���������֪ͨ��������,�����ֲ��ܼٶ�����������˭.����֮,�㲻ϣ����Щ�����ǽ�����ϵ�.
*/
#include <stdio.h>

/*=========== ���Ͷ���(Observer��Subject) ===========*/
// �۲��߻ص�
typedef struct _observer {
    void (*update)(int);
} observer_t;

// �۲�������
typedef struct _observer_link {
    struct _observer_link *next;
    struct _observer *observer;
} observer_link_t;

// ���۲���
typedef struct _subject {
    int data;                        // ���۲�����
    struct _observer_link *list;     // �۲�������(����)
} subject_t;

/*=========== ����ͳ��(�۲��߸���) ===========*/
// 1.���� ���ͳ����ʾ
void update_form(int data)
{
    printf("Update Form:%d\n", data);
}

// 2.���� ��״ͼͳ����ʾ
void update_cylinder(int data)
{
    printf("Update Cylinder:%d\n", data);
}

// 3.���� �ٷֱ�ͳ����ʾ
void update_percent(int data)
{
    printf("Update Percent:%d\n", data);
}

// ��ʼ���۲���
void init_observer(observer_t *observer, void (*update)(int))
{
    observer->update = update;
}

// ����۲��߶���
int attach_observer(subject_t *subject, observer_t *observer)
{
    // ��observer����subject�е�observer����
    observer_link_t *node = subject->list;
    observer_link_t *new = (observer_link_t *)malloc(sizeof(observer_link_t));

    if (NULL == new) return 0;

    new->observer = observer;
    new->next = NULL;

    if (NULL == node) {
        subject->list = new;
    } else {
        while (NULL != node->next) {
            node = node->next;
        }
        node->next = new;
    }

    return 1;
}

// �ӹ۲��߶���ɾ��
int detach_observer(subject_t *subject, observer_t *observer)
{
    // ��observer�߳�subject�е�observer����
    observer_link_t *node = subject->list;
    observer_link_t **node_bak = &subject->list;
    
    while (NULL != node) {
        if (node->observer != observer) {
            node_bak = &node->next;
            node = node->next;
        } else {
            *node_bak = node->next;
            free(node);
            return 1;
        }
    }

    return 0;
}

// �޸ı��۲�����
void set_data(subject_t *subject, int value)
{
    subject->data = value;
}

// ֪ͨ�۲���
void notify_observer(subject_t *subject)
{
    observer_link_t *node = subject->list;

    while (NULL != node)
    {
        node->observer->update(subject->data);
        node = node->next;
    }
}

// ��ʼ���������
void init_subject(subject_t *subject)
{
    memset(subject, 0, sizeof(subject_t));
    subject->list = NULL;
}

/*=========== Observerģʽʹ�� ===========*/
int main(int argc, char * argv[], char * envp[])
{
    observer_t form;        // ������
    observer_t cylinder;    // ��״ͼ����
    observer_t percent;     // �ٷֱȶ���
    subject_t  subject;     // ͳ������

    // ��ʼ���۲���
    init_observer(&form,    update_form);
    init_observer(&cylinder,update_cylinder);
    init_observer(&percent, update_percent);

    // ��ʼ�����۲���
    init_subject(&subject);

    // �۲��߹�עsubject
    attach_observer(&subject, &form);
    attach_observer(&subject, &cylinder);
    attach_observer(&subject, &percent);

    // �޸�״̬,��֪ͨ�۲���
    set_data(&subject, 1);
    notify_observer(&subject);

    set_data(&subject, 2);
    notify_observer(&subject);
    
    detach_observer(&subject, &form);
    //detach_observer(&subject, &cylinder);
    //detach_observer(&subject, &percent);
    
    set_data(&subject, 1);
    notify_observer(&subject);

    return 0;
}
