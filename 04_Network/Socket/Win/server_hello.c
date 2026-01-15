#include "Commons.h"

#include <string.h>
#include <winsock2.h>

int main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET hServSock;
    SOCKET hClntSock;
    SOCKADDR_IN servAddr;
    SOCKADDR_IN clntAddr;
    int szClntAddr;
    char message[] = "Hello world\n";

    if(argc!=2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // Load Winsock 2.2 DLL
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        error_handling("WSAStartup() error!");

    // Create a TCP socket
    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if(hServSock==INVALID_SOCKET)
        error_handling("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(atoi(argv[1]));

    // Bind the socket
    if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
        error_handling("bind() error");

    // Listen for incoming connections
    if(listen(hServSock, 5)==SOCKET_ERROR)
        error_handling("listen() error");

    szClntAddr=sizeof(clntAddr);
    // Accept a client connection
    hClntSock=accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
    if(hClntSock==INVALID_SOCKET)
        error_handling("accept() error");

    // Send data to the client
    send(hClntSock, message, sizeof(message), 0);

    // Close the client and server sockets
    closesocket(hClntSock);
    WSACleanup();
    return 0;
}