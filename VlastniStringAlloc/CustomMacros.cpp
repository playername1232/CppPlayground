#include "CustomMacros.h"


void TestingAllocFunction(void* block)
{
	// https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
	void* xd = VirtualAlloc(block, 10, MEM_COMMIT, 20); // Example
	//VirtualAlloc()
}

void free_heap(void* _block)
{
	if (_block != nullptr)
	{
		// Not functional for now. 0 is a placeholder, there must be size of the allocated heap instead.
		//VirtualFree((LPVOID)_block, 0, MEM_RELEASE);

		free(_block);
		_block = nullptr;
	}
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