#include <iostream>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>

std::pair<int,int> ExtractValue(const char* str);
void UsingQueue(int head, int term);
void UsingVector(int head, int term);
void UsingList(int head, int term);

int main(void)
{
    char input[100] = "10 2";
    // std::cin.getline(input,sizeof(input));

    std::pair<int,int> value = ExtractValue(input);

    UsingQueue(value.first, value.second);
    UsingList(value.first, value.second);
    UsingVector(value.first, value.second);

    return 0;
}

std::pair<int,int> ExtractValue(const char* str)
{
#if defined(_MSC_VER)
    char* temp = _strdup(str); // MSVC 전용
#else
    char* temp = strdup(str);  // POSIX (GCC/Clang)
#endif 
    char* token;
    char* context;
    int head, term;

#if defined(_MSC_VER)
    token = strtok_s(temp," ",&context);
#elif defined(__GNUC__)
    token = strtok_r(temp," ",&context);
#endif
    head = atoi(token);

#if defined(_MSC_VER)
    token = strtok_s(NULL," ",&context);
#elif defined(__GNUC__)
    token = strtok_r(NULL," ",&context);
#endif
    term = atoi(token);

    free(temp);

    return {head, term};
    // return std::make_pair(head, term);
}

void UsingQueue(int head, int term)
{
    // queue 생성
    std::queue<int> que;

    for (int i = 1; i <= head; ++i)
        que.push(i);

    // 2개가 남을 때 까지 반복
    while(que.size() > 2)
    {
        // 첫 해당 조각 추출
        que.pop();

        // term만큼 건너뛰기
        for (int j = 0; j < term - 1; ++j)
        {
            que.push(que.front());
            que.pop();
        }
    }

    // 결과출력
    std::vector<int> result;

    while(!que.empty())
    {
        result.push_back(que.front());
        que.pop();
    }

    // 기본 오름차순
    std::sort(result.begin(),result.end());
    // 내림차순
    // std::sort(result.begin(),result.end(),std::greater<int>());
    std::cout<<result[0]<<" "<<result[1]<<"\n";
}

void UsingList(int head, int term)
{
    // list 생성
    std::list<int> lst;

    for(int i=1;i<=head;++i)
        lst.push_back(i);

    // 시작 iterator 지정
    auto it = lst.begin();

    // 2개가 남을 때까지 반복
    while(lst.size() > 2)
    {   
        // 현재 iterator가 가르키는 값 제거
        // iterator는 다음 원소의 주소로 이전
        it = lst.erase(it);

        // iterator가 마지막 요소를 가리키면
        // 처음으로 반환
        if(it == lst.end())
            it = lst.begin();

        // 건너뛰기
        for(int i=0;i<term-1;++i)
        {
            ++it;

            if(it == lst.end())
                it = lst.begin();
        }
    }

    // 결과 출력
    std::vector<int> result;
    // 1. Constructor
    // std::vector<int> result(lst.begin(),lst.end());

    // 2.list 순회
    for (int it : lst)
        result.push_back(it);
    
    // 3. iterator 순회
    // for (auto it = lst.begin(); it != lst.end(); ++it)
    //     result.push_back(*it);

    std::sort(result.begin(),result.end());
    std::cout<<result[0]<<" "<<result[1]<<"\n";
}

void UsingVector(int head, int term)
{
    std::vector<int> vec;
    int idx = 0;
    
    for(int i=1; i<=head; ++i)
        vec.push_back(i);

    while(vec.size() > 2)
    {
        vec.erase(vec.begin()+idx);

        if(!vec.empty())
            idx = (idx + term - 1) % vec.size();
    }

    std::sort(vec.begin(),vec.end());
    std::cout<<vec[0]<<" "<<vec[1]<<"\n";
}