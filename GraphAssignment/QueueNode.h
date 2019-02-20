#pragma once

template <class T>
struct QueueNode
{
	T data;
	QueueNode<T>* next;
};