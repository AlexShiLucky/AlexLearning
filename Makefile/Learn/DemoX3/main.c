/* main.c */
#include <stdio.h>
 
#include "foo.h"
#include "bar.h"
 
int main(void)
{
	printf("main function\n");
 
	foo();
	bar();
 
	return 0;
}
