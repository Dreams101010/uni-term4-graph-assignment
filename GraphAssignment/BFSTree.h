#ifndef H_BFSTree
#define H_BFSTree

#include <vector>
#include <memory>
#include "GraphNode.h"

class BFSTree
{
	int _source;
	std::vector<GraphNode> _nodes;
	int _pathMaxLength;
	std::vector<int> _chainStarts;
	std::vector<std::vector<int>> _lookup;
	static const bool PRINT_DUPLICATES = false;
public:
	BFSTree(int source, std::vector<GraphNode> nodes, 
		int pathMaxLength, std::vector<int> chainStarts, std::vector<std::vector<int>> lookup);
	int GetMaxChainLength();
	bool HasPathToSource(int index);
	void PrintPathsToSource(int index);
	void PrintMaxLengthChains();
};

#endif // !H_BFSTree