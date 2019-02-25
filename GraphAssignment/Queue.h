#ifndef H_Queue
#define H_Queue

#include "QueueNode.h"

template <class T>
class Queue // valid for primitives (type T)
{
	QueueNode<T>* head = nullptr;
	QueueNode<T>* tail = nullptr;

public:
	void Enqueue(T item);
	T Dequeue();
	bool IsEmpty();
};

#endif // !H_Queue