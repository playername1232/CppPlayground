#include "CustomUtility.h"
#include "MacroUtility/CustomMacros.h"


void strcpy_c(char*& dest, const char* src)
{    
    size_t strSize = strlen(src);

    if(dest != nullptr)
    {
        char* buffer = (char*)reallocate_heap_block(dest, strSize, 1);

        check(buffer);
        dest = buffer;
    }
    else
        dest = (char*)allocate_heap_clean(strSize, 1);
    
    for(size_t i = 0; i < strSize; i++)
    {
        dest[i] = src[i];
    }
    if(dest[strSize - 1] != '\0')
    {
        char* buffer = (char*)reallocate_heap_block(dest, strSize + 1, 1);
        check(buffer);
        buffer[strSize] = '\0';
        
        dest = buffer;
    }
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