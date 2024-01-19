#include "DynamicStringLibrary.h"
#include <iostream>

bool CheckForBufferOverflow(char* arr, size_t index, int& bufferAllocSize)
{
	if (index > (bufferAllocSize - 1)) // Index 9 = length 10 therefore max allocated size is 10
	{
		char* buffer = (char*)realloc(arr, bufferAllocSize + 1); // + 1 to add another character space
		bufferAllocSize += 1;

		if (buffer == nullptr || arr == nullptr)
			return false;

		std::cout << buffer[0] << "\t\t" << arr[0];

		if (buffer == nullptr)
			return false;

		arr = buffer;
	}
	return true;
}

void DynamicStringLibrary::DeleteDynamicString(const char** arrToFree, size_t numOfElements)
{
	for (size_t idx = 0; idx < numOfElements; idx++)
		InnerFree(const_cast<char*>(arrToFree[idx]));
}

char* DynamicStringLibrary::ConcatenateDynamicString(const char* str, const char* concate, const char splitter)
{
	int _currentBufferAlloc = 200;
	size_t currentIndex = 0,
		   lastIndexOfStr = 0;

	char* buffer = (char*)calloc(_currentBufferAlloc, 1);
	
	if (buffer == nullptr)
		throw std::exception("Failed to initialize buffer!");


	while (str[currentIndex] != '\0')
	{
		if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
			throw std::exception("Failed to initialize buffer!");

		buffer[currentIndex] = str[currentIndex];
		currentIndex += 1;
	}

	lastIndexOfStr = currentIndex;

	if (splitter != NULL)
	{

		currentIndex += 1;
		lastIndexOfStr += 1;

		if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
			throw std::exception("Failed to initialize buffer!");

		buffer[currentIndex] = ' ';
	}

	while (concate[currentIndex] != '\0')
	{
		if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
			throw std::exception("Failed to initialize buffer!");

		buffer[currentIndex] = concate[currentIndex - lastIndexOfStr];
		currentIndex += 1;
	}

	if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
		throw std::exception("Failed to initialize buffer!");

	buffer += '\0';

	return buffer;
}

char* DynamicStringLibrary::CreateDynamicString(const char* str, size_t len)
{
	if (len == 0)
		return nullptr;

	char* buffer = str[len-1] == '\0' ?
										(char*)calloc(len, 1) : 
										(char*)calloc(len + 1, 1); // +1 for null terminator


	if (buffer != nullptr)
	{
		for (size_t i = 0; i < len; i++)
			buffer[i] = str[i];

		buffer += '\0'; // Add null terminator

		return buffer;
	}
	else
		return nullptr;
}