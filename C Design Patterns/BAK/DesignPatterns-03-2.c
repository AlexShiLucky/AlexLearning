//C语言和设计模式(工厂模式) 
#include <stdio.h>

typedef enum _shoe_type {
    TYPE_LEATHER    = 0,
    TYPE_RUBBER     = 1,
    TYPE_Unknown
} shoe_type_t;

typedef struct _shoe
{
    enum _shoe_type type;
    void (*print_shoe)(struct _shoe *);
} shoe_t;

void print_leather_shoe(shoe_t *pShoe)
{
    printf("This is a leather show!\n");
}

void print_rubber_shoe(shoe_t *pShoe)
{
    printf("This is a rubber shoe!\n");
}

void print_unknown_shoe(shoe_t *pShoe)
{
    printf("This is a unknown shoe!\n");
}

static shoe_t shoe[] = {
    {TYPE_LEATHER, print_leather_shoe},
    {TYPE_RUBBER,  print_rubber_shoe},
    {TYPE_Unknown, print_unknown_shoe}
};

shoe_t* manufacture_new_shoe(shoe_type_t type)
{
    shoe_t *pShoe = (shoe_t *)malloc(sizeof(shoe_t));
    if (pShoe == NULL) return NULL;

    memset(pShoe, 0, sizeof(shoe_t));
   *pShoe = shoe[type];

    return pShoe;
}

#define PRINT_SHOE(x)   (x->print_shoe(x))

int main(void)
{
    shoe_t *shoe_A;
    
    shoe_A = manufacture_new_shoe(TYPE_LEATHER);
    PRINT_SHOE(shoe_A);

    return 0;
}
