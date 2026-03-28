#include <vector>
#include <array>
#include <algorithm>

struct Point
{
    int x, y;

    bool operator<(const Point& other) const
    {
        if (x != other.x) 
            return x < other.x;

        return y < other.y;
    }
};

std::array<Point,10> points;

long long Cross(const Point& A, const Point& B, const Point& C) 
{
    return (long long)(B.x - A.x) * (C.y - A.y)
         - (long long)(B.y - A.y) * (C.x - A.x);
}

std::vector<Point> AndrewConvexHull()
{
    std::vector<Point> res;
    int size = points.size();
    if(size <= 2)
    {
        // 1. 종료지점에 insert
        // res.insert(res.end(),points.begin(),points.end());
        // 2. 복사
        res.resize(size);
        std::copy(points.begin(),points.end(),res.begin());
        return res;
    }

    // structure 내부 opreator 재정의에 의해 정렬
    std::sort(points.begin(),points.end());

    std::vector<Point> hull;

    // lower hull
    for(const Point& p : points)
    {
        while(hull.size() >= 2)
        {
            Point B = hull.back();
            Point A = hull[hull.size()-2];

            if (Cross(A, B, p) <= 0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(p);
    }

    // upper hull
    size_t lowerSize = hull.size();

    for( int i = size -2 ; i>= 0; --i)
    {
        const Point& p = points[i];

        while(hull.size() > lowerSize)
        {
            Point B = hull.back();
            Point A = hull[hull.size() - 2];

            if (Cross(A, B, p) <= 0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(p);
    }
    // 마지막 점은 시작점과 동일
    hull.pop_back();

    return hull;
}