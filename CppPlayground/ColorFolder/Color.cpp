#include "Color.h"
#include "../Utilities/ConversionsUtility/Conversions.h"

class DynamicStringLibrary;

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
