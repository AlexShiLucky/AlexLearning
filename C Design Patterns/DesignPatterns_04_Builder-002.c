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
    printf("生产发动机.\n");
    return plane->engine;
}

int build_air_frame(plane_t *plane)
{
    plane->air_frame = FINISHED;
    printf("生产机身.\n");
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
        printf("飞机组装完毕！\n");
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
