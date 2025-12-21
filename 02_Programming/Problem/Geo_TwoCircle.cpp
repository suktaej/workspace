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
    float dx = c1.x - c2.x;
    float dy = c1.y - c2.y;
    float dist = std::sqrt(dx * dx + dy * dy);
    float rDist = c1.r + c2.r;

    if(rDist > dist)
    {

    }
    else if(rDist < dist)
        return ETYPE::Outer;
    else
        return ETYPE::Outer_border;
}