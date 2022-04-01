#include <stdio.h>
#include <postavke.h>

int funkcija_Sopot ( const char *prefiks )

{

	char p[DULJINA];
	strcpy ( p, prefiks );
	strcat ( p, " -> Sopot (" );
	strcat(p,CURR_DIR);
	strcat(p,"/");
	strcat(p,__FILE__);
	strcat(p,")\n");
	return printf (p);

}

