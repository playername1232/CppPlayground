#pragma once

class Color
{
private:
    int red;
    int green;
    int blue;
public:
    Color()
    {
        // Set all to 0
        red = green = blue = 0;
    }

    Color(int red, int green, int blue)
    {
        this->red = (red >= 0 && red <= 255) ? red : 0;
        this->green = (green >= 0 && green <= 255) ? green : 0;
        this->blue = (blue >= 0 && blue <= 255) ? blue : 0;
    }

    // 2b done
    Color(char* hexCode)
    {
        
    }
    
    char* GetHexCode();
};
