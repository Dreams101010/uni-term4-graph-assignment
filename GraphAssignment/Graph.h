#ifndef H_Graph
#define H_Graph

#include "Matrix.h"
#include "BFSTree.h"

class Graph
{
	std::shared_ptr<Matrix<int>> m;
public:
	Graph(int nodeCount);
	Graph(std::shared_ptr<Matrix<int>> adjMatrix);
	bool IsValidIndex(int index);
	void AddEdge(int node1, int node2);
	void RemoveEdge(int node1, int node2);
	bool IsSingleComponent();
	BFSTree BFS(int source);
	void Print_Diameter();
};

#endif // !H_Graph