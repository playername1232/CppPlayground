#pragma once
#include <malloc.h>

#define InnerFree(ptr) { free(ptr); }

class DynamicStringLibrary
{
public:
	static char* CreateDynamicString(const char* str, size_t len);
    static char* ConcatenateDynamicString(const char* str, const char* concate, const char splitter = NULL);
    static void DeleteDynamicString(const char* str) { free(const_cast<char*>(str)); }
    static void DeleteDynamicString(const char** arrToFree, size_t numOfElements);
    static void ExtractFirstDynamicString(char*& str, const char* extractStr, size_t sizeExtract);
    static char* CopyDynamicString(const char* str);
    static bool CompareDynamicString(const char* str1, const char* str2);
    static char* ReverseDynamicString(const char* str);
};