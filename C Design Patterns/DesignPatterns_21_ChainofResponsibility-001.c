/**
C���Ժ����ģʽ-<��Ϊ��>-<Chain of Responsibility>-<������ģʽ>
��ͼ:
    ʹ��������л��ᴦ������,�Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ.
    ����Щ��������һ����,���������������ݸ�����,ֱ����һ����������Ϊֹ.
������:
    �ж���Ķ�����Դ���һ������,�ĸ����������������ʱ���Զ�ȷ��.
    �����ڲ���ȷָ�������ߵ������,���������е�һ���ύһ������.
    �ɴ���һ������Ķ��󼯺�Ӧ����ָ̬��.
*/
#include <stdio.h>

typedef struct _leader {
    struct _leader *next;
    char *name;
    unsigned int account;

    int (*request)(struct _leader *pLeader, unsigned int num);
} leader_t;

void set_account(leader_t *pLeader, int account)
{
    //assert(NULL != pLeader);

    pLeader->account = account;
}

void set_next_leader(leader_t *pLeader, leader_t *next)
{
    //assert(NULL != pLeader && NULL != next);

    pLeader->next = next;
}

int request(leader_t *pLeader, unsigned int num)
{
    //assert(NULL != pLeader && 0 != num);

    if(num < pLeader->account) {
        printf("To %s request %d successful\n", pLeader->name, num);
        return 1;
    } else if(NULL != pLeader->next) {
        printf("To next leader\n");
        return pLeader->next->request(pLeader->next, num);
    } else {
        printf("Request failed\n");
        return 0;
    }
}

void leader_init(leader_t *pLeader, char *name, int (*request)(leader_t *pLeader, unsigned int))
{
    pLeader->name    = name;
    pLeader->request = request;
}

int main (int argc, char * argv[], char * envp[])
{
    leader_t boss;
    leader_t manager;
    leader_t supervisor;

    leader_init(&boss,       "boss",       request);
    leader_init(&manager,    "manager",    request);
    leader_init(&supervisor, "supervisor", request);

    set_account(&boss,       1000000u);
    set_account(&manager,     100000u);
    set_account(&supervisor,   10000u);

    set_next_leader(&boss,        NULL);
    set_next_leader(&manager,    &boss);
    set_next_leader(&supervisor, &manager);

    supervisor.request(&supervisor, 30000u);
    supervisor.request(&supervisor, 500000u);
    manager.request(&manager, 20000u);
    manager.request(&manager, 200000u);

    return 0;
}
