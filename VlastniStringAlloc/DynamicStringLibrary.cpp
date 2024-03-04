#include "DynamicStringLibrary.h"
#include <iostream>
#include <cctype>
#include "CustomMacros.h"

// Size of allocations in Bytes
#define DEFAULT_ALLOC_BLOCK_SIZE 500;

/// <summary>
/// Checks for buffer overflow, increases memory allocation if the overflow would occur
/// </summary>
/// <param name="arr">Allocated Memory</param>
/// <param name="index">Used index</param>
/// <param name="bufferAllocSize">Allocated size</param>
/// <returns></returns>
static void CheckForBufferOverflow(char*& arr, size_t index, int& bufferAllocSize)
{
	check(arr);

	check_size(index);
	check_size(bufferAllocSize);

	if (index > (bufferAllocSize - 1)) // Index 9 = length 10 therefore max allocated size is 10
	{
		bufferAllocSize += DEFAULT_ALLOC_BLOCK_SIZE;
		char* buffer = (char*)reallocate_heap_block(arr, bufferAllocSize, 1);
		check(buffer);

		arr = buffer;
	}
}

char* DynamicStringLibrary::CreateDynamicString(const char* str, size_t len)
{
	if (len == 0)
		return nullptr;

	char* buffer = str[len - 1] == '\0' ?
		(char*)allocate_heap_clean(len, 1) :
		(char*)allocate_heap_clean(len + 1, 1);  // +1 for null terminator


	if (buffer != nullptr)
	{
		size_t idx = 0;
		for (size_t idx = 0; idx < len; idx++)
			buffer[idx] = str[idx];

		if (buffer[len - 1] != '\0')
		{
			buffer = (char*)reallocate_heap_block(buffer, len + 1, len);

			buffer[len] = '\0';
		}

		return buffer;
	}
	else
		return nullptr;
}

char* DynamicStringLibrary::ConcatenateDynamicString(const char* str, const char* concate, const char splitter)
{
	int _currentBufferAlloc = DEFAULT_ALLOC_BLOCK_SIZE;
	size_t currentIndex = 0,
		   lastIndexOfStr = 0;

	char* buffer = (char*)allocate_heap_clean(_currentBufferAlloc, 1);

	for (int i = 0; str[i] != '\0'; i++, currentIndex += 1)
	{
		CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc);
		buffer[currentIndex] = str[currentIndex];
	}


	if (splitter != '\0')
	{
		CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc);

		buffer[currentIndex] = splitter;
		currentIndex += 1;
	}


	for (int i = 0; concate[i] != '\0'; i++, currentIndex += 1)
	{
		CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc);
		buffer[currentIndex] = concate[i];
	}

	if (buffer[currentIndex] != '\0')
	{
		CheckForBufferOverflow(buffer, currentIndex, _currentBufferAlloc);
		buffer[currentIndex] = '\0';
	}

	// Resize the buffer to its content size 
	buffer = (char*)reallocate_heap_block(buffer, currentIndex + 1, 1);

	return buffer;
}

void DynamicStringLibrary::DeleteDynamicString(const char** arrToFree, size_t numOfElements)
{
	for (size_t idx = 0; idx < numOfElements; idx++)
		free_heap(const_cast<char*>(arrToFree[idx]));
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

	char* buffer = (char*)allocate_heap_clean(buffSize + 1, 1); // +1 for the null terminator

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
	size_t i = 0;
	size_t currentAlloc = DEFAULT_ALLOC_BLOCK_SIZE;


	char* buffer = (char*)allocate_heap_clean(currentAlloc, 1);

	for (/* i = 0 */ ; str[i] != '\0'; i++)
	{
		if (i == (currentAlloc - 1))
		{
			currentAlloc += DEFAULT_ALLOC_BLOCK_SIZE;
			buffer = (char*)reallocate_heap_block(buffer, currentAlloc, 1);
		}

		buffer[i] = str[i];
	}

	// Add the null terminator at the end of buffer - Sanity check
	if (buffer[i] != '\0')
	{
		i += 1;

		if (i == (currentAlloc - 1))
		{
			currentAlloc += 1;
			buffer = (char*)reallocate_heap_block(buffer, currentAlloc, 1);

			return buffer;
		}

		buffer[i] = '\0';
	}

	// Reallocate buffer according to content
	buffer = (char*)reallocate_heap_block(buffer, i + 1, 1);
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

	char* res = (char*)allocate_heap_clean(strSize + 1, 1);

	for (int i = 0; i < strSize; i++)
	{
		res[i] = str[(strSize - 1) - i];
	}

	return res;
}

DynamicStringLibrary::DynamicStringLibrary(const char* entry)
{
	this->content = nullptr;
	this->contentSize = 0;

	size_t strSize = 0;
	// len counter no condition necessary
	for (size_t i = 0; entry[i] != '\0'; i++, strSize++) {}

	this->content = (char*)allocate_heap_clean(strSize, 1);

	for (size_t i = 0; i < strSize; i++)
	{
		this->content[i] = entry[i];

		if (i == strSize - 1)
		{
			if (this->content[i] != '\0')
			{				
				char* buffer = (char*)reallocate_heap_block(this->content, strSize + 1, 1);

				buffer[i + 1] = '\0';

				this->content = buffer;
				this->contentSize = 1; // Count the null terminator
			}

			this->contentSize += strSize; // add string size
			return;
		}
	}
}

void DynamicStringLibrary::operator=(const char* entry)
{
	if (this->content != nullptr)
		free_heap(this->content);
	this->content = const_cast<char*>(entry);
}

void DynamicStringLibrary::operator+=(const char* entry)
{
	size_t strSize = 0;

	// len counter no condition necessary
	for (size_t i = 0; entry[i] != '\0'; i++, strSize++) { }

	if(this->contentSize == 0)
	{
		this->content = (char*)allocate_heap_clean(strSize, 1);

		for (size_t i = 0; i < strSize; i++)
		{
			this->content[i] = entry[i];

			if (i == strSize - 1)
			{
				if (this->content[i] != '\0')
				{
					char* buffer = (char*)allocate_heap_clean(strSize, 1 + 1);
					buffer[i + 1] = '\0';

					this->content = buffer;
					this->contentSize = 1; // Count the null terminator
				}

				this->contentSize += strSize; // add string size
				return;
			}
		}
	}

	char* buffer = (char*)reallocate_heap_block(this->content, (this->contentSize - 1) + strSize, 1); // excluding null terminator from content (it is included in entry size)

	for (size_t i = 0; i < strSize; i++)
	{
		// null terminator is located on buffer[size - 1] -> "abc" = 4 len > "abc"[3] = '\0'
		buffer[(this->contentSize - 1) + i] = entry[i];

		if (i == strSize - 1)
		{
			if (entry[i] != '\0')
			{
				this->content = (char*)reallocate_heap_block(buffer, this->contentSize + strSize, 1);
				
				this->content[contentSize + i] = '\0';
				this->contentSize += 1;

				return;
			}
		}
	}
}

char* DynamicStringLibrary::operator*()
{
	if (this->content == nullptr)
		return nullptr;
	return this->content;
}

std::ostream& operator<<(std::ostream& os, const DynamicStringLibrary& _string)
{
	os << _string.content;
	return os;
}
