#pragma once

#include "pch.h"
#include <stdexcept>
#include <exception>
#include "Queue.h"

template <class T>
void Queue<T>::Enqueue(T item)
{
	if (head == nullptr && tail == nullptr)
	{
		head = new QueueNode<T>();
		head->data = item;
		tail = head;
	}
	else
	{
		auto prevTail = tail;
		tail = new QueueNode<T>();
		tail->data = item;
		prevTail->next = tail;
	}
}

template <class T>
T Queue<T>::Dequeue()
{
	if (head == nullptr && tail == nullptr)
	{
		throw std::out_of_range("Queue was empty.");
	}
	else
	{
		T retVal;
		if (head == tail)
		{
			retVal = head->data;
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			retVal = head->data;
			auto prevHead = head;
			head = head->next;
			delete prevHead;
		}
		return retVal;
	}
}

template <class T>
bool Queue<T>::IsEmpty()
{
	return head == nullptr;
}

template class Queue<int>; // to avoid linker errors