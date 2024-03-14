#include "Conversions.h"
#include "../CustomUtility.h"

auto Conversions::BinToDec(char* entry, size_t bitSize) -> long
{
    if (bitSize > 64)
    {
        std::cout << "Size of result in bits must not exceed 8 bytes!\n";
        return 0L;
    }
    
    long res = 0L;
    for (size_t i = 0; i < bitSize; i++)
    {
        res += static_cast<long>((entry[i] - '0') * pow(2, (bitSize - 1) - i)); // -'0' char -> int
    }

    return res;
}

// Non-functional 2be finished!
char* Conversions::BeautyPrintBinary(char* binary, size_t len)
{
    if(str_contains(binary, ' '))
    {
        std::cout << "Number binary representation already contains space character!";
        return binary;
    }
    // len / 4 = Number of nibbles = (32bit / 4) = 8 nibbles (8 nibbles = 7 spaces between nibbles + 1 for null terminator)

    const size_t resLen = len + (len / 4);
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