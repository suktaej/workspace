#include <iostream>
#include <cstring>

/*
// stack area size problem
void func1()
{
    constexpr int cnt = 128;
    int slot[cnt][cnt] = { 0, };

    for (int i = 0; i < cnt; ++i)
    {
        for (int j = 0; j < cnt; ++j)
        {
            slot[i][j] = i * cnt + j;
            std::cout<<slot[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}

void func2()
{
    int test[10];

    for(int i=0;i<32;++i)
        test[i] = i*100;
}

class c1
{
    char* m_str;
    int m_size;

    c1(const char* str)
    {
        m_size = strlen(str)+1;
        // strncpy(m_str,str,m_size);
        strcpy_s(m_str, m_size, str);
    }
};

class parent
{
public:
    int i;
    char c;

    parent(){std::cout<<"parent constructor\n";};
    virtual ~parent(){std::cout<<"parent destructor\n";}

    virtual void func1(){std::cout<<"parent func1\n";};
    virtual void func2(){std::cout<<"parent func2\n";};
};

class child1 : public parent
{
public:
    float f;

    child1(){std::cout<<"child1 constructor\n";};
    virtual ~child1(){std::cout<<"child1 destructor\n";};

    virtual void func1(){std::cout<<"child1 func1\n";};
    void func2(){std::cout<<"child1 func2\n";};
    void func3(){std::cout<<"child1 func3\n";};
};

class child2 : public child1
{
public:
    child2(){std::cout<<"child2 constructor\n";};
    virtual ~child2(){std::cout<<"child2 destructor\n";};

    virtual void func1(){std::cout<<"child2 func1\n";};
    void func2(){std::cout<<"child2 func2\n";};
    void func3(){std::cout<<"child2 func3\n";};
};
class child3 : public child2
{
public:
    child3(){std::cout<<"child3 constructor\n";};
    virtual ~child3(){std::cout<<"child3 destructor\n";};
};

void inheritance()
{
    parent* p = new child2;
    p->func1();
    p->func2();
    p->func3();
    delete p;

    int i = sizeof(parent);
    int ii = sizeof(child1);
    int iii = sizeof(child2);
    int iiii = sizeof(child3);
}
*/

/*
class A
{
public:
    int Add1(int a, int b, int c= 0){return a+b;}
    int Add2(int a, int b =0, int c){return a*(b+c);}
};
class B
{
public:
    int Add1(int a, int b, int c= 0){return a+b;}
    int Add2(int a=0, int b =0, int c){return a*(b+c);}
};

void test()
{
    A a;
    a.Add(2,3);
    B b;
    b.Add(3,4);
}

void loopTest()
{
    unsigned int a = 150;
    for(unsigned char i=0;i<a*2;++i)
    {}
}
*/

/*
class MyString1
{
private:
    char* m_str;

public:
    MyString1(const char* str)
    {
        size_t len = strlen(str);
        m_str = new char[len];
        strcpy(m_str, str);
    }

    ~MyString1()
    {
        delete m_str;
    }
};
// 이 코드에서 발생 가능한 메모리 관련 문제를 찾으시오.
// 어떤 상황에서 런타임 오류가 발생할 수 있는지 설명하시오.

class MyString2
{
private:
    char* m_str;

public:
    MyString2(const char* str)
    {
        size_t len = strlen(str) + 1;
        m_str = new char[len];
        strcpy(m_str, str);
    }

    ~MyString2()
    {
        delete[] m_str;
    }
};

int stringTest()
{
    MyString2 a("hello");
    MyString2 b = a;
}
// MyString b = a; 실행 시 어떤 문제가 발생하는가
// 이 문제가 발생하는 근본적인 이유는 무엇인가

class MyString3
{
private:
    char* m_str;

public:
    MyString3(const char* str)
    {
        size_t len = strlen(str) + 1;
        m_str = new char[len];
        strcpy(m_str, str);
    }

    ~MyString3()
    {
        delete[] m_str;
    }

    MyString3& operator=(const MyString3& other)
    {
        delete[] m_str;

        size_t len = strlen(other.m_str) + 1;
        m_str = new char[len];
        strcpy(m_str, other.m_str);

        return *this;
    }
};

//특정 상황에서 undefined behavior가 발생할 수 있다. 어떤 상황인가
class MyString4
{
private:
    char* m_str;

public:
    MyString4(const char* str)
    {
        size_t len = strlen(str) + 1;
        m_str = new char[len];
        strcpy(m_str, str);
    }

    ~MyString4()
    {
        delete[] m_str;
    }

    const char* getStr()
    {
        return m_str;
    }
};

MyString4 makeString()
{
    MyString4 temp("hello");
    return temp;
}
// 이 코드에서 객체 반환 시 어떤 문제가 발생할 가능성이 있는가
// 어떤 C++ 메커니즘과 관련된 문제인가
class MyString5
{
private:
    char* m_str;
    size_t m_size;

public:
    void append(const char* str)
    {
        size_t newLen = m_size + strlen(str);

        char* newStr = new char[newLen + 1];

        strcpy(newStr, m_str);
        strcat(newStr, str);

        delete[] m_str;
        m_str = newStr;
        m_size = newLen;
    }
};
// 성능적으로 어떤 문제가 있는가
// 실제 문자열 클래스 설계에서는 어떻게 해결하는가
*/

/*
int division(int a, int b)
{
    return a/b;
}

bool buy(int64 n, int64 p)
{
    int money = getmoney();
    
    if(money < n*p)
        return false;

    return true;
}
*/

/*
void foo(int* p, int* q)
{
    p = q;
    *p = 3;
}

void Tfoo()
{
    int i =1, j = -1;
    foo(&i, &j);
    printf("%d,%d",i,j);
}

int sum(int n)
{
    return n + sum(n-1);
}

class P
{
public:
    int* m_int;
    std::string m_name;

    P()
    {
        m_int = new int;
        *m_int = 5;
    }

    ~P()
    {
        printf("%s destructor :",m_name);
        printf("%d", *m_int * 2);
        delete m_int;
        m_int = 0;
    }
};

int Pfunc()
{
    P val1;
    P val2 = val1;

    val1.m_name = "val1";
    val2.m_name = "val2";
    
    return 0;
}

void timeC()
{
    int n,j;
    
    for (int i=0;i<n;++i)
    {
        j+=n;
        i = i*2;
    }
}

int main()
{
    Pfunc();
    return 0;
}

*/

/*
class Base
{
public:
    Base()
    {
        std::cout<<"Create Base\n";
    }

    virtual ~Base()
    {
        std::cout<<"Destroy Base\n";
    }

    void funcA()
    {
        std::cout<<"Base funcA\n";
    }

    virtual void funcB()
    {
        std::cout<<"Base funcB\n";
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        std::cout<<"Create Derived\n";
    }

    ~Derived()
    {
        std::cout<<"Destroy Derived\n";
    }

    void funcA()
    {
        std::cout<<"Derived funcA\n";
    }

    virtual void funcB()
    {
        std::cout<<"Derived funcB\n";
    }
};

void main()
{
    Derived A;
    Base* B = static_cast<Base*>(&A);

    A.funcA();
    B->funcA();

    A.funcB();
    B->funcB();
}

// Create Base
// Create Derived
// Derived funcA
// Base funcA
// Derived funcB
// Derived funcB
// Destroy Derived
// Destroy Base
*/

/*
class A
{
public:
    A() {std::cout<<"A constructor\n";}
    A(A& a) {std::cout<<"A copy constructor\n";}
    A(A&& a) {std::cout<<"A move constructor\n";}
    ~A() {std::cout<<"A destructor\n";}
};

A func1(A a)
{
    return a;
}

A func2(A &a)
{
    return a;
}

void main()
{
    A a;
    A b = a;
    A c = func1(b);
    A d = func2(c);
}
*/

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

// N크기인 정방형 배열이 0과 1로 이루어져 있을 때 (x,y)좌표로부터 연속된 0을 1로 바꾸는 함수를 생성하라

using namespace std;
#include <map>
class A
{
private:
    int num;

public:
    A() {};
    ~A() {};
};

class B
{
private:
    int num;

public:
    B() {};
    ~B() {};
};

int main()
{
    A a;
    B b;
    map<A, B> m;
    m.insert(map<A, B>::value_type(a, b));
    
    return 0;
}
int Num[] = {1,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4,3,2,1};

void rtnNum(int* arr, int startidx, int endidx, int targetnum)
{

}

void func()
{
    int num[] = {1,2,3,4,5,6};
    int MAXNUM = sizeof(num)/sizeof(int);

    for (int i = 0; i < MAXNUM - 1; ++i)
    {
        for (int j = 0; j < MAXNUM - 1; ++j)
        {
            if(num[j] > num[j+1])
            {
                int temp = num[j+1];
                num[j+1] = num[j];
                num[j] = temp;
            }
        }
    }

    for(int i=0;i<MAXNUM-1;++i)
        std::cout<<num[i]<<std::endl;
}
int main()
{
    func();
    return 0;
}

class A
{
private:
    int* a;

public:
    A()
    {
        a = new int(0);
    }
    ~A()
    {
        delete a;
    }
};

class B : public A
{
private:
    int *b;

public:
    B()
    {
        b = new int(0);
    }
    ~B()
    {
        delete b;
    }
};

int main()
{
    A* a = new B;
    B* b = new B;

    delete a;
    delete b;

    return 0;
}
=====*/ 

class A
{
    char m_strName;
    int m_iVal;
    double m_dVal;

    virtual void print();
};

class B
{
    int* m_iSize;

    virtual void print();
};

// 32bit class A 크기
// 64bit class B 크기