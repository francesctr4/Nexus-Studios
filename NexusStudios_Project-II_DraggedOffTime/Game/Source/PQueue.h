#pragma once

// ----------------------------------------------------
// Prority FIFO implementation with single linked list  -------
// ----------------------------------------------------

#include "Defs.h"

/**
* Contains items from double linked list
*/
template<class tdata>
struct PQueueItem
{
	tdata data;
	int priority;
	PQueueItem<tdata>* next = nullptr;

	PQueueItem(const tdata& pData, int priority) : data(pData), priority(priority)
	{}
};

/**
* Manages a double linked list
*/
template<class tdata>
class PQueue
{

public:

	PQueueItem<tdata>* start;

public:

	/**
	* Constructor
	*/
	inline PQueue() : start(NULL)
	{}

	/**
	* Destructor
	*/
	~PQueue()
	{
		Clear();
	}

	/**
	* Get Size
	*/
	unsigned int Count() const
	{
		unsigned int result = 0;
		PQueueItem<tdata>* tmp;

		for (tmp = start; tmp != NULL; tmp = tmp->next)
			++result;

		return result;
	}

	/**
	* Get last item
	*/
	PQueueItem<tdata>* GetLast()
	{
		PQueueItem<tdata>* tmp = start;

		while (tmp != NULL && tmp->next != NULL)
			tmp = tmp->next;

		return tmp;
	}

	/**
	* push new item
	*/
	void Push(const tdata& item, int priority)
	{
		PQueueItem<tdata>* pDataItem;
		pDataItem = new PQueueItem < tdata >(item, priority);

		PQueueItem<tdata>* last = GetLast();

		if (last == NULL)
		{
			start = pDataItem;
		}
		else
		{
			PQueueItem<tdata>* prev = start;
			PQueueItem<tdata>* tmp = start;

			while (tmp && tmp->priority <= priority)
			{
				prev = tmp;
				tmp = tmp->next;
			}

			pDataItem->next = tmp;
			if (tmp == start)
				start = pDataItem;
			else
				prev->next = pDataItem;
		}
	}

	/**
	* Deletes an item from the list
	*/
	bool Pop(tdata& item)
	{
		bool result = false;

		if (start != nullptr)
		{
			PQueueItem<tdata>* new_start = start->next;
			item = start->data;
			RELEASE(start);
			start = new_start;
			result = true;
		}

		return result;
	}

	/**
	* Reads one of the values
	*/
	const tdata* Peek(unsigned int index) const
	{
		unsigned int i = 0;
		PQueueItem<tdata>* tmp;

		for (tmp = start; tmp != NULL && i < index; tmp = tmp->next)
			++i;

		if (tmp != NULL)
			return &(tmp->data);

		return NULL;
	}

	/**
	* Destroy and free all mem
	*/
	void Clear()
	{
		PQueueItem<tdata>* pData;
		PQueueItem<tdata>* pNext;
		pData = start;

		while (pData != NULL)
		{
			pNext = pData->next;
			RELEASE(pData);
			pData = pNext;
		}

		start = NULL;
	}

};