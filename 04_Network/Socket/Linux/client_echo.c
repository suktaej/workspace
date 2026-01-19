#include "Commons.h"

#include <string.h>
#include <sys/types.h>

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

#define BUFFER_SIZE 1024

int main(int argc, char** argv)
{
    int sock;
    char message[BUFFER_SIZE];
    int str_len;
    struct sockaddr_in serv_addr;

    if(argc != 3)
    {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");

    for(;;)
    {
        // 데이터 입력 및 전송
        fputs("Input message(q to quit): ", stdout);
        fgets(message, BUFFER_SIZE, stdin);

        if(!strcmp(message,"q\n"))
            break;

        write(sock, message, strlen(message));

        // 데이터 수신 및 출력
        str_len = read(sock, message, BUFFER_SIZE - 1);
        message[str_len] = 0;
        printf("Message from server: %s", message);

        close(sock);
        return 0;
    }
}