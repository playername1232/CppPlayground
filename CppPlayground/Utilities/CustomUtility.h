#pragma once
#include <iosfwd>
#include <sstream>
#include <stdexcept>

inline bool str_contains(char* _s, char _c)
{
    for(int i = 0; _s[i] != '\0'; i++)
    {
        if(_s[i] == _c)
            return true;
    }
    
    return  false;
}

/// <summary>
/// Finds character in string
/// </summary>
/// <param name="content">String entry</param>
/// <param name="_char">Character to find</param>
/// <returns>Index of first character occurence OR -1 if character doesn't exist in given string</returns>
inline int GetIndexOf(char* _s, char _c)
{
    for (int i = 0; _s[i] != '\0'; i++)
    {
        if (_s[i] == _c)
            return i;
    }
    return -1;
}

/// <summary>
/// Replaces character in 
/// </summary>
/// <param name="content">String Entry</param>
/// <param name="_c">Original character</param>
/// <param name="_r">Replacement character</param>
/// <returns></returns>
inline int CharReplace(char* content, char _c, char _r)
{
    int ret = -1;
    for (int i = 0; content[i] != '\0'; i++)
    {
        if (content[i] == _c)
        {
            ret = 0;
            content[i] = _r;
        }
    }
    return ret;
}

/// Copies string from source to destination
/// @param dest Destination
/// @param src Source
void strcpy_c(char*& dest, const char* src);

/// ASCII character To upper convertor
/// @return Upper case letter
char asciiToUpper(char _c);

/// ASCII character to lower convertor
/// @return Lower case letter
char asciiToLower(char _c);

int abs_val(int val);
int negative_val(int val);