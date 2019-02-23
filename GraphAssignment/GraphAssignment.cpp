// GraphAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Graph.h"
#include <iostream>
#include <exception>
#include <stdexcept>
#include <memory>

std::shared_ptr<Matrix<int>> ReadMatrix()
{
	int nodeCount = 0;
	std::cout << "Enter number of nodes:";
	std::cin >> nodeCount;
	if (nodeCount <= 0)
	{
		throw std::invalid_argument("Cannot initialize matrix with dimension = 0");
	}
	auto matrix = std::shared_ptr<Matrix<int>>(new Matrix<int>(nodeCount));
	std::cout << "Enter matrix:" << std::endl;
	for (int i = 0; i < matrix->GetDimension(); i++)
	{
		for (int j = 0; j < matrix->GetDimension(); j++)
		{
			int val = 0;
			std::cin >> val;
			matrix->Set(i, j, val);
		}
	}
	return matrix;
}

int main()
{
	try
	{
		auto adjMatrix = ReadMatrix();
		auto g = Graph(adjMatrix);
		g.Print_Diameter();
	}
	catch (std::exception e)
	{
		std::cout << "Exception occured: " << e.what() << std::endl;
	}
}