#include <stdio.h>

void print_bytes(void *ptr, int size) 
{
    unsigned char *p = ptr;
    int i;
    for (i=0; i<size; i++) {
        printf("%02hhX ", p[i]);
    }
    printf("\n");
}


int main()
{
	//Goal: save output of ptr address into a string

	int num = 1;
	
	printf("%p\n", &num);

	print_bytes(&num, sizeof(num));

}
