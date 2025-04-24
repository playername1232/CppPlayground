#include "CustomUtility.h"
#include "MacroUtility/CustomMacros.h"


void strcpy_c(char*& dest, const char* src)
{
    if (src == nullptr)
        return;

    size_t strSize = strlen(src) + 1; // +1 na '\0'

    if (dest != nullptr)
    {
        char* buffer = static_cast<char*>(reallocate_heap_block(dest, strSize, 1));
        check(buffer);
        dest = buffer;
    }
    else
    {
        dest = static_cast<char*>(allocate_heap_clean(strSize, 1));
    }

    memcpy(dest, src, strSize);
}


char asciiToUpper(char _c)
{
    if(_c >= 'a' && 'z' >= _c)
        return (char)(_c - 32);

    return _c;
}

char asciiToLower(char _c)
{
    if(_c >= 'A' && 'Z' >= _c)
        return (char)(_c + 32);

    return _c;
}

int abs_val(int val)
{
    if(val >= 0)
        return val;
    if(val == INT_MIN)
        return INT_MAX;
    
    val = ~val;
    val += 1;
    return val;
}

int negative_val(int val)
{
    if(val <= 0)
        return val;
    if(val == INT_MAX)
        return INT_MIN;

    val = ~val;
    val += 1;
    return val;
}