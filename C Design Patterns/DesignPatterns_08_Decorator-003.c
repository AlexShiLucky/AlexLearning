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

typedef struct SWriteLetter WriteLetter;
typedef void (* FWrite)(void);
typedef void (* FDecorator)(WriteLetter);

typedef struct _letter {
    void (* write)(void);
} letter_t;

typedef struct _decorator {
    struct _letter *p_letter;
    void (* decorate)(letter_t *);
} decorator_t;

void write(void)
{
    printf("������д����...\n");
}

void decorate(letter_t *pLetter)
{
    decorator_t decorator;

    decorator.p_letter = pLetter;
    decorator.p_letter->write();

    printf("��ӱ���...\n");
    printf("������...\n");
}

static letter_t letter = {write};
static decorator_t decorator = {&letter, decorate};

int main (int argc, char * argv[], char * envp[])
{
    decorator.decorate(&letter);    // �������Ķ������װ��
    return 0;
}
