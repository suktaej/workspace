#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIDX 3

void StringToken(char* str)
{
    // strtok(token) 활용
    // strtok함수 내부에 static variable 보유
    // 첫 번째 탐색 시 구분자가 있는 지점에 \0 삽입
    // 이후 pointer는 그 다음 문자를 가르킴

    char* divStr1 = strtok(str," ");
    // 새로운 문자열이 없으므로(NULL) 이전 static 변수에 주소에서 시작
    char* divStr2 = strtok(NULL," ");
    char* divStr3 = strtok(NULL," ");

    printf("first word: %s\n", divStr1);
    printf("second word: %s\n", divStr2);
    printf("third word: %s\n", divStr3);

    // 첫 번째 공백이 \0으로 바뀌었으므로 "apple"
    // 원본도 파괴(Destructive)
    printf("original str: %s\n", str);
}

void StringTokenS(char* str)
{
    char *temp = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(temp,str);

    printf("original str: %s\n",temp);
    
    char* token;
    char* context;

    token = strtok_s(temp, " ", &context); // msvc 지원함수, linux에서는 strtok_r
    printf("after truncate first str: %s\n",temp);
    printf("context: %s\n",context);
    printf("token: %s\n",token);
    
    token = strtok_s(NULL, " ", &context);
    printf("after truncate second str: %s\n",temp);
    printf("context: %s\n",context);
    printf("token: %s\n",token);

    free(temp);
}

void StringCopy(const char* str)
{
    // string일 경우 마지막 문자에 \0이 포함되므로 +1 필요
    char* temp1 = (char*)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(temp1,str);
    free(temp1);

    char* temp2 = strdup(str); // Dynamic (malloc+copy)
    free(temp2);

    char temp3[100];  
    strcpy(temp3, str); // Static
}

void StringSeprate(const char* str)
{
    char *temp = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(temp,str);

    printf("original str: %s\n",temp);
    
    char* token;

#if defined(_MSC_VER)
    char* context;
    token = strtok_s(temp," ",&context);
#elif defined(__GNUC__)
    // POSIX(Linux) 지원 함수, MSVC library 미지원
    token = strsep(&temp," ");
#endif
    printf("after truncate first str: %s\n",temp);
    printf("token: %s\n",token);

    free(temp);
}

void TypeConversion(char* str)
{
    char* temp = strdup(str);

    int val[MAXIDX];
    int indexCount = 0;

    char* token;
    char* context;

    // 첫 번째 토큰 추출
    token = strtok_s(temp," ",&context);

    // 토큰이 존재하고 배열의 공간이 남아있을 때
    while(token!=NULL && indexCount < MAXIDX)
    {
        // 현재의 토큰을 전환
        val[indexCount++] = atoi(token);
        // 다음 토큰 추출
        token = strtok_s(NULL, " ", &context);
    }

    for(int i=0;i<indexCount;++i)
        printf("%d ",val[i]);

    free(temp);
}

int main()
{
    char str[100] = "apple banana orange";
    char val[100] = "10 20 5";
    
    StringTokenS(str);
    TypeConversion(val);
    
    return 0;
}