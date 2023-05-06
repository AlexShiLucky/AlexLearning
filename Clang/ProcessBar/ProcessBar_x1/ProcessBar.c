#include <stdio.h>
#include <unistd.h>
int main()
{
    int i = 0;
    char bar[102];
    const char* flag = "-\\|/";

    bar[0] = '\0';
    while (i <= 100) {
        printf("[%-100s] [%d%%] [%c]\r", bar, i, flag[i%4]);
        fflush(stdout);
        bar[i++] = '#';
        bar[i] = '\0';
        usleep(100000);
    }
    printf("\n");
    return 0;
}
