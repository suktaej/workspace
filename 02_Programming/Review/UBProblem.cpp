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



int main()
{
    stringTest();
    return 0;
}
