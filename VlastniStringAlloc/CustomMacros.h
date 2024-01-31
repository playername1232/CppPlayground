#pragma once

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