#include <stdio.h>
#include <postavke.h>

int main ()
{	
	printf("\n\n");

		char p[DULJINA];
		strcpy ( p, "****Hrvatska (");
		strcat(p,CURR_DIR);
		strcat(p,"/");
		strcat(p,__FILE__);
		strcat(p,")");
		printf(p);
		printf("\n");

	funkcija_Zagreb (p);
	funkcija_Split (p);
	printf("\n");
	nadoknada_lab1();
	return 0;
}
