#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

std::pair<int, int> MakeVector(std::vector<int> lhs, std::vector<int> rhs);
bool ParallelCheck(std::pair<int, int> lhs, std::pair<int, int> rhs);

int main()
{
    std::vector<std::vector<int>> dots = {{1, 4}, {9, 2}, {3, 8}, {11, 6}};

    if (ParallelCheck(MakeVector(dots[0], dots[1]), MakeVector(dots[2], dots[3])))
        return 1;
    if (ParallelCheck(MakeVector(dots[0], dots[2]), MakeVector(dots[1], dots[3])))
        return 1;
    if (ParallelCheck(MakeVector(dots[0], dots[3]), MakeVector(dots[1], dots[2])))
        return 1;

    return 0;
}

bool ParallelCheck(std::pair<int, int> lhs, std::pair<int, int> rhs)
{
    int crossProudct = lhs.first * rhs.second - lhs.second * rhs.first;
    return crossProudct == 0;
}

std::pair<int, int> MakeVector(std::vector<int> lhs, std::vector<int> rhs)
{
    std::pair<int, int> newVector;
    newVector.first = rhs[0] - lhs[0];
    newVector.second = rhs[1] - lhs[1];

    return newVector;
}

// 모든 라인을 생성하고 이를 비교
// 비교 전, 기울기 값으로 정렬하고 다음 값과 비교 

struct Line {
    long long dy, dx;
    int p1, p2;
};

int CompareAllLine(std::vector<std::vector<int>> dots)
{
    int dotSize = dots.size();
    std::vector<Line> lines;

    // 1. 모든 선분 생성 (O(N^2))
    for (int i = 0; i < dotSize; i++)
    {
        for (int j = i + 1; j < dotSize; j++)
        {
            long long dy = dots[j][1] - dots[i][1];
            long long dx = dots[j][0] - dots[i][0];

            // 부호 정규화 및 기약분수 처리 
            if (dx < 0)
            {
                dx = -dx;
                dy = -dy;
            }
            else if (dx == 0 && dy < 0) { dy = -dy; }
            long long g = std::gcd(abs(dx), abs(dy));

            lines.push_back({dy / g, dx / g, i, j});
        }
    }

    // 2. 정렬 (O(N^2 log N))
    // dx, dy가 이미 정규화되어 있으므로 그냥 pair 비교하듯 정렬하면 됨
    // 정렬하지 않을 경우 아래에서 다시 2중 반복문을 사용해야 하며 이는 O(N^2)만큼의 시간이 추가로 필요
    std::sort(lines.begin(), lines.end(),
              [](const Line& a, const Line& b)
              {
                  if (a.dx != b.dx) 
                      return a.dx < b.dx;
                  
                  return a.dy < b.dy;
              });

    // 3. 인접한 값 비교 (O(N^2))
    for (size_t i = 0; i < lines.size() - 1; i++)
    {
        // 기울기가 같고 (dx, dy가 같고)
        if (lines[i].dx == lines[i + 1].dx && lines[i].dy == lines[i + 1].dy)
        {
            // 점을 공유하지 않는지 확인
            if (lines[i].p1 != lines[i + 1].p1 && lines[i].p1 != lines[i + 1].p2 &&
                lines[i].p2 != lines[i + 1].p1 && lines[i].p2 != lines[i + 1].p2)
                return 1;
        }
    }

    return 0;
}
