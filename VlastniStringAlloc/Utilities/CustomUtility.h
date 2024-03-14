#pragma once
inline bool str_contains(char* _s, char _c)
{
    for(int i = 0; _s[i] != '\0'; i++)
    {
        if(_s[i] == _c)
            return true;
    }
    
    return  false;
}