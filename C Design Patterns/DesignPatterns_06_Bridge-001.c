/**
C���Ժ����ģʽ-<�ṹ��>-<Bridge>-<�Ž�ģʽ>
��ͼ:
    �����󲿷�������ʵ�ֲ��ַ���,ʹ���Ƕ����Զ����ر仯.
������:
    �㲻ϣ���ڳ��������ʵ�ֲ���֮����һ���̶��İ󶨹�ϵ.�������������������Ϊ,�ڳ�������ʱ��ʵ�ֲ���Ӧ���Ա�ѡ������л�.
    ��ĳ����Լ�����ʵ�ֶ�Ӧ�ÿ���ͨ����������ķ�����������.��ʱBridge ģʽʹ����ԶԲ�ͬ�ĳ���ӿں�ʵ�ֲ��ֽ������,���ֱ�����ǽ�������.
    ��һ�������ʵ�ֲ��ֵ��޸�Ӧ�Կͻ�������Ӱ��,���ͻ��Ĵ��벻�����±���.
    (C++(����Կͻ���ȫ���س����ʵ�ֲ���.��C++��,��ı�ʾ����ӿ����ǿɼ���.
    �������Ҫ����.����һ�����νṹ˵������뽫һ������ֽ����������.Rumbaugh ���������νṹΪ��Ƕ�׵��ջ���(nested generalizations (.
    �����ڶ������乲��ʵ��(����ʹ�����ü���(,��ͬʱҪ��ͻ�����֪����һ��.һ���򵥵����ӱ���Coplien ��String ��[ Cop92 ],��������ж��������Թ���ͬһ���ַ�����ʾ(StringRep (.
*/
#include <stdio.h>

typedef enum _dumpling_type {
    TYPE_MEAT   = 0,
    TYPE_NORMAL = 1,
    TYPE_Unknown
} dumpling_type_t;

typedef struct _meat_dumpling {
    void (*make)(void);
} meat_dumpling_t;

typedef struct _normal_dumpling {
    void (*make)(void);
} normal_dumpling_t;

typedef struct _dumpling_reuqest {
    enum _dumpling_type type;
    void *pDumpling;   
} dumpling_request_t;

void buy_dumpling(dumpling_request_t *pDumplingRequest)
{
    //assert(NULL != pDumplingRequest);

    if (TYPE_MEAT == pDumplingRequest->type)
        return ((meat_dumpling_t *)(pDumplingRequest->pDumpling))->make();
    else
        return ((normal_dumpling_t *)(pDumplingRequest->pDumpling))->make();
} 

void make_meat_dumpling(void)
{
    printf("make meat dumpling\n");
}

void make_normal_dumpling(void)
{
    printf("make normal dumpling\n");
}

static dumpling_request_t dumpling_request[] = {
    [0] = {
        .type = TYPE_MEAT,
        .pDumpling = &(meat_dumpling_t){ .make = make_meat_dumpling }
    },
    [1] = {
        .type = TYPE_NORMAL,
        .pDumpling = &(normal_dumpling_t){ .make = make_normal_dumpling }
    }
};

int main (int argc, char * argv[], char * envp[])
{
    dumpling_type_t idx;
    
    for (idx = TYPE_MEAT; idx < TYPE_Unknown; idx++) {
        buy_dumpling(dumpling_request+idx);
    }

    return 0;
}
