#ifndef _COMMONS_ 
#define _COMMONS_ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined (_MSC_VER)
    #define WIN32_LEAN_AND_MEAN
    #include <winsock2.h>
    #include <ws2tcpip.h>
    // #include <windows.h>
    #pragma comment(lib, "ws2_32.lib")
#else if (__GNUC__)
	#include <netinet/in.h>
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
#endif

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

#endif  //COMMONS