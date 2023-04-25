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
    printf("���HTML�ļ�.\n");
}

void txt_viwe(void)
{
    printf("���TXT�ļ�.\n");
}

void jpg_viwe(void)
{
    printf("���JPG�ļ�.\n");
}

void pdf_viwe(void)
{
    printf("���PDF�ļ�.\n");
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

// Strategy�ӿڵ�ʹ��
int main (int argc, char * argv[], char * envp[])
{
    view_strategy_t view = {viewer};
    viewer_t pviewer;
    
    pviewer = viewer.set_view_strategy(&html_viwer.view);
    pviewer.view();
    return 0;
}
