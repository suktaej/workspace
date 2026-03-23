#include "Commons.h"

int main(void)
{
    int serv_sock;
    char *serv_ip = "127.0.0.1";
    char *serv_port = "8080";
    struct sockaddr_in serv_addr;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(serv_ip);
    serv_addr.sin_port = htons(atoi(serv_port));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    printf("file descriptor %d successfully bind to %s:%s \n", serv_sock, serv_ip, serv_port);
    return 0;
}