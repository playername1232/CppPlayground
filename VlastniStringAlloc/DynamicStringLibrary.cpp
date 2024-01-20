#include "DynamicStringLibrary.h"
#include <iostream>
#include <cctype>

/// <summary>
/// Checks for buffer overflow, increases memory allocation if the overflow would occur
/// </summary>
/// <param name="arr">Allocated Memory</param>
/// <param name="index">Used index</param>
/// <param name="bufferAllocSize">Allocated size</param>
/// <returns></returns>
static bool CheckForBufferOverflow(char*& arr, size_t index, int& bufferAllocSize)
{
	if (arr == nullptr)
		return false;

	if (index > (bufferAllocSize - 1)) // Index 9 = length 10 therefore max allocated size is 10
	{
		bufferAllocSize += 1;
		char* buffer = (char*)realloc(arr, bufferAllocSize); // + 1 to add another character space

		if (buffer == nullptr)
			return false;

		arr = buffer;
	}
	return true;
}

char* DynamicStringLibrary::CreateDynamicString(const char* str, size_t len)
{
	if (len == 0)
		return nullptr;

	char* buffer = str[len - 1] == '\0' ?
		(char*)calloc(len, 1) :
		(char*)calloc(len + 1, 1); // +1 for null terminator


	if (buffer != nullptr)
	{
		size_t idx = 0;
		for (size_t idx = 0; idx < len; idx++)
			buffer[idx] = str[idx];

		if (buffer[len - 1] != '\0')
		{
			buffer = (char*)realloc(buffer, len + 1);

			if (buffer == nullptr)
				return nullptr;

			buffer[len] = '\0';
		}

		return buffer;
	}
	else
		return nullptr;
}

char* DynamicStringLibrary::ConcatenateDynamicString(const char* str, const char* concate, const char splitter)
{
	int _currentBufferAlloc = 2;
	size_t currentIndex = 0,
		   lastIndexOfStr = 0;

	char* buffer = (char*)calloc(_currentBufferAlloc, 1);
	
	if (buffer == nullptr)
		throw std::exception("Failed to initialize buffer!");


	for (int i = 0; str[i] != '\0'; i++, currentIndex += 1)
	{
		if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
			throw std::exception("Failed to initialize buffer!");

		buffer[currentIndex] = str[currentIndex];
	}


	if (splitter != NULL)
	{
		if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
			throw std::exception("Failed to initialize buffer!");

		buffer[currentIndex] = splitter;
		currentIndex += 1;
	}


	for (int i = 0; concate[i] != '\0'; i++, currentIndex += 1)
	{
		if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
			throw std::exception("Failed to initialize buffer!");

		buffer[currentIndex] = concate[i];
	}

	if (buffer[currentIndex] != '\0')
	{
		if (CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc) == false)
			throw std::exception("Failed to initialize buffer!");

		buffer[currentIndex] = '\0';
	}

	return buffer;
}

void DynamicStringLibrary::DeleteDynamicString(const char** arrToFree, size_t numOfElements)
{
	for (size_t idx = 0; idx < numOfElements; idx++)
		InnerFree(const_cast<char*>(arrToFree[idx]));
}

void DynamicStringLibrary::ExtractFirstDynamicString(char*& str, const char* extractStr, size_t sizeExtract)
{
	size_t strSize = 0;
	int foundSamples = 0;
	int startIndex = -1, endIndex = -1;

	bool pass = false;

	for (int i = 0; str[i] != '\0'; i++, strSize++)
	{
		if (pass)
			continue;

		if (str[i] == extractStr[foundSamples])
		{
			if (startIndex == -1)
			{
				startIndex = i;
				endIndex = i;
				foundSamples += 1;
			}
			else
			{
				endIndex = i;
				foundSamples += 1;
			}

			// Finish counting the length of string
			if (foundSamples == sizeExtract)
				pass = true;
		}
		else
		{
			startIndex = -1;
			endIndex = -1;
			foundSamples = 0;
		}
	}

	if (startIndex == -1 || endIndex == -1)
		return;

	size_t buffSize = strSize - (endIndex - startIndex + 1);
	// Add additional for null terminator
	char* buffer = (char*)calloc(buffSize + 1, 1);

	if (buffer == nullptr)
		throw std::exception("str reallocation has failed!");

	int bufferIndex = 0;
	for (int i = 0; i < strSize; i++)
	{
		if (i >= startIndex && i <= endIndex)
		{
			continue; // Skip extracted string
		}
		buffer[bufferIndex++] = str[i];
	}

	str = buffer;
}

char* DynamicStringLibrary::CopyDynamicString(const char* str)
{
	size_t strLength = 0;

	while (str[strLength] != '\0')
		++strLength;

	char* buffer = (char*)calloc(strLength + 1, 1);  // +1 for the null terminator

	if (buffer == nullptr)
		throw std::exception("buffer allocation failed!");

	for (size_t i = 0; i < strLength; ++i) {
		buffer[i] = str[i];
	}

	// Add the null terminator at the end of buffer
	buffer[strLength] = '\0';

	return buffer;
}

bool DynamicStringLibrary::CompareDynamicString(const char* str1, const char* str2)
{
	size_t lenStr1 = 0,
		   lenStr2 = 0;

	for (int i = 0; str1[i] != '\0'; i++)
		lenStr1++;

	for (int i = 0; str2[i] != '\0'; i++)
		lenStr2++;

	if (lenStr1 != lenStr2)
		return false;

	for (int i = 0; i < lenStr1; i++)
	{
		if (str1[i] != str2[i])
			return false;
	}

	return true;
}

char* DynamicStringLibrary::ReverseDynamicString(const char* str)
{
	size_t strSize = 0;

	for (int i = 0; str[i] != '\0'; i++)
		strSize++;

	char* res = (char*)calloc(strSize + 1, 1);

	if (res == nullptr)
		return nullptr;

	for (int i = 0; i < strSize; i++)
	{
		res[i] = str[(strSize - 1) - i];
	}

	return res;
}
