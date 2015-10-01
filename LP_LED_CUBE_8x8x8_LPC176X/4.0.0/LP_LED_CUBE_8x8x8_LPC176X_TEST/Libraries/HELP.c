/****************************************************************************
	Luka Penger 2013
	HELP
****************************************************************************/

#include <HELP.h>

char *strdup(const char *s)
{
	char *p = malloc(strlen(s) + 1);   // allocate memory
	if (p != NULL)
			strcpy(p,s);                   // copy string
	return p;                          // return the memory
}

void file_size_format(U64 val, char *sp) {
  if(val >= (U64)1e9) {
    sp += sprintf (sp,"%d.",(U32)(val/(U64)1e9));
    val %= (U64)1e9;
    sp += sprintf (sp,"%03d.",(U32)(val/(U64)1e6));
    val %= (U64)1e6;
    sprintf (sp,"%03d.%03d GB",(U32)(val/1000),(U32)(val%1000));
  } else if (val >= (U64)1e6) {
    sp += sprintf (sp,"%d.",(U32)(val/(U64)1e6));
    val %= (U64)1e6;
    sprintf (sp,"%03d.%03d MB",(U32)(val/1000),(U32)(val%1000));
  } else if (val >= 1000) {
    sprintf (sp,"%d.%03d kB",(U32)(val/1000),(U32)(val%1000));
  } else {
		sprintf (sp,"%d B",(U32)(val));
	}
}

/****************************************************************************
                            End Of File
****************************************************************************/
