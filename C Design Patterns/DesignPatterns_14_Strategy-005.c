/**
C���Ժ����ģʽ-<��Ϊ��>-<Strategy>-<����ģʽ>
��ͼ:
    ����һϵ�е��㷨,������һ������װ����,����ʹ���ǿ��໥�滻.��ģʽʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯.
������:
    �����ص����������Ϊ����.�����ԡ��ṩ��һ���ö����Ϊ�е�һ����Ϊ������һ����ķ���.
    ��Ҫʹ��һ���㷨�Ĳ�ͬ����.����,����ܻᶨ��һЩ��ӳ��ͬ�Ŀռ�/ʱ��Ȩ����㷨.����Щ����ʵ��Ϊһ���㷨������ʱ[H087] ,����ʹ�ò���ģʽ.
    �㷨ʹ�ÿͻ���Ӧ��֪��������.��ʹ�ò���ģʽ�Ա��Ⱪ¶���ӵġ����㷨��ص����ݽṹ.
    һ���ඨ���˶�����Ϊ,������Щ��Ϊ�������Ĳ������Զ������������ʽ����.����ص�������֧�������Ǹ��Ե�Strategy�����Դ�����Щ�������.
*/
#include <stdio.h>

typedef struct _work_mode {
    void (*work)(void);
} work_mode_t;

void work_power_up(void)
{
    printf("power up init.\n");
}

void work_first_priming(void)
{

}

void work_idle(void)
{

}

void work_testing(void)
{

}

void work_maintain(void)
{

}

void work_error_deal(void)
{

}

void work_drain(void)
{

}

void work_power_down(void)
{

}

typedef struct _quack_behavior {
    void (*quack)(void);
} quack_behavior_t;

void quack(void)
{
    printf("Ѽ�����ɽ�\n");
}

void squeak(void)
{
    printf("��ƤѼ�¸½�"); 
}

void mule_quack(void)
{

}

typedef struct _duck {
    struct _fly_behavior    fly_behavior;
    struct _quack_behavior  quack_behavior;
    
    void (*swim)(void);
    void (*display)(void);
    void (*perfom_fly)(struct _duck *);
    void (*perfom_quack)(struct _duck *);
    void (*set_fly_behavior)(struct _duck *, struct _fly_behavior *);
    void (*set_quack_behavior)(struct _duck *, struct _quack_behavior *);
} duck_t;

static void _swim(void)
{
    printf("swim\n");
}

static void _display(void)
{
    printf("display\n");
}

static void _perfom_fly(struct _duck *duck)
{
    duck->fly_behavior.fly();
}

static void _perfom_quack(struct _duck *duck)
{
    duck->quack_behavior.quack();
}

static void _set_fly_behavior(struct _duck *duck, struct _fly_behavior *fly_behavior)
{
    duck->fly_behavior = *fly_behavior;
}

static void _set_quack_behavior(struct _duck *duck, struct _quack_behavior *quack_behavior)
{
    duck->quack_behavior = *quack_behavior;
}

static duck_t   duck = {
    {fly_no_way},
    {quack},
    _swim,
    _display,
    _perfom_fly,
    _perfom_quack,
    _set_fly_behavior,
    _set_quack_behavior
};

// Strategy�ӿڵ�ʹ��
int main (int argc, char * argv[], char * envp[])
{
    duck.swim();
    duck.display();
    duck.perfom_fly(&duck);
    duck.perfom_quack(&duck);
    return 0;
}
