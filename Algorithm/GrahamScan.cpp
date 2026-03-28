#include <array>
#include <vector>
#include <algorithm>

struct Point
{
    int x, y;
};

std::array<Point,10> points;

long long Cross(const Point& A,const Point& B,const Point& C)
{
    return (long long)(B.x - A.x) * (C.y - A.y)
         - (long long)(B.y - A.y) * (C.x - A.x);
}

int main(void)
{
    int size = points.size();
    // pivot 선택
    int pivotIdx = 0;
    
    for(int i =1;i<size;++i)
    {
        if (points[i].x < points[pivotIdx].x ||
            (points[i].x == points[pivotIdx].x &&
             points[i].y < points[pivotIdx].y))
             pivotIdx = i;
    }

    std::swap(points[0],points[pivotIdx]);
    Point pivot = points[0];
    // 각도 순 정렬
    std::sort(points.begin() + 1, points.end(),
              [&](const Point &a, const Point &b)
              {
                  long long c = Cross(pivot, a, b);

                  // 시계방향 우선(각도가 큰 쪽)
                  if (c != 0)
                      return c < 0;

                  // 같은 방향이면 pivot에서 더 먼 점 우선
                  long long da = (long long)(a.x - pivot.x) * (a.x - pivot.x) + (long long)(a.y - pivot.y) * (a.y - pivot.y);
                  long long db = (long long)(b.x - pivot.x) * (b.x - pivot.x) + (long long)(b.y - pivot.y) * (b.y - pivot.y);
                  return da > db;
              });

    // 다각형 생성
    std::vector<Point> hull;

    if (size <= 2)
    {
        hull.assign(points.begin(), points.end());
        return 0;
    }
    else
    {
        hull.push_back(points[0]);
        hull.push_back(points[1]);

        for (int i = 2; i < size; ++i)
        {
            while (hull.size() >= 2)
            {
                Point B = hull.back();
                Point A = hull[hull.size() - 2];
                // CW순 정렬이므로 CCW or collinear이라면 제거
                if (Cross(A, B, points[i]) >= 0)
                    hull.pop_back();
                else
                    break;
            }
            hull.push_back(points[i]);
        }
    }

    return 0;
}