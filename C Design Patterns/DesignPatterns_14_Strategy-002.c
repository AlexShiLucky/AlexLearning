/**
C语言和设计模式-<行为型>-<Strategy>-<策略模式>
意图:
    定义一系列的算法,把它们一个个封装起来,并且使它们可相互替换.本模式使得算法可独立于使用它的客户而变化.
适用性:
    许多相关的类仅仅是行为有异.“策略”提供了一种用多个行为中的一个行为来配置一个类的方法.
    需要使用一个算法的不同变体.例如,你可能会定义一些反映不同的空间/时间权衡的算法.当这些变体实现为一个算法的类层次时[H087] ,可以使用策略模式.
    算法使用客户不应该知道的数据.可使用策略模式以避免暴露复杂的、与算法相关的数据结构.
    一个类定义了多种行为,并且这些行为在这个类的操作中以多个条件语句的形式出现.将相关的条件分支移入它们各自的Strategy类中以代替这些条件语句.
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
    printf("浏览HTML文件.\n");
}

void Tview(void)
{
    printf("浏览TXT文件.\n");
}

void Jview(void)
{
    printf("浏览JPG文件.\n");
}

void Pview(void)
{
    printf("浏览PDF文件.\n");
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

// Strategy接口的使用
int main (int argc, char * argv[], char * envp[])
{
    static ViewerStrategy viewerStrategy = {mview};
    static Viewer pviewer;
    
    pviewer = viewer.setViewerStrategy(htmlViewer.viewerStrategy);
    pviewer.view();
    return 0;
}
