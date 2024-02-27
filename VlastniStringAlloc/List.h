#pragma once
#ifndef MALLOCDEF
#include <malloc.h>
#include "CustomMacros.h"
#endif // !LISTDEF

#ifndef STREAMDEF
#include <iostream>
#include <sstream>
#endif

template<typename T>
class List
{
private:
	T* TCollection;
	size_t CollectionSize;

public:
	List()
	{
		TCollection = nullptr;
		CollectionSize = 0;
	}
	
	List(T* tArray, size_t arrSize)
	{
		if (CollectionSize != 0)
			free(TCollection);

		TCollection = (T*)calloc(arrSize, sizeof(T));

		CollectionSize = arrSize;

		for (int i = 0; i < CollectionSize; i++)
		{
			TCollection = tArray[i];
		}
	}

	static char* ListToCharArray(List<char> _cList)
	{
		size_t listLen = _cList.GetCount();
		// +1 for null terminator
		char* ret = (char*)allocate_heap_clean(listLen + 1, 1);

		for (size_t size = 0; size < listLen; size++)
		{
			ret[size] = _cList[size];
		}

		ret[listLen + 1] = '\0';

		return ret;
	}

	/// <summary>
	/// String currently non-functional!
	/// </summary>
	/// <param name="item"></param>
	void Add(T item)
	{
		T* buffer = nullptr;
		this->CollectionSize += 1;

		size_t _sizePerElement = sizeof(T);

		bool isString = false;
		int  isCharArr = false;

		if (std::is_same<T, std::string>::value)
		{
			_sizePerElement = 1;
			isString = true;
		}
		if (std::is_same<T, char*>::value)
		{
			_sizePerElement = 1;
			isCharArr = true;
		}

		if (isString || isCharArr)
		{
			std::ostringstream oss {};
			oss << item;

			std::string pom = oss.str();
			char* strBuffer = _strdup(pom.c_str());

			if (strBuffer == nullptr)
				throw std::exception("List.h has thrown an exception: ostringstream returned nullptr on strBuffer!");


			size_t strSize = strlen(strBuffer);

			if (strBuffer[strSize - 1] != '\0')
			{
				try
				{
					char* pomStrBuffer = (char*)realloc(strBuffer, strSize + 1);
					if (pomStrBuffer == nullptr)
						throw std::exception("List.h has thrown an exception: failed to allocate strBuffer!");

					strBuffer = pomStrBuffer;
					strBuffer[strSize] = '\0';
					strSize += 1;
				}
				catch (std::exception ex)
				{
					std::cout << "CallStack Message: " << ex.what();
				}
			}

			if (CollectionSize == 1)
			{
				if (this->TCollection != nullptr)
					free(this->TCollection);

				buffer = (T*)calloc(1, sizeof(char*));
				if(buffer == nullptr)
					throw std::exception("Exception thrown in List.h: buffer allocation failed!");

				char* pomStr = (char*)calloc(strSize, 1);

				for (size_t idx = 0; idx < strSize; idx++)
					pomStr[idx] = strBuffer[idx];

				buffer[CollectionSize - 1] = _strdup(pomStr); // Tuto crashuje
			}
			else
			{
				buffer = (T*)realloc(this->TCollection, (CollectionSize + 1) * sizeof(T*));
				if (buffer == nullptr)
					throw std::exception("Exception thrown in List.h: buffer allocation failed!");

				char* pomStr = (char*)calloc(strSize, 1);

				for (size_t idx = 0; idx < strSize; idx++)
					pomStr[idx] = strBuffer[idx];

				buffer[CollectionSize - 1] = (T)pomStr; // Tuto crashuje
			}
		}
		else
		{
			if (CollectionSize == 1)
				buffer = (T*)calloc(1, sizeof(T));
			else
				buffer = (T*)realloc(TCollection, CollectionSize * _sizePerElement);


			if (buffer == nullptr)
				throw std::exception("List.h has thrown an exception: failed to allocate buffer!");

			buffer[CollectionSize - 1] = item;
		}

		this->TCollection = buffer;
	}

	void AddToEnd(T item)
	{
		// Hack solution. Reusing Add(T item) function for less repetive lines in the code
		this->Add(item);

		for (size_t i = this->CollectionSize - 1; i > 0; i--)
		{
			this->TCollection[i] = this->TCollection[i - 1];
		}

		this->TCollection[0] = item;
	}

	void Remove(T item)
	{
		for (int i = 0; i < CollectionSize; i++)
		{
			if (this->TCollection[i] == item)
			{
				size_t _sizePerElement = sizeof(T);

				T* buffer = (T*)realloc(TCollection, CollectionSize * _sizePerElement);
				if (buffer == nullptr)
					throw std::exception("List.h has thrown an exception: failed to allocate buffer!");

				for (int j = i; j < CollectionSize - 1; j++)
					this->buffer[j] = this->TCollection[j + 1];

				buffer = (T*)realloc(TCollection, (CollectionSize - 1) * _sizePerElement);
				if (buffer == nullptr)
					throw std::exception("List.h has thrown an exception: failed to allocate buffer!");

				this->TCollection = buffer;

				return;
			}
		}
	}

	void Clear()
	{
		free_heap(this->TCollection);
		
		this->TCollection = nullptr;
		this->CollectionSize = 0;
	}

	static void Move(List<T>& outList, T* arr, size_t len)
	{
		if (outList.TCollection != nullptr)
			free_heap(outList.TCollection);

		for (size_t idx = 0; idx < len; idx++)
			outList.Add(arr[idx]);

		outList.CollectionSize = len;
	}
	
	static void MoveAndFreePrevious(List<T>& outList, T*& arr, size_t len)
	{
		if (outList.TCollection != nullptr)
			free_heap(outList.TCollection);

		for (size_t idx = 0; idx < len; idx++)
			outList.Add(arr[idx]);

		outList.CollectionSize = len;
		free_heap(arr);
		arr = nullptr;
	}

	size_t GetCount()
	{
		return this->CollectionSize;
	}

	T operator[](size_t idx)
	{
		if (idx >= this->CollectionSize)
			return NULL;
		return TCollection[idx];
	}
};