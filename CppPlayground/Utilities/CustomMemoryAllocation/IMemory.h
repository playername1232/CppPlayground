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
	size_t bitSize = 0;

	void (*memoryAllocatedCallback)();
	void (*memoryEditedCallback)();
	void (*memoryFreedCallback)();
	
public:
	IMemory(size_t size = 1, void (*memAllocCallback)()  = nullptr,
							 void (*memEditCallback)()   = nullptr,
							 void (*memFreedCallback)()  = nullptr)
								: memoryAllocatedCallback(memAllocCallback),
							      memoryEditedCallback(memEditCallback), 
								  memoryFreedCallback(memFreedCallback)
	{
		if(size == 0)
			return;

		ptr = (T*)allocate_heap_clean(size, sizeof(T));
		end = ptr + size;
		this->size = size;
		this->bitSize = sizeof(T) * 8;

		if (memoryAllocatedCallback != nullptr)
			memoryAllocatedCallback();
	}

	~IMemory()
	{
		free_heap(ptr);
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

	size_t GetMemorySize()			{ return this->size; }

	size_t GetMemoryElementBitSize()	{ return this->bitSize; }

	size_t GetMemoryByteSize()		{ return this->size * sizeof(T); }


	void ANDMemValue(T mask, size_t offset)
	{
		if (offset >= size)
		{
			std::ostringstream oss{};
			oss << __FUNCTION__ << ": offset >= size : Offset is out of range! Offsetting " << offset << " in " << size << " sized array!";

			throw std::out_of_range(oss.str());
		}

		this[offset] &= mask;
	}
	void NANDMemValue(T mask, size_t offset)
	{
		if (offset >= size)
		{
			std::ostringstream oss{};
			oss << __FUNCTION__ << ": offset >= size : Offset is out of range! Offsetting " << offset << " in " << size << " sized array!";

			throw std::out_of_range(oss.str());
		}

		this[offset] &= ~mask;
	}
	void ORMemValue(T mask, size_t offset)
	{
		if (offset >= size)
		{
			std::ostringstream oss{};
			oss << __FUNCTION__ << ": offset >= size : Offset is out of range! Offsetting " << offset << " in " << size << " sized array!";

			throw std::out_of_range(oss.str());
		}
		
		this[offset] |= mask;
	}
	void NORMemValue(T mask, size_t offset)
	{
		if (offset >= size)
		{
			std::ostringstream oss{};
			oss << __FUNCTION__ << ": offset >= size : Offset is out of range! Offsetting " << offset << " in " << size << " sized array!";

			throw std::out_of_range(oss.str());
		}

		this[offset] |= ~mask;
	}
	void XORMemValue(T mask, size_t offset)
	{
		if (offset >= size)
		{
			std::ostringstream oss{};
			oss << __FUNCTION__ << ": offset >= size : Offset is out of range! Offsetting " << offset << " in " << size << " sized array!";

			throw std::out_of_range(oss.str());
		}

		this[offset] ^= mask;
	}
	void XNORMemValue(T mask, size_t offset)
	{
		if (offset >= size)
		{
			std::ostringstream oss{};
			oss << __FUNCTION__ << ": offset >= size : Offset is out of range! Offsetting " << offset << " in " << size << " sized array!";

			throw std::out_of_range(oss.str());
		}

		this[offset] ^= ~mask;
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
				std::cerr << "Exception: " << e.what() << '\n';
			}
		}
		return ptr[idx];
	}

	
	/**
	 * @tparam _To New data type
	 * @param src IMemory type Source
	 * @param memAllocCallback Pointer to Callback function called when: New Memory allocation / reallocation occurs
	 * @param memEditCallback Pointer to Callback function called when: Memory is edited
	 * @param memFreedCallback Pointer to Callback function called when: Memory is freed 
	 * @return Pointer to new Memory object 
	 */
	template<typename _From>
	static IMemory* CopyTo(IMemory<_From>* src, 
							void (*memAllocCallback)() = nullptr,
							void (*memEditCallback)() = nullptr,
							void (*memFreedCallback)() = nullptr)
	{
		IMemory<T>* mem = new IMemory<T>(src->GetMemorySize());

		for (int i = 0; i < src->GetMemorySize(); i++)
		{
			mem[i] = 0x0;

			int srcBitSize = (src->GetMemoryByteSize() * 8);
			
			size_t _cpyBits = mem->bitSize > srcBitSize ? srcBitSize : mem->bitSize;
			for (int j = 0; j < _cpyBits; j++)
			{
				mem[i] |= (src[i] >> j) & 1;
			}
		}

		return mem;
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

