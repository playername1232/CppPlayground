#include "CustomMacros.h"
#include <iostream>
#include <sstream>

void* TestingAllocFunction(void* block)
{
	// https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
	return VirtualAlloc(NULL, 10, MEM_COMMIT, 20); // Example
	//VirtualAlloc()
}

void free_heap(void* _block)
{
	if (_block != nullptr)
		free(_block);
}

void* allocate_heap(size_t _count, size_t _size)
{
	if (_count == 0 || _size == 0)
		return nullptr;

	try
	{
		void* _newBlock = malloc(_count * _size);

		if(_newBlock != nullptr)
		{ 
			return _newBlock;
		}
		
		std::ostringstream oss{};
		oss << __FUNCTION__ << ": Allocating new memory block has failed!";

		throw std::runtime_error(oss.str());
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return nullptr;
	}
}

void* allocate_heap_clean(size_t _count, size_t _size)
{
	if (_count == 0 || _size == 0)
		return nullptr;

	try
	{
		void* _newBlock = calloc(_count, _size);

		if (_newBlock != nullptr)
		{
			return _newBlock;
		}

		std::ostringstream oss{};
		oss << __FUNCTION__ << ": Allocating new memory block has failed!";

		throw std::runtime_error(oss.str());
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return nullptr;
	}
}

void* reallocate_heap_block(void* _block, size_t _newCount, size_t _newSize)
{
	check_size(_newCount);
	check_size(_newSize);

	try
	{
		void* _newBlock = realloc(_block, _newCount * _newSize);

		if (_newBlock != nullptr)
		{
			return _newBlock;
		}

		std::ostringstream oss{};
		oss << __FUNCTION__ << ": Reallocating memory block has failed!";

		throw std::runtime_error(oss.str());
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return nullptr;
	}
}