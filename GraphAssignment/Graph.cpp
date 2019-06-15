#pragma once

#include "pch.h"
#include "Graph.h"
#include "Queue.h"
#include <iostream>

Graph::Graph(int nodeCount)
{
	if (nodeCount <= 0)
	{
		throw std::invalid_argument("Cannot create graph with <= 0 nodes.");
	}
	m = std::shared_ptr<Matrix<int>>(new Matrix<int>(nodeCount));
}

Graph::Graph(std::shared_ptr<Matrix<int>> adjMatrix)
{
	m = std::shared_ptr<Matrix<int>>(new Matrix<int>(adjMatrix->GetDimension()));
	for (int i = 0; i < adjMatrix->GetDimension(); i++)
	{
		for (int j = 0; j < adjMatrix->GetDimension(); j++)
		{
			int val = adjMatrix->Get(i, j);
			if ((val != 0 && val != 1) || (val != adjMatrix->Get(j, i)))
			{
				throw std::invalid_argument("Invalid value in adjacency matrix.");
			}
			m->Set(i, j, val);
		}
	}
}

bool Graph::IsValidIndex(int index)
{
	if (index >= m->GetDimension() || index < 0)
	{
		return false;
	}
	return true;
}

void Graph::AddEdge(int node1, int node2)
{
	m->Set(node1, node2, 1);
	m->Set(node2, node1, 1);
}

void Graph::RemoveEdge(int node1, int node2)
{
	m->Set(node1, node2, 0);
	m->Set(node2, node1, 0);
}

bool Graph::IsSingleComponent()
{
	auto bfsTree = BFS(0);
	for (int i = 0; i < m->GetDimension(); i++)
	{
		if (!bfsTree.HasPathToSource(i))
		{
			return false;
		}
	}
	return true;
}

BFSTree Graph::BFS(int source)
{
	if (!IsValidIndex(source))
	{
		throw std::invalid_argument("Node index was out of bounds.");
	}
	std::vector<int> maxChainEnds;
	int curMax = 0;
	std::vector<GraphNode> nodes;
	for (int i = 0; i < m->GetDimension(); i++)
	{
		GraphNode node;
		node.index = i;
		nodes.push_back(node);
	}
	nodes[source].color = GRAY;
	nodes[source].distanceFromRoot = 0;
	Queue<int> queue;
	queue.Enqueue(source);
	while (!queue.IsEmpty())
	{
		int cur = queue.Dequeue();
		for (int i = 0; i < m->GetDimension(); i++)
		{
			if (m->Get(cur, i) == 1) // if i-th node adjacent to cur node
			{
				// Safe to call value() because every node that gets put into queue has its distance initialized
				int curDistanceFromRoot = nodes[cur].distanceFromRoot.value();
				if (nodes[i].color == WHITE)
				{
					nodes[i].color = GRAY;
					nodes[i].distanceFromRoot = curDistanceFromRoot + 1;
					if (nodes[i].distanceFromRoot > curMax)
					{
						curMax = curDistanceFromRoot + 1;
						maxChainEnds.clear();
						maxChainEnds.push_back(i);
					}
					else if (nodes[i].distanceFromRoot == curMax)
					{
						maxChainEnds.push_back(i);
					}
					nodes[i].parentIndex = cur;
					queue.Enqueue(i);
				}
			}
		}
		nodes[cur].color = BLACK;
	}
	// lookup table for path traversal
	std::vector<std::vector<int>> lookup;
	for (unsigned int i = 0; i < m->GetDimension(); i++)
	{
		std::vector<int> v;
		for (unsigned int j = 0; j < m->GetDimension(); j++)
		{
			if (m->Get(i, j) == 1) // if i-th and j-th nodes are adjacent
			{
				if (nodes[i].distanceFromRoot.value() - 1 == nodes[j].distanceFromRoot.value())
				{
					v.push_back(j);
				}
			}
		}
		lookup.push_back(v);
	}
	BFSTree result(source, nodes, curMax, maxChainEnds, lookup);
	return result;
}

void Graph::Print_Diameter()
{
	if (!IsSingleComponent())
	{
		std::cout << "This graph has no edges or has multiple components. Can't find the diameter." << std::endl;
		return;
	}
	if (m->GetDimension() == 1) // corner case
	{
		std::cout << "This graph has only one vertex. Diameter doesn't exist." << std::endl;
		return;
	}
	int curMax = 0;
	std::vector<BFSTree> maximumTrees;
	for (int i = 0; i < m->GetDimension(); i++)
	{
		auto tree = BFS(i);
		if (tree.GetMaxChainLength() > curMax)
		{
			curMax = tree.GetMaxChainLength();
			maximumTrees.clear();
			maximumTrees.push_back(tree);
		}
		else if (tree.GetMaxChainLength() == curMax)
		{
			maximumTrees.push_back(tree);
		}
	}
	std::cout << "Diameter chain length: " << curMax << std::endl;
	std::cout << "Chains:" << std::endl;
	for (auto i : maximumTrees)
	{
		i.PrintMaxLengthChains();
	}
}