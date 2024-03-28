#pragma once
#include <cstdint>

class Color
{
private:
    // 8 bit
    uint8_t red;
    // 8 bit
    uint8_t green;
    // 8 bit
    uint8_t blue;
public:
    Color();
    Color(uint8_t red, uint8_t green, uint8_t blue);
    // 2b done
    Color(char* hexCode);
    
    char* GetHexCode() const;
    
    // Returns color values in int array { red, green, blue }
    int* GetColors() const;
};
