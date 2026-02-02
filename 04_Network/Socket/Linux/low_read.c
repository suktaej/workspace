#include "Commons.h"


#define BUFSIZE 100

int main(void)
{
    int fildes;
    char buf[BUFSIZE];

    fildes = open("data.txt", O_RDONLY);

    if(fildes == -1)
        error_handling("open() error");

    printf("File descriptor of open file is %d\n", fildes);

    if(read(fildes, buf, sizeof(buf)) == -1)
        error_handling("read() error");

    printf("file contents: %s", buf);

    close(fildes);

    return 0;
}