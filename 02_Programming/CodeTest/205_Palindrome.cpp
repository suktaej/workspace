#include <iostream>
#include <string>

std::string str = "aabbaa";

bool strCheck()
{
    int size = str.size();
    int mid = size / 2;

    for(int i=0;i<mid;++i)
    {
        if(str[i]!=str[size-i])
            return false;
    }

    return true;
}

int revInt(int inp)
{
    int res = 0;
    while (inp > 0)
    {
        res = res * 10 + (inp % 10);
        inp /= 10;
    }

    return res;
}

bool isPalindrome(int x) 
{
    // 예외 처리: 음수이거나, 0이 아닌데 0으로 끝나는 경우
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int revertedNumber = 0;
    while (x > revertedNumber) {
        revertedNumber = revertedNumber * 10 + (x % 10);
        x /= 10;
    }

    // 숫자의 길이가 짝수일 때: x == revertedNumber (예: 12 | 12)
    // 숫자의 길이가 홀수일 때: x == revertedNumber / 10 (예: 12 | 123 에서 3 제거)
    return x == revertedNumber || x == revertedNumber / 10;
}

bool solve()
{
    int orth = 123454321;
    int rev = revInt(orth);
    
    if(0 == (orth-rev))
        return true;
    else
        return false;
}

int main()
{

    solve();
    return 0;
}