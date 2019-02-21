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

// TODO: Rewrite to check by color
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
	std::vector<GraphNode> g;
	for (int i = 0; i < m->GetDimension(); i++)
	{
		GraphNode node;
		node.index = i;
		g.push_back(node);
	}
	g[source].color = GRAY;
	g[source].distanceFromRoot = 0;
	Queue<int> queue;
	queue.Enqueue(source);
	while (!queue.IsEmpty())
	{
		int cur = queue.Dequeue();
		for (int i = 0; i < m->GetDimension(); i++)
		{
			if (m->Get(cur, i) == 1) // if i-th node adjacent to cur node
			{
				// Safe to call value because every node that gets put into queue has its distance initialized
				int curDistanceFromRoot = g[cur].distanceFromRoot.value(); 
				if (g[i].color == WHITE)
				{
					g[i].color = GRAY;
					g[i].distanceFromRoot = curDistanceFromRoot + 1;
					if (g[i].distanceFromRoot > curMax)
					{
						curMax = curDistanceFromRoot + 1;
						maxChainEnds.clear();
						maxChainEnds.push_back(i);
					}
					else if (g[i].distanceFromRoot == curMax)
					{
						maxChainEnds.push_back(i);
					}
					g[i].parentIndex = cur;
					queue.Enqueue(i);
				}
			}
		}
		g[cur].color = BLACK;
	}
	BFSTree result(source, g, curMax, maxChainEnds);
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