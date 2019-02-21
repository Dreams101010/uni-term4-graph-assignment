#ifndef H_QueueNode
#define H_QueueNode

template <class T>
struct QueueNode
{
	T data;
	QueueNode<T>* next;
};

#endif // !H_QueueNode