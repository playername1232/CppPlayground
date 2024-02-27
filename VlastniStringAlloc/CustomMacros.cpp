#include "CustomMacros.h"

void TestingAllocFunction(void* block)
{
	// https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
	void* xd = VirtualAlloc(block, 10, MEM_COMMIT, 20); // Example
	//VirtualAlloc()
}

void free_heap(void* _block)
{
	check(_block);

	free(_block);
	_block = nullptr;
}

void* allocate_heap(size_t _count, size_t _size)
{
	if (_count == 0 || _size == 0)
		return nullptr;

	void* _newBlock = malloc(_count * _size);
	check(_newBlock);

	return _newBlock;
}

void* allocate_heap_clean(size_t _count, size_t _size)
{
	if (_count == 0 || _size == 0)
		return nullptr;

	void* _newBlock = calloc(_count, _size);
	check(_newBlock);

	return _newBlock;
}

void* reallocate_heap_block(void* _block, size_t _newCount, size_t _newSize)
{
	check_len(_newCount);
	check_len(_newSize);

	void* _newBlock = realloc(_block, _newCount * _newSize);
	check(_newBlock);

	return _newBlock;
}