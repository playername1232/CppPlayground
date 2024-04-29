#include "../MacroUtility/CustomMacros.h"
#include <iostream>
#include <sstream>

template<typename T>
class IMemory
{
private:
	T* ptr = nullptr;
	T* end = nullptr;

	size_t size = 0;
	
public:

	void (*memoryAllocatedCallback)();
	void (*memoryEditedCallback)();
	void (*memoryFreedCallback)();

	IMemory(size_t size = 1, void(*memAllocCallback)()  = nullptr,
							 void (*memEditCallback)()  = nullptr,
							 void (*memFreedCallback)()  = nullptr) 
								: memoryAllocatedCallback(memAllocCallback),
							      memoryEditedCallback(memEditCallback), 
								  memoryFreedCallback(memFreedCallback)
	{
		check_size(size);

		ptr = (T*)allocate_heap_clean(size, sizeof(T));
		end = ptr + size;
		this->size = size;

		if (memoryAllocatedCallback != nullptr)
			memoryAllocatedCallback();
	}

	~IMemory()
	{
		if (this->memoryFreedCallback != nullptr)
			this->memoryFreedCallback();
	}

	/// <summary>
	/// Retrieves a pointer to first item stored in the memory block
	/// </summary>
	/// <returns>Return pointer to first stored item in the memory block</returns>
	T* GetStart()
	{
		return ptr;
	}

	/// <summary>
	/// Retrieves a pointer to either the last item in the allocated memory pool or the first memory block outside of the allocated heap block.
	/// </summary>
	/// <param name="lastItem">Determiners whether to get pointer to last item in memory or get pointer to first memory block outside of the allocated heap block</param>
	/// <returns>Returns either pointer to last item in the pool or the first memory block outside of the allocated heap block</returns>
	T* GetEndOfHeap(bool lastItem = false)
	{
		if (lastItem)
		{
			// Return pointer to the last item in the memory pool
			return end - 1;
		}
		// Return pointer to the first memory block outside oof of the memory pool
		return end;
	}

	bool IsMemoryWithinRange(T* searchPtr)
	{
		DWORD64 searchAdd = reinterpret_cast<DWORD64>(&searchPtr);
		DWORD64 ptrAdd = reinterpret_cast<DWORD64>(&ptr);
		DWORD64 endAdd = reinterpret_cast<DWORD64>(&end);

		return ptrAdd >= searchAdd && searchAdd < endAdd;
	}

	void ResizeMemory(int newSize)
	{
		if (newSize == this->size)
			return;

		this->ptr = (T*)reallocate_heap_block(this->ptr, size, sizeof(T));
		end = ptr + newSize;
		this->size = newSize;

		if (this->memoryEditedCallback != nullptr)
			this->memoryEditedCallback();
	}

	T& operator[](size_t idx)
	{
		if (idx >= size)
		{
			try 
			{
				std::ostringstream oss{};
				oss << __FUNCTION__ << ": idx >= size : Index is out of range!Accessing index " << idx << " in " << size << " sized array!";

				throw std::out_of_range(oss.str());
			}
			catch (std::exception& e)
			{
				std::cerr << "Exception: " << e.what() << std::endl;
			}
		}
		return ptr[idx];
	}

	static IMemory* CreateMemoryBlock(T* ptr, size_t size, 
											  void (*memAllocCallback)() = nullptr,
											  void (*memEditCallback)()  = nullptr,
											  void (*memFreedCallback)() = nullptr)
	{
		check(ptr);
		check_size(size);

		IMemory* mem = new IMemory<T>(size, memAllocCallback, memEditCallback, memFreedCallback);

		for (size_t i = 0; i < size; i++)
		{
			(*mem)[i] = ptr[i];
		}

		return mem;
	}
};

