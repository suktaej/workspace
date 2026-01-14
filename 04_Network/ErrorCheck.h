#ifndef _ERRORCHECK_
#define _ERRORCHECK_

#include <stdio.h>
#include <stdlib.h>

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

#endif  //ERRORCHECK