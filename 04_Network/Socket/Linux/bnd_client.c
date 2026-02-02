#include "Commons.h"

int main(int argc, char** argv)
{
    int sock;
    int str_len, i;
    struct sockaddr_in serv_addr;

    char msg1[] = "Hello World!";
    char msg2[] = "I'm Client.";
    char message[128];

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

    write(sock, msg1, sizeof(msg1));    // 데이터 1차 전송
    write(sock, msg2, sizeof(msg2));    // 데이터 2차 전송 
    sleep(10);

    for(i = 0; i < 4; i++)
    {
        str_len = read(sock, message, sieof(message) - 1);
        message[str_len] = 0;
        printf("Message from server: %s \n", message);
    }

    close(sock);
    return 0;
}
