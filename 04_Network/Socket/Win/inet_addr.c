#include <stdio.h>

#if defined(__GNUC__)
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
#elif defined(_MSC_VER)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#endif

void inet_addr_exp()
{
    const char* addr1 = "1.2.3.4";
    const char* addr2 = "1.2.3.256";
    unsigned long conv_addr;

    conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
        printf("Error occurred during conversion of %s \n", addr1);
    else
        printf("Network ordered integer address of %s: %#lx \n", addr1, conv_addr);

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
        printf("Error occurred during conversion of %s \n", addr2);
    else
        printf("Network ordered integer address of %s: %#lx \n", addr2, conv_addr);
}

void inet_aton_exp()
{
    const char* addr1 = "1.2.3.4";
    int result;

#if defined(__GNUC__)
    struct sockaddr_in addr_inet;
    
    result = inet_aton(addr1, &addr_inet.sin_addr);
#elif defined(_MSC_VER)
    // WSADATA wsa;
    // WSAStartup(MAKEWORD(2,2), &wsa);
    SOCKADDR_IN addr_inet;
    
    result = InetPtonA(AF_INET, addr1, &addr_inet.sin_addr);
#endif

    if (result == 0)
        printf("Error occurred during conversion of %s \n", addr1);
    else
        printf("Network ordered integer address of %s: %#lx \n", addr1, addr_inet.sin_addr.s_addr);
    
#if defined(_MSC_VER)
    // WSACleanup();
#endif
}

void inet_ntoa_exp()
{
    struct sockaddr_in addr1, addr2;
    char* str;

    addr1.sin_addr.s_addr = htonl(0x01020304); 
    addr2.sin_addr.s_addr = htonl(0x01010101);
    
    str = inet_ntoa(addr1.sin_addr);
    printf("String address of %#lx: %s \n", addr1.sin_addr.s_addr, str);

    inet_ntoa(addr2.sin_addr); // 내부 정적 버퍼 덮어쓰기
    printf("String address of %#lx: %s \n", addr2.sin_addr.s_addr, str);
}

void inet_ntop_exp()
{
    struct sockaddr_in addr1;
    char str[INET_ADDRSTRLEN];

    addr1.sin_addr.s_addr = htonl(0x01020304);

    inet_ntop(AF_INET, &addr1.sin_addr, str, INET_ADDRSTRLEN);
    printf("String address of %#lx: %s \n", addr1.sin_addr.s_addr, str);
}

int main(int argc, char **argv)
{
    // inet_addr_exp();
    // inet_aton_exp();
    // inet_ntoa_exp();
    inet_ntop_exp();

    return 0;
}