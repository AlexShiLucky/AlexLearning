/**
C���Ժ����ģʽ-<�ṹ��>-<Decorator>-<װ����ģʽ>
��ͼ:
    ��̬�ظ�һ���������һЩ�����ְ��.�����ӹ�����˵,Decorator ģʽ������������Ϊ���.
������:
    �ڲ�Ӱ����������������,�Զ�̬��͸���ķ�ʽ�������������ְ��.
    ������Щ���Գ�����ְ��.
    �����ܲ�����������ķ�����������ʱ.һ�������,�����д�����������չ,Ϊ֧��ÿһ����Ͻ���������������,ʹ��������Ŀ�ʱ�ը������.��һ�������������Ϊ�ඨ�屻����,���ඨ�岻��������������.
*/
#include <stdio.h>

typedef struct _object {
    struct _object *prev;

    void (*decorate)(struct _object *pObject);
} object_t;

void decorate1(object_t *pObject)
{
    //assert(NULL != pObject);

    if (NULL != pObject->prev) {
        pObject->prev->decorate(pObject->prev);
    }

    printf("decorate-1\n");
}

void decorate2(object_t *pObject)
{
    //assert(NULL != pObject);

    if (NULL != pObject->prev) {
        pObject->prev->decorate(pObject->prev);
    }

    printf("decorate-2\n");
}

void decorate3(object_t *pObject)
{
    //assert(NULL != pObject);

    if (NULL != pObject->prev) {
        pObject->prev->decorate(pObject->prev);
    }

    printf("decorate-3\n");
}

static object_t object1 = {NULL,     decorate1};
static object_t object2 = {&object1, decorate2};
static object_t object  = {&object2, decorate3};

int main (int argc, char * argv[], char * envp[])
{
    object.decorate(&object);
    return 0;
}
