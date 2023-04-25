/**
C���Ժ����ģʽ-<������>-<Singleton>-<����ģʽ>
��ͼ:
    ��֤һ�������һ��ʵ��,���ṩһ����������ȫ�ַ��ʵ�.
������:
    ����ֻ����һ��ʵ�����ҿͻ����Դ�һ��������֪�ķ��ʵ������ʱ.
    �����Ψһʵ��Ӧ����ͨ�����໯����չ��,���ҿͻ�Ӧ��������Ĵ������ʹ��һ����չ��ʵ��ʱ.
*/
#include <stdio.h>

typedef struct _Singleton {
    int value;
} Singleton_t;

Singleton_t *getInstance(void)
{
    static Singleton_t *p = NULL;
    
    if (NULL != p) {
        return p;
    }
    
    p = (Singleton_t *)malloc(sizeof(Singleton_t));
    memset(p, 0, sizeof(Singleton_t));
    assert(NULL != p);
    return p;
}

int main (int argc, char * argv[], char * envp[])
{
    Singleton_t *pSingleton;
    
    pSingleton = getInstance();
    return 0;
}
