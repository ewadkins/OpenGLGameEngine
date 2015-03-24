/*
 * GLMatrix.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ericwadkins
 */

#include "GLMatrix.h"

template<typename T>
GLMatrix<T>::GLMatrix(int rows, int cols) {
	_rows = rows;
	_cols = cols;
	_matrix = new T*[_rows];
	for (int i = 0; i < _rows; i++)
		_matrix[i] = new T[_cols];
}

template<typename T>
template<typename S>
GLMatrix<T>::GLMatrix(GLMatrix<S> rhs) {
	_rows = rhs.rows();
	_cols = rhs.cols();
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			set(i, j, rhs.matrix()[i][j]);
		}
}

template<typename T, size_t len>
size_t length(T (&)[len]) {
	return len;
}

template<typename T>
GLMatrix<T> GLMatrix<T>::add(GLMatrix other) {
	if (_rows != other._rows || _cols != other._cols)
		throw std::invalid_argument("Matrix dimensions do not match");
	GLMatrix<T> result = GLMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, _matrix[i][j] + other.matrix()[i][j]);
	return result;
}

template<typename T>
GLMatrix<T> GLMatrix<T>::scale(T k) {
	GLMatrix<T> result = GLMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, k * _matrix[i][j]);
	return result;
}

template<typename T>
GLMatrix<T> GLMatrix<T>::transpose() {
	GLMatrix<float> result = GLMatrix<float>(_cols, _rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			result.set(j, i, _matrix[i][j]);
		}
	return result;
}

template<typename T>
GLMatrix<T> GLMatrix<T>::mul(GLMatrix other) {
	GLMatrix<float> result = GLMatrix<float>(_rows, other.cols());
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < other.cols(); j++) {
			T sum = 0;
			for (int k = 0; k < _cols; k++)
				sum += _matrix[i][k] * other.matrix()[k][j];
			result.set(i, j, sum);
		}
	return result;
}

template<typename T>
GLMatrix<T> GLMatrix<T>::reducedRowEchelon() {
	GLMatrix<T> result = clone();
	for (int n = 0; n < std::min(_cols, _rows); n++) {
		if (result.matrix()[n][n] == 0) {
			bool rowToExchange = 0;
			for (int i = n; i < _rows; i++)
				if (result.matrix()[i][n] != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					T temp = result.matrix()[n][j];
					result.matrix()[n][j] = result.matrix()[rowToExchange][j];
					result.matrix()[rowToExchange][j] = temp;
				}
			} else
				n++;
		}
		if (result.matrix()[n][n] != 1) {
			for (int j = 0; j < _cols; j++)
				result.matrix()[n][j] /= result.matrix()[n][n];
		}
		for (int i = 0; i < _rows; i++) {
			if (i != n && result.matrix()[i][n] != 0) {
				T x = -(result.matrix()[i][n] / result.matrix()[n][n]);
				for (int j = 0; j < _cols; j++) {
					result.matrix()[i][j] += x * result.matrix()[n][j];
				}
			}
		}
	}
	// Change negative zeros from floating point error to normal zeros
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			if (result.matrix()[i][j] == 0) {
				result.matrix()[i][j] = 0;
			}
	return result;
}

template<typename T>
int GLMatrix<T>::rows() {
	return _rows;
}

template<typename T>
int GLMatrix<T>::cols() {
	return _cols;
}

template<typename T>
void GLMatrix<T>::set(std::vector<T> values) {
	if (values.size() != _rows * _cols)
		throw std::invalid_argument("Matrix dimensions do not match");

	for (int i = 0; i < _rows * _cols; i++) {
		_matrix[i / _cols][i % _cols] = values[i];
	}
}

template<typename T>
void GLMatrix<T>::set(int i, int j, T value) {
	_matrix[i][j] = value;
}

template<typename T>
T** GLMatrix<T>::matrix() {
	return _matrix;
}

template<typename T>
GLMatrix<T> GLMatrix<T>::clone() {
	GLMatrix<T> result = GLMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			result.set(i, j, _matrix[i][j]);
		}
	return result;
}

template<typename T>
void GLMatrix<T>::print() {
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			if (j == 0)
				std::cout << "[ ";
			std::cout << _matrix[i][j] << " ";
			if (j == _cols - 1)
				std::cout << "]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*
 template<typename T>
 template<typename S>
 GLMatrix<T> GLMatrix<T>::operator=(GLMatrix<S> rhs) {
 for(int i = 0; i < _rows; i++)
 for(int j = 0; j < _cols; j++) {
 set(i, j, rhs._matrix[i][j]);
 }
 return this;
 }*/

// Explicit template instantiation
//template class GLMatrix<int> ;
//template class GLMatrix<long> ;
//template class GLMatrix<double> ;
template class GLMatrix<float> ;
//GLMatrix<int> i(1, 1);
//GLMatrix<double> d(1, 1);
//GLMatrix<float> f(1, 1);
//GLMatrix<long> l(1, 1);

