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

static void make_meat_dumpling(void *pdata, int num);
static void make_normal_dumpling(void *pdata, int num);

typedef enum _dumpling_type {
    TYPE_MEAT   = 0,
    TYPE_NORMAL = 1,
    TYPE_Unknown
} dumpling_type_t;

typedef struct _dumpling {
    char *name;
    void (*make)(void *, int);
} dumpling_t;

typedef struct _dumpling_reuqest {
    enum _dumpling_type type;
    void *pDumpling;
} dumpling_request_t;

static const dumpling_request_t dumpling_request[] = {
    [0] = {
        .type = TYPE_MEAT,
        .pDumpling = &(dumpling_t){ .name = "meat", .make = make_meat_dumpling }
    },
    [1] = {
        .type = TYPE_NORMAL,
        .pDumpling = &(dumpling_t){ .name = "normal", .make = make_normal_dumpling }
    }
};

void buy_dumpling(dumpling_type_t type, int num)
{
    dumpling_t *pDumpling;

    pDumpling = (dumpling_t *)dumpling_request[type].pDumpling;
    pDumpling->make(pDumpling, num);
    printf("dumpling ok\n");
}

static void make_meat_dumpling(void *pdata, int num)
{
    dumpling_t *pDumpling;

    pDumpling = (dumpling_t *)pdata;
    printf("make %s dumpling:%d\n", pDumpling->name, num);
}

static void make_normal_dumpling(void *pdata, int num)
{
    dumpling_t *pDumpling;

    pDumpling = (dumpling_t *)pdata;
    printf("make %s dumpling:%d\n", pDumpling->name, num);
}

int main (int argc, char * argv[], char * envp[])
{
    buy_dumpling(TYPE_MEAT, 10);

    buy_dumpling(TYPE_NORMAL, 20);

    return 0;
}
