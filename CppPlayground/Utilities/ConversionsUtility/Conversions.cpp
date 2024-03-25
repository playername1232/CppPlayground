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
    return 0;
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