/**
C���Ժ����ģʽ-<��Ϊ��>-<Command>-<����ģʽ>
��ͼ:
    ��һ�������װΪһ������,�Ӷ�ʹ����ò�ͬ������Կͻ����в��������������Ŷӻ��¼������־,�Լ�֧�ֿɳ����Ĳ���.
������:
    �������ִ�еĶ����Բ�����ĳ����,����ù��������еĻص�(call back(����������ֲ���������.��ν�ص�������ָ��������ĳ��ע��,���������Ժ�ĳ����Ҫ��ʱ�򱻵���.Command ģʽ�ǻص����Ƶ�һ�������������Ʒ.
    �ڲ�ͬ��ʱ��ָ�������к�ִ������.һ��Command���������һ�����ʼ�����޹ص�������.���һ������Ľ����߿���һ�����ַ�ռ��޹صķ�ʽ���,��ô�Ϳɽ�������������������͸���һ����ͬ�Ľ��̲����Ƕ�ʵ�ָ�����.
    ֧��ȡ������.Command��Excute ��������ʵʩ����ǰ��״̬�洢����,��ȡ������ʱ���״̬���������ò�����Ӱ��.Command �ӿڱ������һ��Unexecute����,�ò���ȡ����һ��Execute���õ�Ч��.ִ�е�����洢��һ����ʷ�б���.��ͨ��������ǰ������һ�б��ֱ����Unexecute��Execute��ʵ���������޵ġ�ȡ�����͡�������.
    ֧���޸���־,������ϵͳ����ʱ,��Щ�޸Ŀ��Ա�����һ��.��Command�ӿ������װ�ز����ʹ洢����,�����������ֱ䶯��һ��һ�µ��޸���־.�ӱ����лָ��Ĺ��̰����Ӵ��������¶����¼�����������Execute��������ִ������.
    �ù�����ԭ������ϵĸ߲��������һ��ϵͳ.����һ�ֽṹ��֧������(transaction)����Ϣϵͳ�кܳ���.һ�������װ�˶����ݵ�һ��䶯.Commandģʽ�ṩ�˶�������н�ģ�ķ���.Command��һ�������Ľӿ�,ʹ���������ͬһ�ַ�ʽ�������е�����.ͬʱʹ�ø�ģʽҲ�����������������չϵͳ.
*/
#include <stdio.h>

typedef struct _post {
    int number;
    void (*doing)(struct _post *pPost);
} post_t;

void doing(post_t *pPost)
{
    printf("post letter: %d\n", pPost->number);
}

typedef struct _command {
    void *pData;
    void (*exe)(struct _command *pCommand);
} command_t;

void post_exe(struct _command *pCommand)
{
    //assert(NULL != pCommand);

    ((post_t *)(pCommand->pData))->doing((post_t *)(pCommand->pData));
}

typedef struct _boss {
    command_t *pCommand;
    void (*call)(struct _boss *pBoss);
} boss_t;

void boss_call(struct _boss *pBoss)
{
    //assert(NULL != pBoss);

    pBoss->pCommand->exe(pBoss->pCommand);
}

int main (int argc, char * argv[], char * envp[])
{
    boss_t boss;
    command_t command;

    boss.pCommand = &command;
    boss.call = boss_call;

    command.pData = &(post_t){ 3, doing };
    command.exe = post_exe;

    boss.call(&boss);

    return 0;
}
