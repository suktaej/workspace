#include <stdio.h>
#include <fcntl.h>
#include <sys/socket.h>

int main(void)
{
    int fdes[3];

    fdes[0] = socket(PF_INET, SOCK_STREAM, 0);    // create socket
    fdes[1] = open("test.dat", O_CREAT, 0644);    // create file
    fdes[2] = socket(PF_INET, SOCK_DGRAM, 0);     // create socket

    for(int i=0;i<=2;++i)
    {
        printf("%d file descripter: %d",i,fdes[i]);
        close(fdes[i]);
    }

    return 0;
}