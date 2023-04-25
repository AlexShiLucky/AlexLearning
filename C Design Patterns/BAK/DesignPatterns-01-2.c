// C语言和设计模式(之模板模式)
#include <stdio.h>

typedef struct _Basic
{
    void *pData;
    void (*step1)(struct _Basic *pBasic);
    void (*step2)(struct _Basic *pBasic);
    void (*process)(struct _Basic *pBasic);
} Basic_t;

void process(Basic_t *pBasic)
{
    pBasic->step1(pBasic);
    pBasic->step2(pBasic);
}

void step1(Basic_t *pBasic)
{
    printf("step 1 in %s\n", (char *)pBasic->pData);
}

void step2(Basic_t *pBasic)
{
    printf("step 2 in %s\n", (char *)pBasic->pData);
}

static Basic_t A_Basic = {
    .pData = "A",
    .step1 = step1,
    .step2 = step2,
    .process = process
};

static Basic_t B_Basic = {
    .pData = "B",
    .step1 = step1,
    .step2 = step2,
    .process = process
};

static Basic_t C_Basic = {
    .pData = "C",
    .step1 = step1,
    .step2 = step2,
    .process = process
};

int main(void)
{
    A_Basic.process(&A_Basic);
    B_Basic.process(&B_Basic);
    C_Basic.process(&C_Basic);

    return 0;
}

