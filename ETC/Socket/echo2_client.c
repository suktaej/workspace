#include "Commons.h"

#define BUFFER_SIZE 1024

int main(int argc, char** argv)
{
    int sock;
    char message[BUFFER_SIZE];
    int str_len, recv_len, recv_cnt;
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

    while(1)
    {
        // 데이터 입력 및 전송
        fputs("Input message(q to quit): ", stdout);
        fgets(message, BUFFER_SIZE, stdin);

        if(!strcmp(message,"q\n"))
            break;

        // 데이터 전송
        str_len = write(sock, message, strlen(message));

        // 데이터 수신
        for(recv_len = 0; recv_len < str_len; )
        {
            recv_cnt = read(sock, &message[recv_len], str_len - recv_len);
        
            if(recv_cnt == -1)
                error_handling("read() error!");
       
            recv_len += recv_cnt;
        }

        message[recv_len] = 0;
        printf("Message from server: %s", message);
    }
    
    close(sock);
    return 0;
}