#pragma once
#ifndef LISTDEF
#include <malloc.h>
#include <iostream>
#endif // !LISTDEF

template<class T>
class List
{
private:
	T* TCollection;
	size_t CollectionSize;

public:
	List()
	{
		TCollection = (T*)calloc(0, sizeof(T));
		CollectionSize = 0;
	}
	
	List(T* tArray, size_t arrSize)
	{
		if (CollectionSize != 0)
			free(TCollection);

		CollectionSize = arrSize;
		for (int i = 0; i < CollectionSize; i++)
		{
			TCollection = tArray[i];
		}
	}

	/// <summary>
	/// String currently non-functional!
	/// </summary>
	/// <param name="item"></param>
	void Add(T item)
	{
		T* buffer;
		CollectionSize += 1;

		size_t _sizePerElement = 0

		if (std::is_convertible_v<T, const char*>)
		{

		}

		if (CollectionSize == 1)
			buffer = (T*)calloc(1, sizeof(T));
		else
			buffer = (T*)realloc(TCollection, CollectionSize * _sizePerElement);
		

		if (buffer == nullptr)
			throw std::exception("List.h has thrown an exception: failed to allocate buffer!");

		buffer[CollectionSize - 1] = item;

		this->TCollection = buffer;
	}

	void Remove(T item)
	{
		for (int i = 0; i < CollectionSize; i++)
		{
			if (this->TCollection[i] == item)
			{
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