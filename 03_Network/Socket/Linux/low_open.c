#include "Commons.h"

int main(void)
{
    int fildes;
    char buf[] = "Text writing\n";

    // 파일 생성
    fildes = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if(fildes == -1)
        error_handling("open() error!");

    printf("The file descriptor of generated file is %d", fildes);

    // 생성한 파일에 버퍼 전달
    if(write(fildes, buf, sizeof(buf)) == -1)
        error_handling("write() error!");

    close(fildes);
    return 0;
}