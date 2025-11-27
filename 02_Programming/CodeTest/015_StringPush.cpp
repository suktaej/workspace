#include <string>
#include <vector>

int StringPush(std::string A, std::string B) 
{
    int answer = -1;
    int count = 0;
    
    for(int i = 0; i< A.size(); ++i)
    {
        // Base case
        if(A == B)
        {
            // 1. 분기(좌우 회전이 가능할 경우 최소확인)
            // if(A.size()-count < count)  
            //     count = A.size()-count;

            // 2. std::min
            // std::min(count, A.size()-count);

            answer = count;
            break;
        }

        // 1. string함수 사용
        A.insert(A.begin(),A.back());
        A.pop_back();

        // 2. rotate 함수 사용
        // (first, n_first, last) : 회전할 범위 시작, 새롭게 범위의 시작이 될 원소, 회전할 범위의 끝
        // std::rotate(A.rbegin(), A.rbegin() + 1, A.rend());

        ++count;
    }

    return answer;
}

int Optimize(std::string A, std::string B)
{
    B += B;
    return B.find(A);
}