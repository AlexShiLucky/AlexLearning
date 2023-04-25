#include<stdio.h>
void send(int * to, int * from, int count)
{
    int n = (count + 7 ) / 8 ;
    switch (count & 7) {
        case 0 : do { * to ++ = * from ++ ;
        case 7 :      * to ++ = * from ++ ;
        case 6 :      * to ++ = * from ++ ;
        case 5 :      * to ++ = * from ++ ;
        case 4 :      * to ++ = * from ++ ;
        case 3 :      * to ++ = * from ++ ;
        case 2 :      * to ++ = * from ++ ;
        case 1 :      * to ++ = * from ++ ;
                } while (--n > 0);
    }
}

int main()
{
    int idx = 0;
    int from[150], to[150];

    for (idx = 0; idx < 150; idx++) {
        from[idx] = idx;
    }

    send(to, from, 150);

	printf("===========================================================");
    for (idx = 0; idx < 150; idx++) {
        if (idx % 8 == 0) printf("\r\n");
        printf("%d\t", to[idx]);
    }
    printf("\r\n============================================================\r\n");
    getchar();
    return 0;
}

