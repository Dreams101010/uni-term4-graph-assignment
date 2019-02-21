#pragma once

#include "pch.h"
#include "BFSTree.h"
#include <vector>
#include <iostream>
#include "GraphNode.h"

BFSTree::BFSTree(int source, std::vector<GraphNode> nodes, int pathMaxLength, std::vector<int> chainStarts)
{
	_source = source;
	_nodes = nodes;
	_pathMaxLength = pathMaxLength;
	_chainStarts = chainStarts;
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

void BFSTree::PrintPathToSource(int index)
{
	std::vector<int> path;
	int curIndex = index;
	while (curIndex != _source)
	{
		path.push_back(curIndex);
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
		path.push_back(_source);
		for (std::vector<int>::iterator it = path.begin(); it != path.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "There is no path between " << index << " and " << _source << "." << std::endl;
	}
}

void BFSTree::PrintMaxLengthChains()
{
	for (int i : _chainStarts)
	{
		PrintPathToSource(i);
	}
}