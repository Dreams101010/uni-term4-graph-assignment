#pragma once

#include <memory>
#include "Matrix.h"
#include "BFSTree.h"

class Graph
{
	std::shared_ptr<Matrix<int>> m;
public:
	Graph(int nodeCount);
	bool IsValidIndex(int index);
	void AddEdge(int node1, int node2);
	void RemoveEdge(int node1, int node2);
	bool IsSingleComponent();
	// TODO: check the need of the shared pointers
	BFSTree BFS(int source);
	void Print_Diameter();
};