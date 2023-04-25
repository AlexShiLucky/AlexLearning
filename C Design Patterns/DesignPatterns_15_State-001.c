/**
C���Ժ����ģʽ-<��Ϊ��>-<State>-<״̬ģʽ>
��ͼ:
    ����һ�����������ڲ�״̬�ı�ʱ�ı�������Ϊ.���������ƺ��޸���������.
������:
    һ���������Ϊȡ��������״̬,����������������ʱ�̸���״̬�ı�������Ϊ.
    һ�������к����Ӵ�Ķ��֧���������,����Щ��֧�����ڸö����״̬.
    ���״̬ͨ����һ������ö�ٳ�����ʾ.
    ͨ��,�ж������������һ��ͬ�������ṹ.
    Stateģʽ��ÿһ��������֧����һ������������.
    ��ʹ������Ը��ݶ������������������״̬��Ϊһ������,��һ������Բ���������������������仯.
*/
#include <stdio.h>

// ����״̬
typedef enum _person_state {
    PSTATE_BABY     = 0,    // Ӥ��
    PSTATE_YOUNG    = 1,    // ������
    PSTATE_MIDDLE   = 2,    // ����
    PSTATE_OLD      = 3,    // ����
    PSTATE_TOTAL            // ״̬����
} person_state_t;

// ����:�ṹ��
typedef struct _person {
    int (*action)(void);     // ״̬��Ӧ����Ϊ
} person_t;

// Ӥ��״̬:����,etc.
int drink(void)
{
    printf("I am drinking milk!\n");

    return 0;
}

// ������״̬:ѧϰ,etc.
int study(void)
{
    printf("I am study!\n");

    return 0;
}

// ����״̬:����,etc.
int work(void)
{
    printf("I am working!\n");

    return 0;
}

// ����״̬:����,etc.
int retire(void)
{
    printf("I am have been retired!\n");

    return 0;
}

void set_state(person_t *pPerson, person_state_t state)
{
    int (* const action_tbl[])(void) = { drink, study, work, retire };

    pPerson->action = action_tbl[state];
}

int main (int argc, char * argv[], char * envp[])
{
    person_state_t state;
    person_t person;

    for (state = 0; state < PSTATE_TOTAL; state++) {
        set_state(&person, state);
        person.action();
    }

    return 0;
}
