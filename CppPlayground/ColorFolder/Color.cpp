#include "Color.h"
#include "../Utilities/ConversionsUtility/Conversions.h"

class DynamicStringLibrary;

Color::Color()
{
    // Set all to 0
    red = green = blue = 0;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Color::Color(char* hexCode)
{
    // 32 bits are enough to store values for 8bit RGB therefore the 32 bit loss is not important
    uint32_t colorDec = Conversions::HexToDec(hexCode);

    this->red = (colorDec >> 16) & 0xFF;
    this->green = (colorDec >> 8) & 0xFF;
    this->blue = colorDec & 0xFF;
}

char* Color::GetHexCode() const
{
    DynamicStringLibrary res = "#";
    res += Conversions::DecToHex(this->red, 8);
    res += Conversions::DecToHex(this->green, 8);
    res += Conversions::DecToHex(this->blue, 8);
    
    char* result = (char*)allocate_heap_clean(res.GetSize(), 1);
    strcpy_s(result, res.GetSize() + 1, res.GetContent());
    return result;
}


int* Color::GetColors() const
{
    int* arr = (int*)allocate_heap_clean(3, sizeof(int));
    
    arr[0] = this->red;
    arr[1] = this->green;
    arr[2] = this->blue;

    return arr;
}
