#include <stdio.h>
#include <postavke.h>

int funkcija_Radiceva ( const char *prefiks )
{
	char p[DULJINA];
	strcpy ( p, prefiks );
	strcat ( p, " -> Radiceva ul. (" );
	strcat(p,CURR_DIR);
	strcat(p,"/");
	strcat(p,__FILE__);
	strcat(p,")\n");
	return printf (p);

}
