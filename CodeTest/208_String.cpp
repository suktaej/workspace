#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

void deleteDupStr(char* src, const char* str) 
{
    if (!src || !str) 
        return;

    int srcLen = strlen(src);
    int strLen = strlen(str);
    if (strLen == 0) 
        return;

    int widx = 0;
    int ridx = 0;

    while (src[ridx] != '\0')
    {
        if(strncmp(&src[ridx],str,strLen) == 0)
            ridx += strLen;
        else
            src[widx++] = src[ridx++];
    }

    src[widx] = '\0';
}

void deleteDupStr_default(char* src, const char* str) 
{
    if (!src || !str) 
        return;

    int srcLen = strlen(src);
    int strLen = strlen(str);
    if (strLen == 0) 
        return;

    std::string source(src);
    std::string toDelete(str);

    size_t pos = 0;

    while ((pos = source.find(toDelete, pos)) != std::string::npos) 
        source.erase(pos, strLen);

    strcpy(src, source.c_str());
}

void duplicateElementDelete(std::vector<int>& arr)
{
    // std::sort(arr.begin(), arr.end());
    // auto last = std::unique(arr.begin(), arr.end());
    // arr.erase(last, arr.end());
    // std::erase_if(arr, [](int a, int b){ return a == b; });
}

void deleteSomeElement(std::vector<int>& arr, int target)
{
    auto it = std::find(arr.begin(), arr.end(), target);
    if (it != arr.end())
        arr.erase(it);
}

bool anagram(const std::string& str, const std::string& target)
{
    int cnt[26] = {0,};
    for(const char& c : str)
        ++cnt[c-'a'];

    for(const char& c : target)
    {
        if (--cnt[c - 'a'] < 0)
            return false;
    }

    return true;
}

bool anagramCpp( std::string str,  std::string target)
{
    std::sort(str.begin(),str.end());
    std::sort(target.begin(),target.end());
    
    // return strcmp(str.c_str(),target.c_str()) ? false : true;
    if(str == target)
        return true;
}

void stringCopy(const std::string& src, char* target)
{
    // strcpy(target,src.c_str());
    int size = src.length();
    for(int i=0;i<size;++i)
        target[i] = src[i];
    
    target[size+1] = '\0';
}

bool stringCompare(const std::string& str, const std::string& comp)
{
    int strSize = str.length();
    int compSize = comp.length();

    if(strSize != compSize)
        return false;

    for(int i=0;i<strSize;++i)
        if(str[i]!=comp[i])
            return false;

    return true;
}

bool PalindromeChar(const std::string& str)
{
    int size = str.length();
    for (int i = 0; i < size / 2; ++i)
        if (str[i] != str[size - 1 - i])
            return false;

    return true;
}

char* findStr(const char* src, int srcSize, const char* target, int targetSize)
{
    if (src == nullptr || target == nullptr || targetSize > srcSize) 
        return nullptr;

    for (int i = 0; i <= srcSize - targetSize; ++i)
        if(src[i] == target[0] && strncmp(&src[i],target,targetSize) == 0)
                return const_cast<char*>(&src[i]);

    return nullptr;
}

int main()
{
    // char* str = "hello";
    // char res[100];
    // myStrcpy(str,res);
    // std::cout<<res;

    // char* inp = "hello world this is test ground";
    // int size = strlen(inp);
    // char oup[100];

    // reverse(oup,size,inp);
    // // std::cout<<oup;

    // int intInp = -1919;
    // char charOutp[128] = {};
    // intToStr(intInp,charOutp);
    // std::cout<<charOutp;

    // char* delchar = "aaabbbcccdc";
    // deleteDupChar(delchar);

    // char inpstr[] = "abcabcaadf";
    // char* delstr = "abc";
    // deleteDupStr(inpstr,delstr);
    // std::cout<<inpstr;

    std::string str = "hello";
    char temp[64];
    stringCopy(str,temp);
    std::cout<<temp;
    return 0;
}