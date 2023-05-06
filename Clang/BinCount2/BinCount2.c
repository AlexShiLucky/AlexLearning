#include <stdio.h>

#define NUM     65536u

static unsigned char BitCount2(unsigned long num)
{
    unsigned char cnt;

    for (cnt = 0; num; ++cnt) {
        num &= (num - 1) ;      // 清除最低位的1
    }

    return cnt;
}

int main(int argc, char *argv[])
{
    unsigned long num = 0;
    unsigned char cnt;
    
    for (num = 0; num < NUM; num++) {
        cnt = BitCount2(num);
        printf("0x%08lX: %d\r\n", num, cnt);
    }
    return 0;
}
