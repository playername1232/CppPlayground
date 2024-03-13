#pragma once

#ifndef ARRFUNCDEFINE
#include "../MacroUtility/CustomMacros.h"
#include "../List Utility/List.h"
#endif

void reverse_str(char* str);

template<class T>
void reverse_array(T* arr, size_t count, size_t size)
{
	CHECK_SIZE(count);
	CHECK_SIZE(size);
	
	T* copy = (T*)allocate_heap_clean(count, size);
	for (size_t idx = 0; idx < count; idx++)
	{
		copy[idx] = arr[idx];
	}

	for (size_t idx = 0; idx < count; idx++)
	{
		arr[idx] = copy[(count - 1) - idx];
	}

	free_heap(copy);
}

template <typename T>
void sort_array(T* arr, size_t len)
{
	assert(std::is_arithmetic<T>::value);

	for (size_t i = 0; i < len; i++) 
	{
		for (size_t j = i + 1; j < len; j++) 
		{
			if (arr[i] > arr[j])
			{
				T temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}