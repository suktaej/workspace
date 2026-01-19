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

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;
	char message[] = "Hello world";

	if(argc!=2)
	{
		printf("Usage: %s <port> \n",argv[0]);
		exit(1);
	}

	// 서버 소켓생성
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	// 소켓에 주소할당
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	// 연결요청 대기상태 진입
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	// 연결요청 수락
	
	for(;;)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

		if (clnt_sock == -1)
			error_handling("accpet() error");

		// 데이터 전송
		write(clnt_sock, message, sizeof(message));
		// 연결종료
		close(clnt_sock);
	}

	return 0;
}