#pragma once
#include "../MacroUtility/CustomMacros.h"

class Conversions
{
public:
    template <typename T>
    static inline char* DecToBin(T item, size_t size)
    {
        char* res = static_cast<char*>(allocate_heap_clean(size + 1, 1)); // +1 for null terminator

        for (int i = size - 1; i >= 0; i--)
        {
            res[(size - 1) - i] = ((item >> i) & 0x1) + '0'; // +'0' int -> char
        }

        res[size] = '\0';
        return res;
    }

    /// \brief 
    /// \param entry Number for conversion represented in binary 
    /// \param bitSize Bit size of result - Can cause overflow if number actual size overflows return type bitSize
    /// \return Decimal number - long
    static auto BinToDec(char* entry, size_t bitSize) -> long;

    template<typename T>
    static inline auto DecToHex(T item, size_t size)
    {
        
    }
    
    /// \brief 
    /// \param binary Binary string to beautify
    /// \param len Length in bits (4 bytes integer = 32 bits)
    /// \return Beautified binary number (divided by nibbles e.g. 0110 0111)
    static char* BeautyPrintBinary(char* binary, size_t len);
};
