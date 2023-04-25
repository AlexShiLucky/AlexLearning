/**
C���Ժ����ģʽ-<��Ϊ��>-<Strategy>-<����ģʽ>
��ͼ:
    ����һϵ�е��㷨,������һ������װ����,����ʹ���ǿ��໥�滻.��ģʽʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯.
������:
    �����ص����������Ϊ����.�����ԡ��ṩ��һ���ö����Ϊ�е�һ����Ϊ������һ����ķ���.
    ��Ҫʹ��һ���㷨�Ĳ�ͬ����.����,����ܻᶨ��һЩ��ӳ��ͬ�Ŀռ�/ʱ��Ȩ����㷨.����Щ����ʵ��Ϊһ���㷨������ʱ[H087] ,����ʹ�ò���ģʽ.
    �㷨ʹ�ÿͻ���Ӧ��֪��������.��ʹ�ò���ģʽ�Ա��Ⱪ¶���ӵġ����㷨��ص����ݽṹ.
    һ���ඨ���˶�����Ϊ,������Щ��Ϊ�������Ĳ������Զ������������ʽ����.����ص�������֧�������Ǹ��Ե�Strategy�����Դ�����Щ�������.
*/
#include <stdio.h>

typedef struct SViewerStrategy ViewerStrategy;
typedef struct SViewer Viewer;
typedef void (* FView)(void);
typedef Viewer(* FsetViewerStrategy)(ViewerStrategy);

struct SViewerStrategy {
    FView view;
};

struct SViewer {
    FView view;
    FsetViewerStrategy setViewerStrategy;
};

typedef struct ShtmlViewer {
    ViewerStrategy viewerStrategy;
} HtmlViewer;

typedef struct StxtViewer {
    ViewerStrategy viewerStrategy;
} TxtViewer;

typedef struct SjpgViewer {
    ViewerStrategy viewerStrategy;
} JpgViewer;

typedef struct SpdfViewer {
    ViewerStrategy viewerStrategy;
} PdfViewer;

void mview(void){}

void Hview(void)
{
    printf("���HTML�ļ�.\n");
}

void Tview(void)
{
    printf("���TXT�ļ�.\n");
}

void Jview(void)
{
    printf("���JPG�ļ�.\n");
}

void Pview(void)
{
    printf("���PDF�ļ�.\n");
}

Viewer msetViewerStrategy(ViewerStrategy viewerStrategy)
{
    Viewer viewer;
    
    viewer.view = viewerStrategy.view;
    return viewer;
}

static HtmlViewer htmlViewer = {{Hview}};
static TxtViewer  txtViewer  = {{Tview}};
static JpgViewer  jpgViewer  = {{Jview}};
static PdfViewer  pdfViewer  = {{Pview}};
static Viewer viewer = {mview, msetViewerStrategy};

// Strategy�ӿڵ�ʹ��
int main (int argc, char * argv[], char * envp[])
{
    static ViewerStrategy viewerStrategy = {mview};
    static Viewer pviewer;
    
    pviewer = viewer.setViewerStrategy(htmlViewer.viewerStrategy);
    pviewer.view();
    return 0;
}
