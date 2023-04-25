//C语言和设计模式(工厂模式) 
#include <stdio.h>

typedef struct _shoe
{
    int type;
    void (*print_shoe)(struct _shoe*);
} shoe_t;

void print_leather_shoe(shoe_t *pShoe)
{
    //assert(NULL != pShoe);
    printf("This is a leather show!\n");
}

void print_rubber_shoe(shoe_t *pShoe)
{
    //assert(NULL != pShoe);
    printf("This is a rubber shoe!\n");
}

#define LEATHER_TYPE 0x01
#define RUBBER_TYPE  0x02

shoe_t* manufacture_new_shoe(int type)
{
    //assert(LEATHER_TYPE == type || RUBBER_TYPE == type);

    shoe_t* pShoe = (shoe_t*)malloc(sizeof(shoe_t));
    //assert(NULL != pShoe);

    memset(pShoe, 0, sizeof(shoe_t));
    if(LEATHER_TYPE == type)
    {
        pShoe->type == LEATHER_TYPE;
        pShoe->print_shoe = print_leather_shoe;
    }
    else
    {
        pShoe->type == RUBBER_TYPE;
        pShoe->print_shoe = print_rubber_shoe;
    }

    return pShoe;
}

#define PRINT_SHOE(x)   (x->print_shoe(x))

int main(void)
{
    shoe_t *shoe_A;
    
    shoe_A = manufacture_new_shoe(LEATHER_TYPE);
    PRINT_SHOE(shoe_A);

    return 0;
}
