#pragma once

#include <vector>
#include <memory>
#include "GraphNode.h"

class BFSTree
{
	int _source;
	std::vector<std::shared_ptr<GraphNode>> _nodes;
	int _pathMaxLength;
	std::vector<int> _chainStarts;
public:
	BFSTree(int source, std::vector<std::shared_ptr<GraphNode>> nodes, int pathMaxLength, std::vector<int> chainStarts);
	int GetMaxChainLength();
	bool HasPathToSource(int index);
	void PrintPathToSource(int index);
	void PrintMaxLengthChains();
};