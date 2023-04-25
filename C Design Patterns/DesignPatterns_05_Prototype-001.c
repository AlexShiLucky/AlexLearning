/**
C���Ժ����ģʽ-<������>-<Prototype>-<ԭ��ģʽ>
��ͼ:
    ��ԭ��ʵ��ָ���������������,����ͨ��������Щԭ�ʹ����µĶ���.
������:
    ��Ҫʵ����������������ʱ��ָ��ʱ,����,ͨ����̬װ�أ�����
    Ϊ�˱��ⴴ��һ�����Ʒ����ƽ�еĹ�������ʱ������
    ��һ�����ʵ��ֻ���м�����ͬ״̬����е�һ��ʱ.������Ӧ��Ŀ��ԭ�Ͳ���¡���ǿ��ܱ�ÿ���ú��ʵ�״̬�ֹ�ʵ�������������һЩ.
*/
#include <stdio.h>

typedef struct _DATA {
    int value;
    struct _DATA *(copy)(struct _DATA *);
} DATA_t;

struct _DATA *data_copy_A(struct _DATA * pData)
{
    DATA_t *pResult = (DATA_t *)malloc(sizeof(DATA_t));
    assert(NULL != pResult);
    memmove(pResult, pData, sizeof(DATA_t));
    return pResult;
}

DATA_t data_A = {'A', data_copy_A};

struct _DATA *data_copy_B(struct _DATA * pData)
{
    DATA_t *pResult = (DATA_t *)malloc(sizeof(DATA_t));
    assert(NULL != pResult);
    memmove(pResult, pData, sizeof(DATA_t));
    return pResult;
}

DATA_t data_B = {'B', data_copy_B};

struct _DATA *clone(struct _DATA *pData)
{
    pData->copy(pData);
}

void destory(struct _DATA *pData)
{
    free(pData);
}

int main (int argc, char * argv[], char * envp[])
{
    DATA_t *pClone = NULL;
    
    pClone = clone(&data_A);
    pClone->value = 'X';
    printf("data_A value:%c\n", data_A.value);
    printf("cloneA value:%c\n", pClone->value);
    destory(pClone);

    pClone = clone(&data_B);
    printf("data_B value:%c\n", data_B.value);
    printf("cloneB value:%c\n", pClone->value);
    destory(pClone);

    return 0;
}
