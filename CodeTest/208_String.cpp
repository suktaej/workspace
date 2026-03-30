#include <iostream>
#include <string>
#include <sstream>

int myStrlen(char* str)
{
    int n = 0;
    while(true)
    {
        char c;
        c = *(str+n);

        if(c == '\0')
            break;
        ++n;
    }
    return n;
}

void myStrcpy(char *dest, const char *src)
{
    int n = 0;
    while(true)
    {
        char c;
        c = *(src + n);
        *(dest + n) = c;
        
        if(c == '\0')
            break;
        ++n;
    }
}

void reverse(char* output, int outputArraySize, const char* input)
{
    // char* rev;
    char rev[128] ={};
    int idx = 0;
    int outIdx = 0;

    for(int i =0;i< outputArraySize+1;++i)
    {
        if(input[i] == ' ')
        {
            while(idx)
                output[outIdx++] = rev[--idx];

            output[outIdx++] = ' ';
            continue;
        }
        else if(input[i]=='\0')
        {
            while(idx)
                output[outIdx++] = rev[--idx];
            
            output[outIdx++] = '\0';
            return;
        }

        *(rev+idx) = input[i];
        ++idx;
    }

}

void reverse_default(char* output, int outputArraySize, const char* input)
{
    int idx = 0;
    int i = 0;
    while(input[i]!='\0')
    {
        int start = i;
        while(input[i]!=' ' && input[i]!='\0')
            ++i;

        int end = i - 1;

        while(end>=start)
            output[idx++] = input[end--];

        if(input[i]==' ')
        {
            output[idx++] = ' ';
            ++i;
        }
    }

    output[idx] = '\0';
}

void reverseRange(char* str, int l, int r)
{
    while (l < r)
    {
        char tmp = str[l];
        str[l++] = str[r];
        str[r--] = tmp;
    }
}

void reverseWords(char* str)
{
    int len = strlen(str);

    reverseRange(str, 0, len - 1);

    int start = 0;
    for (int i = 0; i <= len; ++i)
    {
        if (str[i] == ' ' || str[i] == '\0')
        {
            reverseRange(str, start, i - 1);
            start = i + 1;
        }
    }
}

void intToStr(const int& inp, char* str)
{
    int idx = 0;

    if (inp == 0)
    {
        str[idx++] = '0';
        str[idx] = '\0';
        return;
    }
    
    long n = inp;
    bool isNegative = false;

    if(n < 0)
    {
        isNegative = true;
        n *= -1;
    }

    while (n > 0)
    {
        str[idx++] = '0' + (n % 10);
        n /= 10;
    }

    if(isNegative)
        str[idx++] = '-';

    for (int i = 0; i < idx / 2; ++i)
    {
        char temp = str[i];
        str[i] = str[idx - 1 - i];
        str[idx-1-i] = temp;
    }

    str[idx] = '\0';
}

void deleteDupChar(const char* str)
{
    int idx = 0;
    char buffer[128];

    for(int i=0;str[i]!='\0';++i)
    {
        if(str[i] != str[i+1])
            buffer[idx++] = str[i];
    }

    buffer[idx] = '\0';

    std::cout<<buffer;
}

int main()
{
    char* str = "hello";
    char res[100];
    // myStrcpy(str,res);
    // std::cout<<res;

    char* inp = "hello world this is test ground";
    int size = strlen(inp);
    char oup[100];

    reverse(oup,size,inp);
    // std::cout<<oup;

    int intInp = -1919;
    char charOutp[128] = {};
    intToStr(intInp,charOutp);

    std::cout<<charOutp;

    char* delchar = "aaabbbcccdc";
    deleteDupChar(delchar);
    return 0;
}