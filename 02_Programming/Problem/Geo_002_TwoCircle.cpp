#include <cmath>

struct FCircle
{
    int x,y,r;
};

enum class ETYPE
{
    Inner,
    Inner_border,
    Cross,
    Outer_border,
    Outer
};

ETYPE CircleCollision(const FCircle& c1, const FCircle& c2)
{
    long dx = c1.x - c2.x;
    long dy = c1.y - c2.y;
    // long dist = std::sqrt(dx * dx + dy * dy);
    // Sqrt연산 제외
    long dist2 = dx * dx + dy * dy;
    
    long rSum = c1.r + c2.r;
    long rSum2 = rSum * rSum;

    if(dist2 > rSum2)
        return ETYPE::Outer;
    else if(dist2 == rSum2)
        return ETYPE::Outer_border;
    else
    {
        long rDiff = std::abs(c1.r - c2.r);
        long rDiff2 = rDiff * rDiff;

        if (dist2 > rDiff2)
            return ETYPE::Cross;
        else if(dist2 == rDiff2)
            return ETYPE::Inner_border;
        else
            return ETYPE::Inner;
    }
}