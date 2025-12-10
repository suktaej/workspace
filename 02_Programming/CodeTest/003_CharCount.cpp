#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>

int Count7(std::vector<int> array) {
    int answer = 0;

    for(int i : array)
    {
        while (i != 0)
        {
            if (i % 10 == 7)
                ++answer;
            i /= 10;
        }
    }

    return answer;
}

int SumDigit(std::string my_string) {
    int answer = 0;
    int temp = 0;

    for(char c : my_string)
    {
        if (c <= '9' && c >= '0')
            temp = temp * 10 + (c - '0');
        else
        {
            answer += temp;
            temp = 0;
        }
    }

    answer += temp;

    return answer;
}

std::string OnlyOnceAppearChar(std::string s) 
{
    std::string answer = "";
    std::vector<int> cnt(26,0);

    for(char& c : s)
        ++cnt[c-'a'];

    for (int i = 0; i < cnt.size(); ++i)
        if (cnt[i] == 1)
            answer.push_back(static_cast<char>('a'+i));

    return answer;
}

int CountK(int i, int j, int k) {
    int answer = 0;

    for (int m = i; m <= j; ++m)
    {
        int n = m;

        while (n != 0)
        {
            if (n % 10 == k)
                ++answer;
            n /= 10;
        }
    }

    return answer;
}

int Reverse(std::string before, std::string after) 
{
    for(int i=0; i<before.size();++i)
        if(before[i]!=after[after.size()-1-i])
            return 0;

    // 문자열을 뒤집어 새 문자열 생성
    // std::string beforeReversed(before.rbegin(), before.rend());

    // 문자열 뒤집기
    // std::reverse(before.begin(),before.end());

    return 1;
}

int Rearrange(std::string before, std::string after) 
{
    std::vector<int> cnt(26);

    for(char& c : before)
        ++cnt[c-'a'];

    for(char& c : after)
        --cnt[c-'a'];

    for(int& i : cnt)
        if(0!=i)
            return 0;

    return 1;

    // std::sort(before.begin(), before.end());
    // std::sort(after.begin(), after.end());
    // return before == after ? 1 : 0;
}

std::string Morse(std::string letter) {
    
    std::unordered_map<std::string,std::string> morse = {
        {".-" , "a"},
        {"-..." , "b"},
        {"-.-." , "c"},
        {"-.." , "d"},
        {"." , "e"},
        {"..-." , "f"},
        {"--." , "g"},
        {"...." , "h"},
        {".." , "i"},
        {".---" , "j"},
        {"-.-" , "k"},
        {".-.." , "l"},
        {"--" , "m"},
        {"-." , "n"},
        {"---" , "o"},
        {".--." , "p"},
        {"--.-" , "q"},
        {".-." , "r"},
        {"..." , "s"},
        {"-" , "t"},
        {"..-" , "u"},
        {"...-" , "v"},
        {".--" , "w"},
        {"-..-" , "x"},
        {"-.--" , "y"},
        {"--.." , "z"}
    };
 
    std::istringstream iss(letter);
    std::string token;
    std::string answer = "";
    
    while(iss>>token)
        answer.append(morse[token]);

    return answer;
}

int main(void)
{
    return 0;
}