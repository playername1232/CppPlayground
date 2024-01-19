#pragma once
#include <malloc.h>

#define InnerFree(ptr) { free(ptr); }

class DynamicStringLibrary
{
public:

	static void DeleteDynamicString(const char* str) { free(const_cast<char*>(str)); }
	static void DeleteDynamicString(const char** arrToFree, size_t numOfElements);
	static char* ConcatenateDynamicString(const char* str, const char* concate, const char splitter = NULL);
	static char* CreateDynamicString(const char* str, size_t len);
};