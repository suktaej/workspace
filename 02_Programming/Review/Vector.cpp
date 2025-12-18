#include <cmath>

struct Vector2D
{
    float x;
    float y;
};

inline Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
    return {a.x + b.x, a.y + b.y};
}

inline Vector2D operator-(const Vector2D& a, const Vector2D& b)
{
    return {a.x - b.x, a.y - b.y};
}

inline Vector2D operator*(float f, const Vector2D& vec)
{
    return {f * vec.x, f * vec.y};
}

inline float dot(const Vector2D& a, const Vector2D& b)
{
    return a.x * b.x + a.y * b.y;
}

inline float cross(const Vector2D& a, const Vector2D& b)
{
    return a.x * b.y - a.y * b.x;
}

inline float dist(const Vector2D& a, const Vector2D& b)
{
    Vector2D temp = a - b;
    return std::sqrt(temp.x * temp.x + temp.y * temp.y);
}

inline Vector2D projection(const Vector2D& a, const Vector2D& b)
{
    return (dot(a, b) / dot(b, b)) * b;
}

float ClosestDistance(const Vector2D& a, const Vector2D& b, const Vector2D& c)
{
    Vector2D ab = b-a;
    Vector2D ac = c-a;
    float t = dot(ac, ab) / dot(ab, ab);

    if (t < 0.f)
        return dist(a,c);
    if (t > 1.f)
        return dist(b,c);

    // dot
    Vector2D proj = t * ab;
    Vector2D h = a + proj;
    Vector2D normal = c - h;

    return dist(c,h);
    
    // cross
    float len = std::sqrt(dot(ab, ab));
    float d = std::abs(cross(ac,ab)) / len;

    return d;
}