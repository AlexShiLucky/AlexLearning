/**
C语言和设计模式-<结构型>-<Decorator>-<装饰者模式>
意图:
    动态地给一个对象添加一些额外的职责.就增加功能来说,Decorator 模式相比生成子类更为灵活.
适用性:
    在不影响其他对象的情况下,以动态、透明的方式给单个对象添加职责.
    处理那些可以撤消的职责.
    当不能采用生成子类的方法进行扩充时.一种情况是,可能有大量独立的扩展,为支持每一种组合将产生大量的子类,使得子类数目呈爆炸性增长.另一种情况可能是因为类定义被隐藏,或类定义不能用于生成子类.
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
    printf("正在书写正文...\n");
}

void mDecorator(WriteLetter write)
{
    Decorator decorator;
    
    decorator.Write = write;
    decorator.Write.Write();
    
    printf("添加背景...\n");
    printf("添加外框...\n");
}

static WriteLetter writer = {mWrite};
static Decorator decorator = {{mWrite}, mDecorator};

int main (int argc, char * argv[], char * envp[])
{
    writer.Write();
    decorator.Decorator(writer);    // 对所给的对象进行装饰
    return 0;
}
