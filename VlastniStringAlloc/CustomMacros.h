#pragma once
#ifndef CUSTOMMACROS

#include <malloc.h>
#include <iostream>
#include <Windows.h>
#include <cassert>

#ifndef DYNAMICSTRING
#include "DynamicStringLibrary.h"
#endif

#endif

#define check(ptr) \
assert(ptr != nullptr)

#define check_size(len) \
assert(len > 0);

/// <summary>
/// Converts const to variables
/// </summary>
/// <typeparam name="T">Data type</typeparam>
/// <param name="ptr">Const entry</param>
/// <returns>Returns value of constant as variable</returns>
template<typename T>
auto remove_constant(const T* ptr)
{
	if (std::is_same<T, char*>::value ||
		std::is_same<T, std::string>::value)
	{
		char* res = _strdup(static_cast<char*>(ptr));

		return res;
	}
	if (std::is_same<T, DynamicStringLibrary>::value)
	{
		DynamicStringLibrary res = ((DynamicStringLibrary*)ptr)->GetContent();

		return res;
	}

	T* value = &*ptr;
}

void TestingAllocFunction(void* block);
void free_heap(void* _block);
void* allocate_heap(size_t _count, size_t _size);
void* allocate_heap_clean(size_t _count, size_t _size);
void* reallocate_heap_block(void* _block, size_t _newCount, size_t _newSize);