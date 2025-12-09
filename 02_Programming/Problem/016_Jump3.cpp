#include <string>

bool CheckThree(int num) 
{
    if (num % 3 == 0)
        return true;

    // Overhead 발생
    /*
    std::string str = std::to_string(num);

    if (str.find('3') != std::string::npos)
        return true;
    */

    // 정수 자리연산
    while(num > 0)
    {
        if(num % 10 == 3)
            return true;
        num /= 10;
    }

    return false;
}

void LoopFunc()
{
    int n = 10;
    int answer = 0;
    int count = 0;

    // 반복회수를 조정하므로 불필요 연산 증가(--i)
    /*
    for (int i = 0; i < n; ++i)
    {
        ++answer;

        if (CheckThree(answer))
            --i;
    }
    */

    while(count < n)
    {
        ++answer;
        
        if(!CheckThree(answer))
            ++count;
    }
}