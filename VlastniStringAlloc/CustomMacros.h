// TODO: Check for multiple declaration of allocate_heap, allocate_heap_clean and reallocate_heap_block

//1 > Program.obj : error LNK2005 : "void * __cdecl allocate_heap(unsigned __int64,unsigned __int64)" (? allocate_heap@@YAPEAX_K0@Z) already defined in DynamicStringLibrary.obj
//1 > Program.obj : error LNK2005 : "void * __cdecl allocate_heap_clean(unsigned __int64,unsigned __int64)" (? allocate_heap_clean@@YAPEAX_K0@Z) already defined in DynamicStringLibrary.obj
//1 > Program.obj : error LNK2005 : "void * __cdecl reallocate_heap_block(void *,unsigned __int64,unsigned __int64)" (? reallocate_heap_block@@YAPEAXPEAX_K1@Z) already defined in DynamicStringLibrary.obj

#pragma once
#ifndef CUSTOMMACRO
#define CUSTOMMACRO

#include <malloc.h>
#include <iostream>
#include <Windows.h>

#endif // CUSTOMMACRO

class MemoryHeader
{
private:
	size_t byteSize;
	void* heapBlockHead;
};

template <typename T>
void InnerFree(T* ptr)
{
	if (ptr != nullptr)
	{
		free(ptr);
		if (!std::is_const<T>::value)
			ptr = nullptr;
	}
}

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
		char* res = _strdup(ptr);
	
		return res;
	}
	if (std::is_same<T, DynamicStringLibrary>::value)
	{
		DynamicStringLibrary res = ((DynamicStringLibrary*)ptr)->GetContent();

		return res;
	}

	return *ptr;
}

void TestingAllocFunction()
{
	//VirtualFree()
	//VirtualAlloc()
}

void* allocate_heap(size_t _count, size_t _size)
{
	if (_count == 0 || _size == 0)
		return nullptr;

	void* _newBlock = malloc(_count * _size);

	if (_newBlock == nullptr)
		throw std::exception("An excption occured in CustomMacros::allocate_memory_clean(size_t, size_t): Unable to allocate new block on heap");

	return _newBlock;
}

void* allocate_heap_clean(size_t _count, size_t _size)
{
	if (_count == 0 || _size == 0)
		return nullptr;

	void* _newBlock = calloc(_count, _size);
	if (_newBlock == nullptr)
		throw std::exception("An excption occured in CustomMacros::allocate_memory_clean(size_t, size_t): Unable to allocate new block on heap");

	return _newBlock;
}

void* reallocate_heap_block(void* _block, size_t _newCount, size_t _newSize)
{
	if (_newCount == 0 || _newSize == 0)
	{
		if (_block == nullptr)
			throw std::exception("An excption occured in CustomMacros::reallocate_heap_block(void*, size_t, size_t): Invalid count or size of new block!");
	}

	void* _newBlock = realloc(_block, _newCount * _newSize);
	if (_newBlock == nullptr)
		throw std::exception("An excption occured in CustomMacros::allocate_memory_clean(size_t, size_t): Unable to allocate new block on heap");

	return _newBlock;
}