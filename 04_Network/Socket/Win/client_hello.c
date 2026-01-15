#include "Commons.h"

#include <string.h>
#include <winsock2.h>

int main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;
    char message[30];
    int strLen;

    if(argc!=3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // Load Winsock 2.2 DLL
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        error_handling("WSAStartup() error!");

    // Create a TCP socket
    hSocket=socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket==INVALID_SOCKET)
        error_handling("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(argv[1]);
    servAddr.sin_port=htons(atoi(argv[2]));

    // Request connection to server
    if(connect(hSocket, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
        error_handling("connect() error");

    // Receive data from server
    strLen = recv(hSocket, message, sizeof(message) - 1, 0);
    if (strLen == -1)
        error_handling("read() error");

    message[strLen]=0;
    printf("Message from server: %s \n", message);

    // Close the socket
    closesocket(hSocket);
    WSACleanup();
    return 0;
}