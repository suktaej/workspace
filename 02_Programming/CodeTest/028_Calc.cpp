#include <string>
#include <vector>
#include <sstream>

int solution(std::string my_string) {
    int answer = 0;
    std::string buffer;
    bool oper = true;

    std::istringstream iss(my_string);

    while(iss >> buffer)
    {
        if ("+" == buffer)
            oper = true;
        else if ("-" == buffer)
            oper = false;
        else
            oper ? answer += std::stoi(buffer) : answer -= std::stoi(buffer);
    }

    return answer;
}

int Optimize(std::string str)
{
    int result = 0;
    int val = 0;
    bool oper = true;

    for(char ch : str)
    {
        if( ch >= '0' && ch <= '9')
            val = val * 10 + (ch - '0');
        else if(ch == '+')
        {
            result += oper ? val : -val;
            val = 0;
            oper = true;
        }
        else if(ch =='-')
        {
            result += oper ? val : -val;
            val = 0;
            oper = false;
        }
    }

    result += oper ? val : -val;
    return result;
}