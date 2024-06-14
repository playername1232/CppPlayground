#pragma once
#include "../MacroUtility/CustomMacros.h"

class Conversions
{
public:
    static char* LongToString(long number);
    
    template <typename T>
    static inline char* DecToBin(T item, int size)
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
    static UINT64 BinToDec(char* entry, const int bitSize);

    /// \brief 
    /// \tparam T item data type
    /// \param item item to convert
    /// \param bitSize amount of bits to convert into hex (if not divisible by 4, the missing amount is added)
    /// \return Returns item represented in hex
    template<typename T>
    static char* DecToHex(T item, int bitSize)
    {
        assert(bitSize > 0 && bitSize <= 64);
        constexpr char mask[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
        DynamicStringLibrary res = "";

        // round it to 4 bits
        bitSize += bitSize % 4;
        
        for(int i = bitSize; i >= 0; i -= 4)
        {
            // Shift nibbles i times
            char pomCharmask = mask[(item >> i) & 0xF];
            res += mask[(item >> i) & 0xF];
        }
        
        char* result = (char*)allocate_heap_clean(res.GetSize(), 1);
        strcpy_s(result, res.GetSize() + 1, res.GetContent());
        return result;
    }

    static UINT64 HexToDec(char* hex);
    
    /// \brief 
    /// \param binary Binary string to beautify
    /// \param len Length in bits (4 bytes integer = 32 bits)
    /// \return Beautified binary number (divided by nibbles e.g. 0110 0111)
    static char* BeautyPrintBinary(char* binary, int len);
};
