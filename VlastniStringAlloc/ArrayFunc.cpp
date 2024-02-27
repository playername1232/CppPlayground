#include "ArrayFunc.h"

void reverse_str(char* str)
{
	if (str[0] == '\0')
		return;

	size_t allocSize = 500;
	size_t idx = 0;

	char* copy = (char*)allocate_heap_clean(allocSize, 1);

	for (; str[idx] != '\0'; idx++)
	{
		if (idx == allocSize - 1)
		{
			copy = (char*)reallocate_heap_block(copy, allocSize += 500, 1);
		}
		copy[idx] = str[idx];
	}
	// reuse allocSize as last Idx storage;
	allocSize = idx;

	for (idx = 0; idx < allocSize; idx++)
	{
		str[idx] = copy[(allocSize - 1) - idx];
	}

	free_heap(copy);
}