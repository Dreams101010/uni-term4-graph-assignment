// GraphAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Graph.h"

int main()
{
	Graph g(5);
	g.AddEdge(1, 2);
	g.AddEdge(0, 1);
	g.AddEdge(2, 3);
	g.AddEdge(2, 4);
	g.Print_Diameter();
}