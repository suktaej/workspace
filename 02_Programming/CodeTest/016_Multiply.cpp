#include <vector>
#include <iostream>
#include <cmath>

// num[]의 자릿수 올림
void Normalize(std::vector<int>& num)
{
    num.push_back(0);
    // 자릿수 올림 처리
    for(int i =0;i<num.size();++i)
    {
        if(num[i] < 0)
        {
            int borrow = (std::abs(num[i]) + 9) / 10;
            num[i+1] -= borrow;
            num[i] += borrow * 10;
        }
        else
        {
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
    }

    while(num.size() > 1 && num.back() == 0)
        num.pop_back();
}

// 두 긴 자연수 간의 곱을 반환
// 각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어 있음
std::vector<int> Multiply(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> c(a.size() + b.size() + 1, 0);
    for(int i = 0; i< a.size(); ++i)
        for(int j =0; j<b.size();++j)
            c[i+j] += a[i] * b[j];

    Normalize(c);

    // for (auto &it = c.rbegin(); it != c.rend(); ++it)
    //     std::cout<<(*it);

    return c;
}

int main()
{

    Multiply({3,2,1},{6,5,4});
    return 0;
}