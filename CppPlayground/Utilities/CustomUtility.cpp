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
    
    for(int i = 0; i < strSize; i++)
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
        return _c - 32;

    return 0x0;
}

char asciiToLower(char _c)
{
    if(_c >= 'A' && 'Z' >= _c)
        return _c + 32;

    return 0x0;
}
