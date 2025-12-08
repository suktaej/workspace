#include <vector>
#include <unordered_set>
#include <algorithm>

int MakeTriangleUsingVector(std::vector<int> sides)
{
    int most = std::max(sides[0], sides[1]);
    int less = std::min(sides[0], sides[1]);

    // 1. vector 저장
    std::vector<int> vecLength;
    for (int i = most - less + 1; i <= most; ++i)
        vecLength.push_back(i);

    for (int i = most + 1; most + less > i; ++i)
        vecLength.push_back(i);

    int count = 0;

    for(int i=0;i<vecLength.size();++i)
    {
        ++count;

        for (int j = i + 1; j < vecLength.size(); ++j)
        {
            if (vecLength[i] == vecLength[j])
            {
                --count;
                break;
            }
        }
    }
    
    return count;
}

int MakeTriangleUsingSet(std::vector<int> sides)
{
    int most = std::max(sides[0], sides[1]);
    int less = std::min(sides[0], sides[1]);
    
    // 2. unordered_set (중복무시)
    std::unordered_set<int> setLength;

    for (int i = most - less + 1; i <= most; ++i)
        setLength.insert(i);

    for (int i = most + 1; most + less > i; ++i)
        setLength.insert(i);

    return setLength.size();
}

int MakeTriangleUsingBool(std::vector<int> sides)
{
    int most = std::max(sides[0], sides[1]);
    int less = std::min(sides[0], sides[1]);

    // 3. bool vector를 통한 중복체크
    std::vector<bool> dupCheck(most * 10, false);
    std::vector<int> vecLength;
    
    for (int i = most - less + 1; i <= most; ++i)
    {
        if (false == dupCheck[i])
        {
            dupCheck[i] = true;
            vecLength.push_back(i);
        }
    }

    for (int i = most + 1; most + less > i; ++i)
    {
        if (false == dupCheck[i])
        {
            dupCheck[i] = true;
            vecLength.push_back(i);
        }
    }

    return vecLength.size();
}

int MakeTriangleUsingUnique(std::vector<int> sides)
{
    int most = std::max(sides[0], sides[1]);
    int less = std::min(sides[0], sides[1]);

    std::vector<int> length;
    for (int i = most - less + 1; i <= most; ++i)
        length.push_back(i);

    for (int i = most + 1; most + less > i; ++i)
        length.push_back(i);

    std::sort(length.begin(), length.end());
    
    // 4. std::unique
    // 연속된 중복들을 탐지하고 맨 뒤로 이동시킴(정렬필요)
    // 예) 3 3 4 4 5 5 가 입력될 경우 3 4 5 | 3 4 5
    // 반환되는 위치는 |
    length.erase(std::unique(length.begin(), length.end()), length.end());

    return length.size();
}