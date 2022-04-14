#include <stdio.h>
#include <api/prog_info.h>
#include <api/malloc.h>
#include "demo.h"


int demo(){

void *a,*b,*c,*d,*e;
	printf("malloc a\n");
	a = malloc(1110);
	printf("malloc returned %x(1110)\n\n\n", a);

	printf("malloc b\n");
	b = malloc(100);
	printf("malloc returned %x(100)\n\n\n", b);

	if (a){printf("Free a\n");
		free(a);}
	if (b){
		printf("Free b\n");
		free(b);}
	printf("malloc c\n");
	c=malloc(3999);
	printf("malloc returned %x(3999)\n\n\n", c);

	printf("malloc d\n");
	d = malloc(7286100);
	printf("malloc returned %x(7286100)\n\n\n", d);
	
	if (d){printf("Free d\n");
		free(d);}

	printf("malloc e\n");
	e = malloc(7300100);
	printf("malloc returned %x(7300100)\n\n\n", e);
	

	
return 0;
}
