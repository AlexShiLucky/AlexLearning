/**
C���Ժ����ģʽ-<�ṹ��>-<Composite>-<���ģʽ>
��ͼ:
    ��������ϳ����νṹ�Ա�ʾ������-���塱�Ĳ�νṹ.C o m p o s i t e ʹ���û��Ե����������϶����ʹ�þ���һ����.
������:
    �����ʾ����Ĳ���-�����νṹ.
    ��ϣ���û�������϶����뵥������Ĳ�ͬ,�û���ͳһ��ʹ����Ͻṹ�е����ж���.
*/
#include <stdio.h>

typedef struct _Object {
    struct _Object** ppObject;
    int number;
    void (*operate)(struct _Object* pObject);
} Object_t;

void operate_of_parent(struct _Object* pObject)
{
    int index;
    assert(NULL != pObject);
    assert(NULL != pObject->ppObject && 0 != pObject->number);

    for(index = 0; index < pObject->number; index++) {
        pObject->ppObject[index]->operate(pObject->ppObject[index]);
    }
}

void operate_of_child(struct _Object* pObject)
{
    assert(NULL != pObject);
    printf("child node!\n");
}

void process(struct Object* pObject)
{
    assert(NULL != pObject);
    pObject->operate(pObject);
}

int main (int argc, char * argv[], char * envp[])
{
    return 0;
}
