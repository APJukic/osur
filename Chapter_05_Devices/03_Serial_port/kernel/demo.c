#include <stdio.h>
#include <api/prog_info.h>
#include <api/malloc.h>
#include "demo.h"


int demo(){
//void *a,*b;
// *b, *c, *d;
//size_t  size_b,size_a;
//, size_c, size_d, size_e; 
//size_a = 10000;
//size_b = 64;

//a = malloc(size_a);
//b = malloc(size_b);
//free(b);
//printf("%d sa\n",sizeof(*a));
//printf("%d sa\n",*(size_t*)b);

//void *a1;
//size_t size_a1 = 100;
//a1 = malloc(size_a1);
void *ptr1, *ptr2,*ptr3,*a;
	printf("malloc ptr1\n");
	ptr1 = malloc(1110);
	printf("malloc returned %x(9999999999)\n", ptr1);

	printf("malloc ptr2\n");
	ptr2 = malloc(100);
	printf("malloc returned %x(123)\n", ptr2);
	printf("malloc ptra\n");
	a = malloc(1000000000);
	printf("malloc returned %x(123)\n", a);

	if (ptr1){printf("Free ptr1\n");
		free(ptr1);}
	if (ptr2){
		printf("Free ptr2\n");
		free(ptr2);}
	printf("malloc ptr3\n");
	ptr3=malloc(3999);
	printf("malloc returned %x(123)\n", ptr3);
return 0;
}
