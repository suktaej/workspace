#include <cmath>
#include <algorithm>

float Clockhand(int hour, int minute, int hourLen, int minuteLen)
{
    constexpr float MINUTE_DEG_PER_MIN = 6.f;
    constexpr float HOUR_DEG_PER_MIN   = 0.5f;
    constexpr float DEG_TO_RAD = 3.141592f / 180.f;

    hour %= 12;

    float minAngle = minute * MINUTE_DEG_PER_MIN;
    float hourAngle = hour * 30.f + minute * HOUR_DEG_PER_MIN;

    float diff = std::abs(minAngle - hourAngle);
    diff = std::min(diff, 360.f - diff);
    float rad = diff * DEG_TO_RAD;

    return std::sqrt(hourLen * hourLen + minuteLen * minuteLen - 2 * hourLen * minuteLen * std::cos(rad));
}