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

typedef struct SPlane Plane;
typedef struct SConcreteBuilder ConcreteBuilder;
typedef int  (* FbuildEngine)(Plane *);
typedef int  (* FbuildAirFrame)(Plane *);
typedef void (* FConstruct)(ConcreteBuilder *);

struct SPlane {
    int engine;
    int airFrame;
};

struct SConcreteBuilder {
    Plane plane;
    FbuildEngine buildEngine;
    FbuildAirFrame buildAirFrame;
};

typedef struct SDirector {
    ConcreteBuilder builder;
    FConstruct Construct;
} Director;

int mbuildEngine(Plane *plane)
{
    plane->engine = FINISHED;
    printf("����������.\n");
    return plane->engine;
}

int mbuildAirFrame(Plane *plane)
{
    plane->airFrame = FINISHED;
    printf("��������.\n");
    return plane->airFrame;
}

void mConstruct(ConcreteBuilder *builder)
{
    int part1 = UNFINISHED;
    int part2 = UNFINISHED;
    
    part1 = builder->buildEngine(&builder->plane);
    part2 = builder->buildAirFrame(&builder->plane);
    if ((part1 == FINISHED)
     && (part2 == FINISHED))
    {
        printf("�ɻ���װ��ϣ�\n");
    }
}

static Director director = {
    {
        {UNFINISHED, UNFINISHED},
        mbuildEngine,
        mbuildAirFrame
    },
    mConstruct
};

int main (int argc, char * argv[], char * envp[])
{
    director.Construct(&director.builder);
    return 0;
}
