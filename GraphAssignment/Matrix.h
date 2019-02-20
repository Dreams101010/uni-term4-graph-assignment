#pragma once

template <class T>
class Matrix
{
	T** _matrix;
	int _dim;

private:
	inline bool CheckIndex(int ind);
public:
	Matrix(int dim);
	~Matrix();
	int Get(int row, int column);
	void Set(int row, int column, int value);
	int GetDimension();
};