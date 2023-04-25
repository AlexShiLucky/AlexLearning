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

void A_step1(Basic_t *pBasic)
{
    printf("step 1 in A\n");
}

void A_step2(Basic_t *pBasic)
{
    printf("step 2 in A\n");
}

static Basic_t A_Basic = {
    .step1 = A_step1,
    .step2 = A_step2,
    .process = process
};

void B_step1(Basic_t *pBasic)
{
    printf("step 1 in B\n");
}

void B_step2(Basic_t *pBasic)
{
    printf("step 2 in B\n");
}

static Basic_t B_Basic = {
    .step1 = B_step1,
    .step2 = B_step2,
    .process = process
};

void C_step1(Basic_t *pBasic)
{
    printf("step 1 in C\n");
}

void C_step2(Basic_t *pBasic)
{
    printf("step 2 in C\n");
}

static Basic_t C_Basic = {
    .step1 = C_step1,
    .step2 = C_step2,
    .process = process
};

int main(void)
{
    A_Basic.process(&A_Basic);
    B_Basic.process(&B_Basic);
    C_Basic.process(&C_Basic);

    return 0;
}

