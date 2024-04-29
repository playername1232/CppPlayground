#include "Conversions.h"
#include "../CustomUtility.h"
#include "../ArrayUtility/ArrayFunc.h"

char* Conversions::LongToString(long number)
{
    DynamicStringLibrary res = "";

    while(number != 0)
    {
        res += (number % 10) + '0';
        number /= 10;
    }
    
    return reverse_str(res.GetContent());
}

UINT64 Conversions::BinToDec(char* entry, int bitSize)
{
    if(bitSize <= 0)
        return 0;

    UINT64 result = 0;
        
    for(int i = 0; i < bitSize || entry[i] != '\0'; i++)
    {
        result += (entry[i] - '0') & 0x1;
    }

    return result;
}

UINT64 Conversions::HexToDec(char* hex)
{
    UINT64 result = 0l;

    char _cVal[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    int _iVal[16] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x5, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF };
    
    int len = 0;
    // Get length first otherwise there's no way to tell position of the first character
    for(;hex[len] != '\0'; len++) {}

    if(len == 0)
        return 0l;
    
    auto valOfHex = [_cVal, _iVal](char _c) -> int
    {
        for(int i = 0; i < 16; i++)
        {
            if(_cVal[i] == _c)
                return _iVal[i];
        }

        return 0x0;
    };
    
    for(int i = len - 1; i >= 0; i--)
    {
        result += (unsigned long long)valOfHex(hex[i]) << ((len - 1) - i) * 4;
    }
    
    return result;
}

// Non-functional 2be finished!
char* Conversions::BeautyPrintBinary(char* binary, int len)
{
    if(str_contains(binary, ' '))
    {
        std::cout << "Number binary representation already contains space character!";
        return binary;
    }
    // len / 4 = Number of nibbles = (32bit / 4) = 8 nibbles (8 nibbles = 7 spaces between nibbles + 1 for null terminator)

    const int resLen = len + (len / 4);
    char* res = static_cast<char*>(allocate_heap_clean(resLen, 1));
    
    for (int i = len, idx = resLen - 1; i >= 0; i--, idx--)
    {
        if((i + 1) % 4 == 0)
        {
            res[idx] = ' ';
            idx -= 1;
        }

        res[idx] = binary[i];
    }

    res[resLen - 1] = '\0';

    return res;
}