/**
C���Ժ����ģʽ-<������>-<Builder>-<������ģʽ>
��ͼ:
    ��һ�����Ӷ���Ĺ��������ı�ʾ����,ʹ��ͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ.
������:
    ���������Ӷ�����㷨Ӧ�ö����ڸö������ɲ����Լ����ǵ�װ�䷽ʽʱ.
    ��������̱�����������Ķ����в�ͬ�ı�ʾʱ.
*/
#include <stdio.h>

#define FINISHED    1
#define UNFINISHED  0

typedef struct _plane {
    int engine;
    int air_frame;
} plane_t;

typedef struct _builder {
    struct _plane plane;
    int (* build_engine)(plane_t *);
    int (* build_air_frame)(plane_t *);
} builder_t;

typedef struct _director {
    struct _builder builder;
    void (* construct)(builder_t *);
} director_t;

int build_engine(plane_t *plane)
{
    plane->engine = FINISHED;
    printf("����������.\n");
    return plane->engine;
}

int build_air_frame(plane_t *plane)
{
    plane->air_frame = FINISHED;
    printf("��������.\n");
    return plane->air_frame;
}

void construct(builder_t *builder)
{
    int part1 = UNFINISHED;
    int part2 = UNFINISHED;
    
    part1 = builder->build_engine(&builder->plane);
    part2 = builder->build_air_frame(&builder->plane);

    if ((part1 == FINISHED)
     && (part2 == FINISHED))
    {
        printf("�ɻ���װ��ϣ�\n");
    }
}

static director_t director = {
    {
        {UNFINISHED, UNFINISHED},
        build_engine,
        build_air_frame
    },
    construct
};

int main (int argc, char * argv[], char * envp[])
{
    director.construct(&director.builder);

    return 0;
}
