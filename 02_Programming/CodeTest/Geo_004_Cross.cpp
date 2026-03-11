#include <utility>

struct Point
{
   int x, y;
};

struct Line
{
    Point p1, p2;
};

long Cross(Line l1, Line l2)
{
    long l1x = l1.p1.x - l1.p2.x;
    long l1y = l1.p1.y - l1.p2.y;
    long l2x = l2.p1.x - l2.p2.x;
    long l2y = l2.p1.y - l2.p2.y;

    return l1x*l2y - l1y*l2x;
}

long Cross(const Point& a,const Point& b,const Point& pivot)
{
    long v1x = pivot.x - a.x;
    long v1y = pivot.y - a.y;
    long v2x = pivot.x - b.x;
    long v2y = pivot.y - b.y;

    return v1x*v2y - v1y*v2x;
}

int CCW(const Point& a,const Point& b,const Point& pivot)
{
    long v = Cross(a,b,pivot);

    if(v > 0) 
        return 1;
    if(v < 0)
        return -1;
    else
        return 0;
}

bool Overlap(int a, int b, int c, int d)
{
    if (a > b)
        std::swap(a, b);

    if (c > d)
        std::swap(c, d);

    return std::max(a, c) <= std::min(b, d);
}

bool IsOverlapping(const Line& l1, const Line& l2)
{
    return Overlap(l1.p1.x, l1.p2.x, l2.p1.x, l2.p2.x) &&
           Overlap(l1.p1.y, l1.p2.y, l2.p1.y, l2.p2.y);
}

bool Intersect(const Line& l1, const Line& l2)
{
    int ab1 = CCW(l1.p2, l2.p1, l1.p1);
    int ab2 = CCW(l1.p2, l2.p2, l1.p1);
    int cd1 = CCW(l2.p2, l1.p1, l2.p1);
    int cd2 = CCW(l2.p2, l1.p2, l2.p1);

    if (ab1 * ab2 == 0 && cd1 * cd2 == 0)
        return IsOverlapping(l1,l2);

    return ab1 * ab2 < 0 && cd1 * cd2 < 0;
}

bool IntersectionPoint(const Line& l1, const Line& l2, double& x, double& y)
{
    double A1 = l1.p2.y - l1.p1.y;
    double B1 = l1.p1.x - l1.p2.x;
    double C1 = A1 * l1.p1.x + B1 * l1.p1.y;

    double A2 = l2.p2.y - l2.p1.y;
    double B2 = l2.p1.x - l2.p2.x;
    double C2 = A2 * l2.p1.x + B2 * l2.p1.y;

    double det = A1 * B2 - A2 * B1;
    if (det == 0) 
        return false; // 평행 또는 동일 직선

    x = (B2 * C1 - B1 * C2) / det;
    y = (A1 * C2 - A2 * C1) / det;
    return true;
}