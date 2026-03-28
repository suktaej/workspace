#include <iostream>
#include <vector>

void bottomUp(int n)
{
    std::vector<int> arr;
    arr.resize(n);
    arr[0]=1;
    arr[1]=1;
   
    for(int i=2;i<n;++i)
        arr[i] = arr[i-1]+arr[i-2];

    std::cout<<arr[n-1];
}

void twoValue(int n)
{
    int f = 1;
    int s = 1;

    for(int i=2;i<=n;++i)
    {
        int temp = s;
        s += f;
        f = temp;
    }

    std::cout<<f;
}

std::vector<int> memo;

int topDown(int n)
{
    // 0-base : n-1 입력값 필요
    // if(n<=1)
        // return 1;
    
    // 1-base
    if(n<=2)
        return 1;

    if(memo[n]!=0)
        return memo[n];

    return memo[n] = topDown(n-1) + topDown(n-2);
}

int recursion(int n)
{
    // 0-base
    // if(n==0) return 0;
    // if(n==1) return 1;

    // 1-base
    if (n <= 2)
        return 1;

    int res = 0;
    res = recursion(n-1) + recursion(n-2);

    return res;
}

int main()
{
    int n;
    std::cin>>n;

    memo.resize(n+1);
    std::cout<<topDown(n);
    bottomUp(n);
    std::cout<<recursion(n);

    return 0;
}