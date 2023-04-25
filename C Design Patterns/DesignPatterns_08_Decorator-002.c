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

struct SWriteLetter {
    FWrite Write;
};

typedef struct SDecorator {
    WriteLetter Write;
    FDecorator Decorator;
} Decorator;

void mWrite(void)
{
    printf("������д����...\n");
}

void mDecorator(WriteLetter write)
{
    Decorator decorator;
    
    decorator.Write = write;
    decorator.Write.Write();
    
    printf("��ӱ���...\n");
    printf("������...\n");
}

static WriteLetter writer = {mWrite};
static Decorator decorator = {{mWrite}, mDecorator};

int main (int argc, char * argv[], char * envp[])
{
    writer.Write();
    decorator.Decorator(writer);    // �������Ķ������װ��
    return 0;
}
