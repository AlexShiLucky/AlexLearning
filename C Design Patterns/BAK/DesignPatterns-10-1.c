// C语言和设计模式(桥接模式)
#include <stdio.h>

typedef enum _dumpling_type
{
    TYPE_MEAT   = 0,
    TYPE_NORMAL = 1,
    TYPE_Unknown
} dumpling_type_t;

typedef struct _meat_dumpling
{
    void (*make)(void);
} meat_dumpling_t;

typedef struct _normal_dumpling
{
    void (*make)(void);
} normal_dumpling_t;

typedef struct _dumpling_reuqest
{
    dumpling_type_t type;
    void *pDumpling;   
} dumpling_request_t;

void buy_dumpling(dumpling_request_t *pDumplingRequest)
{
    //assert(NULL != pDumplingRequest);

    if (TYPE_MEAT == pDumplingRequest->type)
        return ((meat_dumpling_t *)(pDumplingRequest->pDumpling))->make();
    else
        return ((normal_dumpling_t *)(pDumplingRequest->pDumpling))->make();
} 

void make_meat_dumpling(void)
{
    printf("make meat dumpling\n");
}

void make_normal_dumpling(void)
{
    printf("make normal dumpling\n");
}

static dumpling_request_t dumpling_request[] = {
    [0] = {
        .type = TYPE_MEAT,
        .pDumpling = &(meat_dumpling_t){ .make = make_meat_dumpling }
    },
    [1] = {
        .type = TYPE_NORMAL,
        .pDumpling = &(normal_dumpling_t){ .make = make_normal_dumpling }
    }
};

int main(void)
{
    dumpling_type_t idx;
    
    for (idx = TYPE_MEAT; idx < TYPE_Unknown; idx++) {
        buy_dumpling(dumpling_request+idx);
    }

    return 0;
}
