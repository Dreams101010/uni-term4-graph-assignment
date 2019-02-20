#pragma once

#include "pch.h"
#include "Matrix.h"
#include <stdexcept>
#include <exception>

template <class T>
inline bool Matrix<T>::CheckIndex(int ind)
{
	if (ind >= _dim || ind < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template <class T>
Matrix<T>::Matrix(int dim)
{
	_dim = dim;
	_matrix = new int*[dim];
	for (int i = 0; i < dim; i++)
	{
		_matrix[i] = new int[dim];
	}
}

template <class T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < _dim; i++)
	{
		delete _matrix[i];
	}
	delete _matrix;
}

template <class T>
int Matrix<T>::Get(int row, int column)
{
	if (CheckIndex(row) && CheckIndex(column))
	{
		return _matrix[row][column];
	}
	else
	{
		throw std::invalid_argument("Index was out of bounds.");
	}
}

template <class T>
void Matrix<T>::Set(int row, int column, int value)
{
	if (CheckIndex(row) && CheckIndex(column))
	{
		_matrix[row][column] = value;
	}
	else
	{
		throw std::invalid_argument("Index was out of bounds.");
	}
}

template <class T>
int Matrix<T>::GetDimension()
{
	return _dim;
}

template class Matrix<int>; // to avoid linker errors