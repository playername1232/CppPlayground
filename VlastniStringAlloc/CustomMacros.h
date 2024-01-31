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

template<typename T>
T remove_const(const T* ptr)
{
	return *ptr;
}