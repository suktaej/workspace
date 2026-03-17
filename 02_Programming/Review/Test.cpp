#include <iostream>
#include <vector>
#include <algorithm>

/*
int n, m;
std::vector<std::vector<int>> graph;
std::vector<bool> visited;

struct disjointSet
{
    std::vector<int> parents;
    std::vector<int> rank;
    int numSet;

    disjointSet(int n)
    : parents(n+1), rank(n+1), numSet(n)
    {
        for(int i=0;i<=n;++i)
            parents[i]= i;
    }

    int find(int i)
    {
        if(parents[i]==i)
            return i;

        return parents[i] = find(parents[i]);
    }

    bool unite(int i,int j)
    {
        int rooti = find(i);
        int rootj = find(j);

        if(rooti==rootj)
            return false;

        if(rank[rooti] < rank[rootj])
            std::swap(rooti, rootj);

        parents[rootj] = rooti;

        if(rank[rooti]==rank[rootj])
            ++rank[rooti];
        
        --numSet;
        return true;
    }

    int Components()
    {
        // int cnt = 0;

        // for(int i=1;i<=n;++i)
        //     if(parents[i]==i)
        //         ++cnt;

        // return cnt;
        return numSet;
    }
};

void bfs(int src)
{
    std::queue<int> q;

    q.push(src);
    visited[src] = true;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(const int& node : graph[cur])
        {
            if(visited[node])
            {
                continue;
            }

            q.push(node);
            visited[node] = true;
        }
    }
}

void dfs(int node)
{
    visited[node] = true;
    
    for(const int& next : graph[node])
        if(!visited[next])
            dfs(next);
}

void ds()
{
    struct disjointSet s(n);

    for(int i=1;i<=n;++i)
        for(const auto& j : graph[i])
            s.unite(i,j);

    std::cout<<s.Components();
}

int main()
{
    std::cin>>n>>m;
    graph.resize(n+1);
    visited.resize(n+1,false);

    for(int i=0;i<m;++i)
    {
        int u, v;
        std::cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    ds();

    // int cnt = 0;

    // for(int i=1;i<=n;++i)
    // {
    //     if (!visited[i])
    //     {
    //         ++cnt;
    //         // bfs(i);
    //         // dfs(i);
    //     }
    // }

    // std::cout<<cnt;

    return 0;
}


// int main()
// {
//     int n;
//     int blocks[] = {1,2,2};
//     std::cin>>n;

//     std::vector<int> dp(n+1,0);
//     dp[0]=1;
    
//     for(int i =1;i<=n;++i)
//         for(const int& block : blocks)
//             if(i-block >= 0)
//                 dp[i] += dp[i-block];
    
//     std::cout << dp[n];
    
//     return 0;
// }

int main()
{
    int x = ((0xEF >> 1) << 2) & 0xF;
    // 11101111
    // 01110111
    // 11011100
    // 00001111
    // 00001100
    std::cout<<x;
    return 0;
}

//bigclass는 멤버변수가 많은 클래스
//잠재적으로 문제가 될 수 있는 부분 2가지를 구하라
class BigClass
{
    char* m_longstr;

    void doSomething(BigClass a)
    {
        for(int i=0;i<strlen(a.m_longstr);++i)
        {
            doSomething(a.m_long)
        }
    }
}

// doSomething을 통해 m_longstr이 전달되면, BigClass는 m_longstr

// void func(char*& str)
// {
//     str = "changed";
// }

// int main()
// {
//     char* temp = "string";
//     func(temp);
//     std::cout<<temp;
//     return 0;
// }

// char* func(int num)
// {
//     char str[128];
//     sprintf_s(str, sizeof(str), "number : %d", num);
//     return str;
// }

// bool Store(unsigned int money, unsigned int count, unsigned int price)
// {
//     return money >= price*count;
// }

// target 변수의 n번째 bit를 flag에 따라 on/off시킬 수 있도록 함수를 완성해라
void func(int& target, int n ,bool flag)
{
    if(flag)
        target |= (1 << n);
    else
        target &= ~(1 << n);

    target ^= (1 << n);
}

// pow함수를 bit연산자를 이용해서 구현
int pow(int base, int exp)
{
    int res = 1;
    while(exp)
    {
        if(exp & 1)
            res *= base;
        base*= base;

        exp >>= 1;
    }

    return res;
}

// 13, 27 뒤바뀐 비트 개수
// 1110 
// 0001 1011
int diff()
{
    int a = 13;
    int b = 27;
    int c = a ^ b;
    int cnt = 0;

    while(c)
    {
        c &= (c - 1);
        ++cnt;
    }

    std::cout<<cnt;
}


// apple, alepp처럼 문자 배열이 다르지만 
// 길이와 문자구성이 같은 단어를 판별하는 함수 생성

bool diff(const std::string& a,const std::string& b)
{
    if (a.length() != b.length())
        return false;
    
    int alp[26] = {0,};

    for(const char& c : a)
        ++alp[c-'a'];

    for(const char& c : b)
        if (--alp[c - 'a'] < 0)
            return false;

    return true;
}

bool diff(std::string a,std::string b)
{
    std::sort(a.begin(),a.end());
    std::sort(b.begin(),b.end());

    std::cout<<a<<' '<<b<<'\n';

    if (a == b)
        return true;

    return false;
}

void func()
{
    int a= 10, b= 100, c =20;
    int r1 = a * b / c;
    int r2 = a / c * b;
    std::cout<<r1<<' '<<r2;
}
=====*/ 

// N크기인 정방형 배열이 0과 1로 이루어져 있을 때 (x,y)좌표로부터 연속된 0을 1로 바꾸는 함수를 생성하라

int main()
{
    func();
    return 0;
}