#pragma once

class Color
{
private:
    int red;
    int green;
    int blue;
public:
    Color();
    Color(int red, int green, int blue);
    // 2b done
    Color(char* hexCode);
    
    char* GetHexCode();
};