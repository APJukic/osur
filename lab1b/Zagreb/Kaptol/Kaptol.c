#include <stdio.h>
#include <string.h>
#include <math.h>
#include <postavke.h>

int funkcija_Kaptol ( const char *prefiks )
{

	char p[DULJINA];

	strcpy ( p, prefiks );
	strcat ( p, " -> Kaptol(");
	strcat(p,CURR_DIR);
	strcat(p,"/");
	strcat(p,__FILE__);
	strcat(p,")\n");
	printf ( "%s", p);

	funkcija_Medvedgradska ( p );
	funkcija_Radiceva ( p );
	funkcija_Jurjevska ( p );

	return 0;
}
