#pragma once

#ifndef STREAMDEF
#include <sstream>
#endif

template<typename T>
struct ListNode
{
	T _val;
	ListNode* next;

	ListNode() : _val(0), next(nullptr) {}
	ListNode(T _val) : _val(_val), next(nullptr) {}
	ListNode(T _val, ListNode* next) : _val(_val), next(next) {}
};

template<typename T>
class List
{
	
private:
	ListNode<T>* head;
	ListNode<T>* tail;
	
	size_t CollectionSize;

public:
	List() : head(nullptr), tail(nullptr), CollectionSize(0) {}
	
	List(T* tArray, size_t arrSize)
	{
		if(arrSize == 0)
		{
			this->head = nullptr;
			this->tail = nullptr;
		}

		this->head = new ListNode<T>(tArray[0]);
		this->tail = head;

		ListNode<T>* prev = tail;

		for(size_t i = 1; i < arrSize; i++)
		{
			tail->next = new ListNode<T>(tArray[i]);
			tail = tail->next;
		}

		this->CollectionSize = arrSize;
	}

	List(const List<T>& other) : head(nullptr), tail(nullptr), CollectionSize(0)
	{
		if(other.CollectionSize == 0)
			return;
		
		this->head = new ListNode<T>(other.head->_val);
		this->tail = head;

		ListNode<T>* _it = other.head->next;

		while(_it != nullptr)
		{
			this->tail->next = new ListNode<T>(_it->_val);
			this->tail = this->tail->next;
			_it = _it->next;
		}

		this->CollectionSize = other.CollectionSize;
	}
	
	~List() { this->Clear(); }

	
	/**
	 * Adds item to List
	 * @param item Item to be added to List
	 */
	void Add(T item)
	{
		if(head == nullptr)
		{
			head = new ListNode<T>(item);
			tail = head;
		}

		ListNode<T>* node = new ListNode<T>(item);
		this->tail->next = node;
		this->tail = node;

		this->CollectionSize += 1;
	}
	
	/**
	 * Removes all occurences of given item in the List
	 * @param item Item to be removed
	 */
	void Remove(T item)
	{
		if(head == nullptr)
			return;

		while (head->_val == item)
		{
			ListNode<T>* temp = head->next;
			delete head;

			head = temp;
			this->CollectionSize -= 1;

			if(head == nullptr)
				return;
		}

		ListNode<T>* prev = head;
		ListNode<T>* it = prev->next;
		
		while(it != nullptr)
		{
			if(it->_val == item)
			{
				ListNode<T>* temp = it;
				
				it = it->next;
				prev->next = it;
				
				delete temp;
				this->CollectionSize -= 1;

				continue;
			}

			prev = it;
			it = it->next;
		}

		this->tail = prev;
	}

	/** Erase List and frees memory occupied by its elements */
	void Clear()
	{
		this->CollectionSize = 0;
		this->tail = this->head;
		
		while(tail != nullptr)
		{
			ListNode<T>* temp = tail;
			tail = tail->next;

			delete temp;
		}
	}
	
	/** @return Count of elements in the List */
	size_t GetCount()
	{
		return this->CollectionSize;
	}

	T operator[](size_t idx)
	{
		if (idx >= this->CollectionSize)
			return (T)0x0;

		ListNode<T>* node = this->head;
		
		for(int i = 1; i < idx; i++)
		{
			node = node->next;
			if(node == nullptr)
				return (T)0x0;
		}

		return node->_val;
	}

	List<T>& operator=(const List<T> other)
	{
		std::swap(this->head, other.head);
		return *this;
	}
	
	/**
	 * Copies items from Array to new List instance
	 * @param arr Array to be copied to List
	 * @param len Length of the array
	 * @return Array elements copied to List instance
	 */
	static List<T> Copy(T* arr, size_t len)
	{
		List<T> outList(arr, len);

		return outList;
	}
};