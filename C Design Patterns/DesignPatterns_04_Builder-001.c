/**
C语言和设计模式-<创建型>-<Builder>-<建造者模式>
意图:
    将一个复杂对象的构建与它的表示分离,使得同样的构建过程可以创建不同的表示.
适用性:
    当创建复杂对象的算法应该独立于该对象的组成部分以及它们的装配方式时.
    当构造过程必须允许被构造的对象有不同的表示时.
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
    printf("生产发动机.\n");
    return plane->engine;
}

int mbuildAirFrame(Plane *plane)
{
    plane->airFrame = FINISHED;
    printf("生产机身.\n");
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
        printf("飞机组装完毕！\n");
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
