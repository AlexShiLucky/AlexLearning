/**
C���Ժ����ģʽ-<�ṹ��>-<Proxy>-<����ģʽ>
��ͼ:
    Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ���.
������:
    ����Ҫ�ñȽ�ͨ�ú͸��ӵĶ���ָ�����򵥵�ָ���ʱ��,ʹ��Proxyģʽ.������һ Щ����ʹ��Proxy ģʽ�������:
    1) Զ�̴���(Remote Proxy (Ϊһ�������ڲ�ͬ�ĵ�ַ�ռ��ṩ�ֲ�����. NEXTSTEP[Add94] ʹ��NXProxy ��ʵ������һĿ��.Coplien[Cop92] �����ִ���Ϊ����ʹ�� (Ambassador (.
    2) �����(Virtual Proxy (������Ҫ���������ܴ�Ķ���.�ڶ���һ��������ImageProxy ��������һ�ִ��������.
    3) ��������(Protection Proxy (���ƶ�ԭʼ����ķ���.�����������ڶ���Ӧ���в�ͬ �ķ���Ȩ�޵�ʱ��.����,��Choices ����ϵͳ[ CIRM93]��KemelProxiesΪ����ϵͳ�����ṩ �˷��ʱ���.
    4) ����ָ��(Smart Reference (ȡ���˼򵥵�ָ��,���ڷ��ʶ���ʱִ��һЩ���Ӳ���. ���ĵ�����;����:
    ��ָ��ʵ�ʶ�������ü���,�������ö���û������ʱ,�����Զ��ͷ���(Ҳ��ΪSmartPointers[Ede92 ] ).
    ����һ������һ���־ö���ʱ,����װ���ڴ�.
    �ڷ���һ��ʵ�ʶ���ǰ,����Ƿ��Ѿ���������,��ȷ�����������ܸı���.
*/
#include <stdio.h>

typedef struct _kind_woman {
    void (*make_eyes_with_man)(void);
    void (*happy_with_man)(void);
} kind_woman_t;

typedef struct _woman {
    struct _kind_woman woman;
} woman_t;

void pjl_make_eyes_with_man(void)
{
    printf("pan jin lian pao mei yan\n");
}

void pjl_happy_with_man(void)
{
    printf("pan jin lian happy with man\n");
}

void js_make_eyes_with_man(void)
{
    printf("jia shi pao mei yan\n");
}

void js_happy_with_man(void)
{
    printf("jia shi happy with man\n");
}

typedef struct _wang_po {
    struct _kind_woman *woman;
} wang_po_t;

void pan_jin_lian_init(woman_t *pPJL)
{
    memset(pPJL, 0, sizeof(woman_t));
    pPJL->woman.make_eyes_with_man = pjl_make_eyes_with_man;
    pPJL->woman.happy_with_man = pjl_happy_with_man;
}

void jia_shi_init(woman_t *pJS)
{
    memset(pJS, 0, sizeof(woman_t));
    pJS->woman.make_eyes_with_man = js_make_eyes_with_man;
    pJS->woman.happy_with_man = js_happy_with_man;
}

void wang_po_proxy(wang_po_t *pWP, kind_woman_t *pKW)
{
    pWP->woman = pKW;
}

int main (int argc, char * argv[], char * envp[])
{
    woman_t pan_jin_lian;
    woman_t jia_shi;
    wang_po_t wang_po;
    
    pan_jin_lian_init(&pan_jin_lian);
    wang_po_proxy(&wang_po, (kind_woman_t *)&pan_jin_lian);
    
    wang_po.woman->make_eyes_with_man();
    wang_po.woman->happy_with_man();
    
    jia_shi_init(&jia_shi);
    wang_po_proxy(&wang_po, (kind_woman_t *)&jia_shi);
    
    wang_po.woman->make_eyes_with_man();
    wang_po.woman->happy_with_man();
    return 0;
}
