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
    pBasic->ops->step1(pBasic);
    pBasic->ops->step2(pBasic);
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
    .ops   = &Basic_ops
};

static Basic_t B_Basic = {
    .pData = "B",
    .ops   = &Basic_ops
};

static Basic_t C_Basic = {
    .pData = "C",
    .ops   = &Basic_ops
};

int main(void)
{
    A_Basic.ops->process(&A_Basic);
    B_Basic.ops->process(&B_Basic);
    C_Basic.ops->process(&C_Basic);

    return 0;
}

