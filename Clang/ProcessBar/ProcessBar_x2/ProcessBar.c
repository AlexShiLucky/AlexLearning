#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    float delta = 0.25f;
    float percent = 0;
    int barnum = 0;
    char bar[102];
    const char* flag = "-\\|/";

    bar[0] = '\0';
    while (barnum < 100) {
        percent += delta;
        barnum = (int)percent;
        memset(bar, '#', barnum);
        bar[barnum+1] = '\0';
        printf("ProcessBar [%-100s] [%.2f%%] [%c]\r", bar, percent, flag[barnum%4]);
        fflush(stdout);
        usleep(25000);
    }
    printf("\n");
    return 0;
}
