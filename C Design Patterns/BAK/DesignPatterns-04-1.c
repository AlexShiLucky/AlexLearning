//C语言和设计模式(责任链模式)
#include <stdio.h>

typedef struct _leader
{
    struct _leader *next;
    int account;
    
    int (*request)(struct _leader *pLeader, int num); 
} leader_t;

void set_account(struct _leader *pLeader, int account)
{
    //assert(NULL != pLeader);

    pLeader->account = account;
    return;
} 

void set_next_leader(const struct _leader *pLeader, struct _leader *next)
{
    //assert(NULL != pLeader && NULL != next);

    pLeader->next = next;
    return;
}

int request_for_manager(struct _leader *pLeader, int num)
{
    //assert(NULL != pLeader && 0 != num);

    if (num < 100000)
        return 1;
    else if(pLeader->next) 
        return pLeader->next->request(pLeader->next, num);   
    else  
        return 0;
}

#define PRINT_SHOE(x)   (x->print_shoe(x))

int main(void)
{
    shoe_t *shoe_A;
    
    shoe_A = manufacture_new_shoe(TYPE_LEATHER);
    PRINT_SHOE(shoe_A);

    return 0;
}
