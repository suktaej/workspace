#include <string>
#include <vector>

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

std::string solution(std::string s) 
{
    std::string answer = "";
    return answer;
}