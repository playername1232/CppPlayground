#include "DynamicStringLibrary.h"
#include <iostream>
#include <cctype>
#include "../MacroUtility/CustomMacros.h"

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

	// Edit: check_size_allow_zero(len) as index can be zero
	check_size_allow_zero(index);
	check_size(bufferAllocSize);

	if (index > (bufferAllocSize - 1)) // Index 9 = length 10 therefore max allocated size is 10
	{
		bufferAllocSize += DEFAULT_ALLOC_BLOCK_SIZE;
		arr = (char*)reallocate_heap_block(arr, bufferAllocSize, 1);
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
	int current_buffer_alloc = DEFAULT_ALLOC_BLOCK_SIZE;
	size_t currentIndex = 0,
		   lastIndexOfStr = 0;

	char* buffer = (char*)allocate_heap_clean(current_buffer_alloc, 1);

	for (int i = 0; str[i] != '\0'; i++, currentIndex += 1)
	{
		CheckForBufferOverflow(buffer, currentIndex, current_buffer_alloc);
		buffer[currentIndex] = str[currentIndex];
	}


	if (splitter != '\0')
	{
		CheckForBufferOverflow(buffer, currentIndex, current_buffer_alloc);

		buffer[currentIndex] = splitter;
		currentIndex += 1;
	}


	for (int i = 0; concate[i] != '\0'; i++, currentIndex += 1)
	{
		CheckForBufferOverflow(buffer, currentIndex, current_buffer_alloc);
		buffer[currentIndex] = concate[i];
	}

	if (buffer[currentIndex] != '\0')
	{
		CheckForBufferOverflow(buffer, currentIndex, current_buffer_alloc);
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

	if(entry[0] == '\0')
		return;
	
	int arrAlloc = DEFAULT_ALLOC_BLOCK_SIZE;
	// len counter no condition necessary - to be remade using DEFAULT_ALLOC_BLOCK_SIZE
	
	// for (size_t i = 0; entry[i] != '\0'; i++, strSize++) {}

	this->content = (char*)allocate_heap_clean(arrAlloc, 1);

	for (size_t i = 0; entry[i] != '\0'; i++, this->contentSize++)
	{
		CheckForBufferOverflow(this->content, i, arrAlloc);

		this->content[i] = entry[i];
	}

	// Add null terminator
	this->contentSize += 1;
	this->content = (char*)reallocate_heap_block(this->content, this->contentSize, 1);

	this->content[contentSize - 1] = '\0';
}

/*DynamicStringLibrary::~DynamicStringLibrary()
{
	free_heap(this->content);
}*/

void DynamicStringLibrary::operator=(const char* entry)
{
	if(entry[0] == '\0')
	{
		this->content = nullptr;
		this->contentSize = 0;
	}
	
	if (this->content != nullptr)
		free_heap(this->content);
	this->contentSize = 0;

	this->content = const_cast<char*>(entry);
	for (int i = 0; this->content[i] != '\0'; i++)
		this->contentSize += 1;

	// Increment null terminator
	this->contentSize += 1;
}

void DynamicStringLibrary::operator+=(const char* entry)
{
	check(entry);

	// Size must not be negative
	check_size_allow_zero(this->contentSize);

	int arrayAlloc = DEFAULT_ALLOC_BLOCK_SIZE;

	if(this->contentSize == 0)
	{
		if (this->content != nullptr)
			free_heap(this->content);

		this->content = (char*)allocate_heap_clean(arrayAlloc, 1);

		for (size_t i = 0; entry[i] != '\0'; i++)
		{
			CheckForBufferOverflow(this->content, i, arrayAlloc);

			this->content[this->contentSize] = entry[i];
			this->contentSize += 1;
		}
		
		if (this->content[this->contentSize - 1] != '\0')
		{
			CheckForBufferOverflow(this->content, this->contentSize, arrayAlloc);
			this->content[this->contentSize] = '\0';
			this->contentSize += 1;
		}

		this->content = (char*)reallocate_heap_block(this->content, this->contentSize, 1);

		return;
	}

	while (arrayAlloc < this->contentSize)
	{
		arrayAlloc += DEFAULT_ALLOC_BLOCK_SIZE;
	}
	this->content = (char*)reallocate_heap_block(this->content, arrayAlloc, 1);
	
	for (size_t i = 0; entry[i] != '\0'; i++)
	{
		CheckForBufferOverflow(this->content, i, arrayAlloc);

		this->content[contentSize - 1] = entry[i];
		this->contentSize += 1;
	}
		
	if (this->content[this->contentSize - 1] != '\0')
	{
		this->content[this->contentSize - 1] = '\0';
	}

 	this->content = (char*)(reallocate_heap_block(this->content, this->contentSize, 1));
}

void DynamicStringLibrary::operator+=(const char entry)
{
	if(entry == '\0')
		return;
	
	this->content = static_cast<char*>(reallocate_heap_block(this->content, this->contentSize + 1, 1));
	this->content[contentSize - 1] = entry;
	this->content[contentSize] = '\0';
	this->contentSize += 1;
}

char* DynamicStringLibrary::operator*()
{
	if (this->content == nullptr)
		return nullptr;
	return this->content;
}

std::ostream& operator<<(std::ostream& os, const DynamicStringLibrary& str)
{
	os << str.content;
	return os;
}
