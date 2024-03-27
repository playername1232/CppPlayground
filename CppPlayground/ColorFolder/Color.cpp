#include "Color.h"
#include "../Utilities/ConversionsUtility/Conversions.h"

class DynamicStringLibrary;

Color::Color()
{
    // Set all to 0
    red = green = blue = 0;
}

Color::Color(int red, int green, int blue)
{
    this->red = (red >= 0 && red <= 255) ? red : 0;
    this->green = (green >= 0 && green <= 255) ? green : 0;
    this->blue = (blue >= 0 && blue <= 255) ? blue : 0;
}

Color::Color(char* hexCode)
{
    
}

char* Color::GetHexCode()
{
    DynamicStringLibrary res = "#";
    res += Conversions::DecToHex(this->red, 8);
    res += Conversions::DecToHex(this->green, 8);
    res += Conversions::DecToHex(this->blue, 8);
    
    char* result = (char*)allocate_heap_clean(res.GetSize(), 1);
    strcpy_s(result, res.GetSize() + 1, res.GetContent());
    return result;
}
