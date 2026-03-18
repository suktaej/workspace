#include <iostream>
#include <iomanip>
#include <cstdint>

int main()
{
    uint32_t RED, GREEN, BLUE;
    
    RED = 255;
    GREEN = 128;
    BLUE = 64;

    uint32_t HEX = (RED << 16) | (GREEN << 8) | BLUE;

    std::cout<<'#'<<
    std::setfill('0')<<
    std::setw(6)<<
    std::uppercase<<
    std::hex<<
    HEX<< '\n';

    std::cout << ((HEX >> 16) & 0xFF) << '\n';
    std::cout << ((HEX >> 8) & 0xFF) << '\n';
    std::cout << (HEX & 0xFF) << '\n';
    // HEX |= RED;
    // HEX <<= 8;
    // HEX |= GREEN;
    // HEX <<= 8;
    // HEX |= BLUE;

    // std::cout<<std::hex<<(int)RED<<'\n';
    // std::cout<<std::hex<<(int)BLUE<<'\n';
    // std::cout<<std::hex<<(int)GREEN<<'\n';

    return 0;
}