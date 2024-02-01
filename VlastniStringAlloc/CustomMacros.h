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
		char* res = ((DynamicStringLibrary)ptr).GetContent();

		return res;
	}

	return *ptr;
}