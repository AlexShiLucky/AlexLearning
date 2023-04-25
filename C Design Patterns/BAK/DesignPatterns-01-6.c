// C语言和设计模式(之模板模式)
#include <stdio.h>

struct _Basic_ops;

typedef struct _Basic
{
    void *pData;
    struct _Basic_ops *ops;
} Basic_t;

typedef struct _Basic_ops
{
    void (*step1)(Basic_t *pBasic);
    void (*step2)(Basic_t *pBasic);
    void (*process)(Basic_t *pBasic);
} Basic_ops_t;

void process(Basic_t *pBasic)
{
    Basic_ops_t *ops = pBasic->ops;

    if (ops->step1 != NULL) {
        ops->step1(pBasic);
    }

    if (ops->step2 != NULL) {
        ops->step2(pBasic);
    }
}

void step1(Basic_t *pBasic)
{
    printf("step 1 in %s\n", (char *)pBasic->pData);
}

void step2(Basic_t *pBasic)
{
    printf("step 2 in %s\n", (char *)pBasic->pData);
}

static Basic_ops_t Basic_ops = {
    .step1 = step1,
    .step2 = step2,
    .process = process
};

static Basic_t A_Basic = {
    .pData = "A",
    .ops   = &Basic_ops         // 使用公用结构(默认)
};

static Basic_t B_Basic = {
    .pData = "B",
    .ops   = &Basic_ops         // 使用公用结构(默认)
};

static Basic_t C_Basic = {
    .pData = "C",
    .ops   = &(Basic_ops_t){    // 使用匿名结构(特例)
        .step1 = NULL,
        .step2 = step2,
        .process = process
    }
};

#define PROCESS(x)  (x.ops->process(&x))
int main(void)
{
    PROCESS(A_Basic);
    PROCESS(B_Basic);
    PROCESS(C_Basic);

    return 0;
}

