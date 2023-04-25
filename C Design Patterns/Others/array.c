#include <stdio.h>

typedef char ARR2[2];
typedef char ARR3[3][2]; 

int main(int argc, char* argv[])
{
    char a[4][3][2] = {
        {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}},
        {{'g', 'h'}, {'i', 'j'}, {'k', 'l'}},
        {{'m', 'n'}, {'o', 'p'}, {'q', 'r'}},
        {{'s', 't'}, {'u', 'v'}, {'w', 'x'}}
    };

    char (*pa)[2]     = &a[1][0];
    char (*ppa)[3][2] = &a[1];
    //ARR2	*pa	 = &a[1][0];
	//ARR3   *ppa  = &a[1];
    
    printf("opt pa = %c\r\n", (*(pa+5))[1]);
    printf("opt ppa = %c\r\n", (*(ppa+1))[2][1]);
    
    return 0;
}
