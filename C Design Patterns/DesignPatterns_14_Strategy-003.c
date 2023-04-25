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

struct _view_strategy {
    void (* view)(void);
} view_strategy_t;

struct _viewer {
    void (* view)(void);
    struct _viewer (* set_view_strategy)(view_strategy_t *);
} viewer_t;

typedef struct _html_viewer {
    struct _view_strategy view;
} html_viewer_t;

typedef struct StxtViewer {
    struct _view_strategy view;
} txt_viewer_t;

typedef struct SjpgViewer {
    struct _view_strategy view;
} jpg_viewer_t;

typedef struct SpdfViewer {
    struct _view_strategy view;
} pdf_viewer_t;

void viewer(void){}

void html_viwe(void)
{
    printf("浏览HTML文件.\n");
}

void txt_viwe(void)
{
    printf("浏览TXT文件.\n");
}

void jpg_viwe(void)
{
    printf("浏览JPG文件.\n");
}

void pdf_viwe(void)
{
    printf("浏览PDF文件.\n");
}

viewer_t set_view_strategy(view_strategy_t *pView)
{
    viewer_t viewer;
    
    viewer.view = pView->view;
    return viewer;
}

static html_viewer_t html_viwer = {{html_viwe}};
static txt_viewer_t  txt_viwer  = {{txt_viwe}};
static jpg_viewer_t  jpg_viwer  = {{jpg_viwe}};
static pdf_viewer_t  pdf_viwer  = {{pdf_viwe}};
static viewer_t viewer = {viewer, set_view_strategy};

// Strategy接口的使用
int main (int argc, char * argv[], char * envp[])
{
    view_strategy_t view = {viewer};
    viewer_t pviewer;
    
    pviewer = viewer.set_view_strategy(&html_viwer.view);
    pviewer.view();
    return 0;
}
