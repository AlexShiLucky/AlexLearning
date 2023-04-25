/**
C���Ժ����ģʽ-<�ṹ��>-<Flyweight>-<��Ԫģʽ>
��ͼ:
    ���ù�������Ч��֧�ִ���ϸ���ȵĶ���.
������:
    һ��Ӧ�ó���ʹ���˴����Ķ���.
    ��ȫ����ʹ�ô����Ķ���,��ɺܴ�Ĵ洢����.
    ����Ĵ����״̬���ɱ�Ϊ�ⲿ״̬.
    ���ɾ��������ⲿ״̬,��ô��������Խ��ٵĹ������ȡ���ܶ������.
    Ӧ�ó��������ڶ����ʶ.����Flyweight ������Ա�����,���ڸ����������б�Ķ���,��ʶ���Խ�������ֵ.
*/
#include <stdio.h>

typedef struct _Font {
    int type;
    int sequence;
    int gap;
    int lineDistance;

    void (*operate)(struct _Font* pFont);
} Font;

typedef struct _FontFactory {
    Font** ppFont;
    int number;
    int size;

    Font* GetFont(struct _FontFactory* pFontFactory, int type, int sequence, int gap, int lineDistance);
} FontFactory;

Font* GetFont(struct _FontFactory* pFontFactory, int type, int sequence, int gap, int lineDistance)
{
    int index;
    Font* pFont;
    Font* ppFont;

    if (NULL == pFontFactory)
        return NULL;

    for (index = 0; index < pFontFactory->number; index++) {
        if (type != pFontFactory->ppFont[index]->type)
            continue;

        if (sequence != pFontFactory->ppFont[index]->sequence)
            continue;

        if (gap != pFontFactory->ppFont[index]->gap)
            continue;

        if (lineDistance != pFontFactory->ppFont[index]->lineDistance)
             continue;

        return pFontFactory->ppFont[index];
    }

    pFont = (Font*)malloc(sizeof(Font));
    assert(NULL != pFont);
    pFont->type = type;
    pFont->sequence = sequence;
    pFont->gap = gap;
    pFont->lineDistance = lineDistance;

    if (pFontFactory->number < pFontFactory->size) {
        pFontFactory->ppFont[index] = pFont;
        pFontFactory->number ++;
        return pFont;
    }

    ppFont = (Font**)malloc(sizeof(Font*) * pFontFactory->size * 2);
    assert(NULL != ppFont);
    memmove(ppFont, pFontFacoty->ppFont, pFontFactory->size);
    free(pFontFactory->ppFont);
    pFontFactory->size *= 2;
    pFontFactory->number ++;
    ppFontFactory->ppFont = ppFont;

    return pFont;
}

int main (int argc, char * argv[], char * envp[])
{
    return 0;
}
