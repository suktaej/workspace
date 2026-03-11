#include <array>
#include <iostream>
#include <string>

constexpr int MAX_SIZE = 8;
std::array<std::array<char,MAX_SIZE>,MAX_SIZE> decompressed;

void Decompress(std::string::iterator& it, int y, int x, int size)
{
    // 한 글자를 검사할 때 마다 반복자를 한 칸 앞으로 이동
    char head = *(it++);
    // base case : 첫 글자가 b 또는 w
    if(head == 'b' || head == 'w')
        for(int dy = 0; dy < size; ++dy)
            for(int dx = 0; dx <size; ++dx)
                decompressed[y + dy][x + dx] = head;
    else
    {
        // 4 부분을 각각 순서대로 압축해제
        int half = size/2;
        Decompress(it, y, x, half);
        Decompress(it, y, x+half, half);
        Decompress(it, y+half, x, half);
        Decompress(it, y+half, x+half, half);
    }
}
using CombineFn = std::string(*)(const std::string&, const std::string&, const std::string&, const std::string&);
std::string VerticalCombine(const std::string &ul, const std::string &ur, const std::string &ll, const std::string &lr)
{
    return ll + lr + ul + ur;
}
std::string HorizontalCombine(const std::string &ul, const std::string &ur, const std::string &ll, const std::string &lr)
{
    return ur + ul + lr + ll;
}

std::string Reverse(std::string::iterator& it, CombineFn combine)
{
    char head = *(it++);

    if(head == 'b'|| head =='w')
        return std::string(1, head);

    std::string upperLeft = Reverse(it, combine);
    std::string upperRight = Reverse(it, combine);
    std::string lowerLeft = Reverse(it, combine);
    std::string lowerRight = Reverse(it, combine);

    return std::string("x") + combine(upperLeft, upperRight, lowerLeft, lowerRight);
}

int main()
{
    std::string s = "xbwxbbwbb";
    auto& it = s.begin();
    Decompress(it, 0, 0, MAX_SIZE);
    
    for(int i=0;i<MAX_SIZE;++i)
    {
        for (int j = 0; j < MAX_SIZE; ++j)
            std::cout<<decompressed[i][j]<<" ";
        std::cout<<"\n";
    }

    it = s.begin();
    std::string r = Reverse(it,VerticalCombine);
    std::cout<<r<<"\n";

    it = r.begin();
    Decompress(it, 0, 0, MAX_SIZE);
    
    for(int i=0;i<MAX_SIZE;++i)
    {
        for (int j = 0; j < MAX_SIZE; ++j)
            std::cout<<decompressed[i][j]<<" ";
        std::cout<<"\n";
    }
    
    return 0;
}