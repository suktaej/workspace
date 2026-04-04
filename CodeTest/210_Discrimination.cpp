#include <iostream>
#include <vector>

bool isVaild(int ival)
{
    bool arr[10] = {false,};
    int cnt = 0;

    while (ival > 0)
    {
        int digit = ival % 10;
        if (digit != 0 && !arr[digit])
        {
            arr[digit] = true;
            ++cnt;

            if (cnt == 9)
                return true;
        }
        ival /= 10;
    }

    return true;
}

bool isVaild_Bit(int ival)
{
    int b = 0;

    while(ival > 0)
    {
        int digit = ival % 10;
        b |= (1 << digit);
        ival /= 10;
    }

    int mask = 0;
    for (int i = 1; i <= 9; ++i)
        mask |= (1 << i);

    return (b & mask) == mask;
    // return (b & 0b1111111110) == 0b1111111110;
}

int reverse(int ival)
{
    int temp = 0;
    while(ival > 0)
    {
        temp = temp * 10 + (ival % 10);
        ival/=10;
    }

    return temp;
}

int revsum(int fval, int sval)
{
    int frev = reverse(fval);
    int srev = reverse(sval);
    int res = reverse(frev+srev);

    return res;
}

int gcd(int a, int b)
{
    return b ? gcd(b, a%b) : a;
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

void eratosthenes(std::vector<bool>& vec, int p)
{
    vec.resize(p+1,true);
    vec[0] = false;
    vec[1] = false;

    for (long i = 2; i * i <= p; ++i)
        if(vec[i])
            for (int j = 2 * i; j <= p; j += i)
                vec[j] = false;
}

long nlm(long n, long p)
{
    std::vector<long> largePrimes;
    long res = 0;
    
    for(long i = 1; i * i <= p; ++i)
    {
        if (p % i == 0)
        {
            --n;

            if(n == 0)
                return i;

            if (i != p / i)
                largePrimes.push_back(p / i);
        }
    }

    for(int i = largePrimes.size() - 1; i >= 0; --i)
        if(--n == 0)
            return largePrimes[i];

    return -1;
}

int countDigit(int range, int target)
{
    int count = 0;
    for (int i = 1; i <= range; ++i) 
    {
        int temp = i;

        while (temp > 0) 
        {
            if (temp % 10 == target)
                count++;
            
            temp /= 10; 
        }
    }
    return count;
}

long long countDigit(long long n, int digit)
{
    long long count = 0;
    long long factor = 1; // 1, 10, 100, 1000 ... (현재 검사 중인 자릿수)

    while (factor <= n)
    {
        long long lower = n % factor;          // 현재 자릿수보다 낮은 숫자들
        long long current = (n / factor) % 10; // 현재 자릿수의 숫자
        long long higher = n / (factor * 10);  // 현재 자릿수보다 높은 숫자들

        // 1. 현재 자릿수가 찾는 숫자(digit)보다 작을 때
        if (current < digit)
            count += higher * factor;

        // 2. 현재 자릿수가 찾는 숫자(digit)와 같을 때
        else if (current == digit)
            count += (higher * factor) + (lower + 1);

        // 3. 현재 자릿수가 찾는 숫자(digit)보다 클 때
        else
        {
            // 찾는 숫자가 0일 경우, 맨 앞자리 0(Leading Zero)은 세지 않아야 함
            if (digit == 0 && higher > 0)
                count += (higher - 1) * factor;
            else if (digit != 0)
                count += (higher + 1) * factor;
            //  else
            // digit이 0이고 higher가 0이면 아무것도 더하지 않음 (맨 앞자리 0 방지)
        }

        factor *= 10; // 다음 자릿수(십의 자리 -> 백의 자리 등)로 이동
    }

    return count;
}

int bitArrayCheck(std::vector<int>& arr)
{
    int x = 0;
    int size = arr.size();

    for(int i=0;i<size;++i)
        x ^= i;

    for(int i : arr)
        x ^= i;

    return x;
}

bool intDigitsCheck(int ival, int pos)
{
    return (ival & (1 << pos)) != 0;
}

int memberCount(int time, const std::vector<int>& enter, const std::vector<int>& exit)
{
    constexpr int fulltime = 24;
    std::vector<int> exist(fulltime+1, 0);

    for (int i = 1; i <= fulltime; ++i)
        exist[i] = exist[i-1] + enter[i] - exit[i]; // [enter, exit)

    return exist[time];
}

int main()
{
    // std::cout<<reverse(12034506);
    std::cout<<gcd(5,10)<<' '<<gcd(32,6);
    std::cout<<'\n';
    std::cout<<lcm(5,10)<<' '<<lcm(32,6);
    std::cout<<'\n';
    std::cout<<nlm(3,10);
    return 0;
}