#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>

static constexpr int vecSize = 10000000;

int UsingMapForMode(std::vector<int> array) {

    std::map<int,int> freq;

    // map의 key가 존재하면 value 1 증가
    // key가 존재하지 않는다면 key를 자동으로 생성
    // value는 기본 생성자로 초기화
    // int의 기본 생성자는 0
    // 0이 생성된 다음 후위연산자(++)을 통해 1로 변경
    for(int num : array)
        freq[num]++;

    int maxNum = 0;
    int maxCount = 0;
    bool eq = false;

    for(auto& [num, count] : freq)
    {
        if(count > maxCount)
        {
            maxCount = count;
            maxNum = num;
            eq = false;
        }
        else if(count == maxCount)
            eq = true;
    } 
    
    return eq ? -1 : maxNum;
}


int UsingMapFuncForMode(std::vector<int> array) {

    std::map<int,int> freq;

    for(const int &num : array)
    {
        // map의 find는 iterator
        auto it = freq.find(num);

        if(it != freq.end())
            it->second++;
        else
            freq.insert({num,1});
    }

    int maxCount = 0;
    int maxNum = 0;
    bool eq = false;

    for(const auto &it : freq)
    {
        if(maxCount < it.second)
        {
            maxCount = it.second;
            maxNum = it.first;
            eq = true;
        }
        else if(maxCount == it.second)
            eq = false;
    }

    return eq ? -1 : maxNum;
}

int UsingVectorForMode(std::vector<int> array) {

    std::vector<int> freq(vecSize+1,0);

    for(const int& num : array)
        freq[num]++;

    int maxCount = 0;
    int maxNum = 0;
    bool eq = false;

    for(int i=0;i<=vecSize;++i)
    {
        if(maxCount < freq[i])
        {
            maxCount = freq[i];
            maxNum = i;
            eq = false;
        }
        else if(maxCount == freq[i])
            eq = true;
    }

    return eq ? -1 : maxNum;
}

int main(void)
{
    std::vector<int> vec;

    std::random_device rd;  // seed value
    std::mt19937 gen(rd()); // Mersenne Twister
    std::uniform_int_distribution<> dis(1,vecSize-1);    //1~vectorSize

    for(int i=0;i<vecSize;++i)
        vec.push_back(dis(gen));

    auto mapCountStart = std::chrono::high_resolution_clock::now();
    UsingMapForMode(vec);
    auto mapCountEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> mapTime = mapCountEnd - mapCountStart;

    auto vecCountStart = std::chrono::high_resolution_clock::now();
    UsingVectorForMode(vec);
    auto vecCountEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vecTime = vecCountEnd - vecCountStart;

    std::cout << "Vector time: " << vecTime.count() << " ms\n";
    std::cout << "Map time: " << mapTime.count() << " ms\n";

    return 0; 
}