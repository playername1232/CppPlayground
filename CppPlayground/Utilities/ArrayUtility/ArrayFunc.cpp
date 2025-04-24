#include "ArrayFunc.h"

char* reverse_str(char* str)
{
	if (str[0] == '\0' || strlen(str) == 0)
		return nullptr;

	size_t size = strlen(str);
	char* copy = (char*)allocate_heap_clean(size, 1);
	
	const size_t iterate_start = str[size - 1] == '\0' ? size - 2 : size - 1;
	
	for(int write = 0, i = (int)iterate_start; i >= 0 ; write++, i--)
	{
		copy[write] = str[i];
	}
	
	if(copy[size - 1] != '\0')
	{
		char* buffer = (char*)reallocate_heap_block(copy, size + 1, 1);
		check(buffer);

		buffer[size] = '\0';
		copy = buffer;
	}

	return copy;
}