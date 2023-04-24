#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *str ="2019 \t 2\t  14";
    char *sbuf;
    char *pstr;
    int tmp;
    int year, month, day;
    int isok = 0;
    
    sbuf = strdup(str);
    do {
        pstr = strtok(sbuf, " \t");
        if (pstr)
            printf("%s\n", pstr);
        tmp = atoi(pstr);
        if ((tmp >= 2000) && (tmp <= 2099)) {
            year = tmp;
        } else {
            free(sbuf);
            break;
        }
        pstr = strtok(NULL, " \t");
        if (pstr)
            printf("%s\n", pstr);
        tmp = atoi(pstr);
        if ((tmp >= 1) && (tmp <= 12)) {
            month = tmp;
        } else {
            free(sbuf);
            break;
        }
        pstr = strtok(NULL, " \t");
        if (pstr)
            printf("%s\n", pstr);
        tmp = atoi(pstr);
        if ((tmp >= 1) && (tmp <= 31)) {
            day = tmp;
        } else {
            free(sbuf);
            break;
        }
        free(sbuf);
        isok = 1;
    } while (0);
    
    if (isok)
        printf("%d-%d-%d\n", year, month, day);
    else
        printf("Error\n");

    return 0;
}