#include <vector>
#include <cmath>
constexpr int MIN_LEN = 50;

// num[]의 자릿수 올림
void Normalize(std::vector<int>& num)
{
    num.push_back(0);
    // 자릿수 올림 처리
    for (int i = 0; i + 1 < num.size(); ++i)
    {
        if(num[i] < 0)
        {
            int borrow = (-1 * num[i] + 9) / 10;
            num[i + 1] -= borrow;
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

// a+=b*(10^k)
void AddTo(std::vector<int>& a, const std::vector<int>& b, int k) {

    if (a.size() < b.size() + k + 1)
        a.resize(b.size() + k + 1, 0);

    for (int i = 0; i < b.size(); ++i) 
        a[i + k] += b[i];
}

// a-=b let(a>=b);
void SubFrom(std::vector<int>& a,const std::vector<int>& b)
{
    for(int i = 0; i< b.size(); ++i)
        a[i] -= b[i];
}

std::vector<int> Karatsuba(const std::vector<int>& a, const std::vector<int>& b)
{
    int an = a.size();
    int bn = b.size();

    // a가 b보다 짧을 경우 둘을 변경
    if(an < bn)
        return Karatsuba(b,a);

    // base case : a,b가 빈 경우
    if(an == 0 || bn == 0)
        return std::vector<int>();

    // base case : a가 짧을 경우 O(n^2) 곱으로 변경
    if(an <= MIN_LEN)
        return Multiply(a,b);

    // a,b를 half자리로 분리
    int half = an / 2;
    std::vector<int> a0(a.begin(),a.begin()+half);
    std::vector<int> a1(a.begin()+half, a.end());
    std::vector<int> b0(b.begin(), b.begin() + std::min<int>(b.size(),half));
    std::vector<int> b1(b.begin() + std::min<int>(b.size(),half), b.end());

    std::vector<int> z2 = Karatsuba(a1,b1);
    std::vector<int> z0 = Karatsuba(a0,b0);
    AddTo(a0,a1,0);
    AddTo(b0,b1,0);
    std::vector<int> z1 = Karatsuba(a0,b0);
    SubFrom(z1,z0);
    SubFrom(z1,z2);

    std::vector<int> res;
    AddTo(res,z0,0);
    AddTo(res,z1,half);
    AddTo(res,z2,half+half);
    Normalize(res);

    return res;
}