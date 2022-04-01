#include <stdio.h>
#include <string.h>
#include <math.h>
#include <postavke.h>


int funkcija_Zagreb ( const char *prefiks )
{
	char p[DULJINA];

	strcpy ( p, prefiks );
	strcat ( p, " -> Zagreb (" );
	strcat(p,CURR_DIR);
	strcat(p,"/");
	strcat(p,__FILE__);

	strcat(p,")");

	printf ( "%s \n", p);

	funkcija_Sopot ( p );
	funkcija_Kaptol ( p );

	return 0;
}

