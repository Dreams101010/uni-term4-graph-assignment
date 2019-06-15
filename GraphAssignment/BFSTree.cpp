#pragma once

#include "pch.h"
#include "BFSTree.h"
#include <vector>
#include <iostream>
#include "GraphNode.h"

BFSTree::BFSTree(int source, std::vector<GraphNode> nodes, 
	int pathMaxLength, std::vector<int> chainStarts, std::vector<std::vector<int>> lookup)
{
	_source = source;
	_nodes = nodes;
	_pathMaxLength = pathMaxLength;
	_chainStarts = chainStarts;
	_lookup = lookup;
};

int BFSTree::GetMaxChainLength()
{
	return _pathMaxLength;
}

bool BFSTree::HasPathToSource(int index)
{
	int curIndex = index;
	while (curIndex != _source)
	{
		if (_nodes[curIndex].parentIndex.has_value()) // if node has a parent
		{
			curIndex = _nodes[curIndex].parentIndex.value();
		}
		else
		{
			break;
		}
	}
	if (curIndex == _source)
	{
		return true;
	}
	return false;
}

void BFSTree::PrintPathsToSource(int index)
{
	std::vector<std::vector<int>> stack;
	std::vector<std::vector<int>> retVal;
	std::vector<int> v;
	v.push_back(index);
	stack.push_back(v);
	while (stack.size() > 0)
	{
		std::vector<int> temp = stack.back();
		stack.pop_back();
		if (temp.back() == _source)
		{
			retVal.push_back(temp);
		}
		else
		{
			int lastNodeInPath = temp.back();
			for (int i : _lookup[lastNodeInPath])
			{
				std::vector<int> pushVec = std::vector<int>(temp); // make a copy
				pushVec.push_back(i); // add a new node to the path
				stack.push_back(pushVec);
			}
		}
	}
	for (std::vector<int> i : retVal)
	{
		for (std::vector<int>::iterator it = i.begin(); it != i.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
}

void BFSTree::PrintMaxLengthChains()
{
	for (int i : _chainStarts)
	{
		if ((i < _source) || PRINT_DUPLICATES)
		{
			std::cout << "Start: " << i << " End: " << _source << std::endl;
			PrintPathsToSource(i);
		}
	}
}