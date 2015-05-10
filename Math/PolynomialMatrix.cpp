/*
 * PolynomialMatrix.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: ericwadkins
 */

#include "PolynomialMatrix.h"

// Basic constructor
template<typename T>
PolynomialMatrix<T>::PolynomialMatrix(int rows, int cols) {
	_rows = rows;
	_cols = cols;
	_matrix = new Polynomial<T>*[_rows];
	for (int i = 0; i < _rows; i++) {
		_matrix[i] = new Polynomial<T>[_cols];
		for (int j = 0; j < _cols; j++)
			_matrix[i][j] = 0;
	}
}

// Square matrix constructor
template<typename T>
PolynomialMatrix<T>::PolynomialMatrix(int size) {
	_rows = size;
	_cols = size;
	_matrix = new Polynomial<T>*[_rows];
	for (int i = 0; i < _rows; i++) {
		_matrix[i] = new Polynomial<T>[_cols];
		for (int j = 0; j < _cols; j++)
			_matrix[i][j] = 0;
	}
}

// Constructor that allows matrix casting
template<typename T>
template<typename S>
PolynomialMatrix<T>::PolynomialMatrix(PolynomialMatrix<S> other) {
	_rows = other.rows();
	_cols = other.cols();
	_matrix = new Polynomial<T>*[_rows];
	for (int i = 0; i < _rows; i++)
		_matrix[i] = new Polynomial<T> [_cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			_matrix[i][j] = other.get(i, j);
		}
}

// Returns the sum of this matrix with another
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::add(PolynomialMatrix other) {
	if (_rows != other._rows || _cols != other._cols)
		throw std::runtime_error("Matrix dimensions do not match");
	PolynomialMatrix<T> result = PolynomialMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, _matrix[i][j] + other.get(i, j));
	return result;
}

// Returns this matrix multiplied by a scalar
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::scale(T k) {
	PolynomialMatrix<T> result = PolynomialMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, _matrix[i][j] * k);
	return result;
}

// Returns the transpose of this matrix
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::transpose() {
	PolynomialMatrix<T> result = PolynomialMatrix<T>(_cols, _rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			result.set(j, i, _matrix[i][j]);
		}
	return result;
}

// Returns the product of this matrix with another
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::mul(PolynomialMatrix other) {
	if (_cols != other._rows)
		throw std::runtime_error("Matrix dimensions do not match");
	PolynomialMatrix<T> result = PolynomialMatrix<T>(_rows, other.cols());
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < other.cols(); j++) {
			Polynomial<T> sum = Polynomial<T>(0, 1);
			for (int k = 0; k < _cols; k++)
				sum += _matrix[i][k] * other.get(k, j);
			result.set(i, j, sum);
		}
	return result;
}

// Returns the reduced row echelon form of this matrix
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::rref() {
	PolynomialMatrix<T> result = *this;
	int x = 0;
	int y = 0;
	while (x < _rows && y < _cols) {

		// FIXME Decide whether to always round numbers
		// Rounds numbers with very small errors
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (result.get(i, j) != 0) {
					Polynomial<T> temp = result.get(i, j);
					temp.round();
					result.set(i, j, temp);
				}

		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					Polynomial<T> temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
				}
			} else {
				y++;
				if (x == _rows -1)
					break;
				continue;
			}
			/*std::cout << "Row exchange (Row " << x + 1 << " <-> Row "
			 << rowToExchange + 1 << ")" << std::endl;
			 result.print();*/
		}
		if (result.get(x, y) != 1 && result.get(x, y) != 0) {
			Polynomial<T> k = result.get(x, y);
			for (int j = 0; j < _cols; j++)
				result.set(x, j, result.get(x, j) / k);
			/*std::cout << "Row division (Row " << x + 1 << " / " << k.toString() << ")"
			 << std::endl;
			 result.print();*/
		}
		for (int i = 0; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				Polynomial<T> n = -(result.get(i, y) / result.get(x, y));
				for (int j = 0; j < _cols; j++) {
					result.set(i, j, result.get(i, j) + result.get(x, j) * n);
				}
			}
		}
		x++;
		y++;
		/*std::cout << "Row elimination" << std::endl;
		 result.print();*/
	}
	return result;
}

// Returns the upper triangular factorization of this matrix
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::upperTriangular() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	PolynomialMatrix<T> result = *this;
	int x = 0;
	int y = 0;
	while (x < _rows && y < _cols) {

		// FIXME Decide whether to always round numbers
		// Rounds numbers with very small errors
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (result.get(i, j) != 0) {
					Polynomial<T> temp = result.get(i, j);
					temp.round();
					result.set(i, j, temp);
				}

		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					Polynomial<T> temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
				}
			} else {
				y++;
				if (x == _rows -1)
					break;
				continue;
			}
		}
		for (int i = x; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				Polynomial<T> n = -(result.get(i, y) / result.get(x, y));
				for (int j = 0; j < _cols; j++) {
					result.set(i, j, result.get(i, j) + n * result.get(x, j));
				}
			}
		}
		x++;
		y++;
	}
	return result;
}

// Returns the determinant of this matrix
template<typename T>
Polynomial<T> PolynomialMatrix<T>::determinant() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	PolynomialMatrix<T> result = *this;
	int rowChanges = 0;
	int x = 0;
	int y = 0;
	while (x < _rows && y < _cols) {

		// FIXME Decide whether to always round numbers
		// Rounds numbers with very small errors
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (result.get(i, j) != 0) {
					Polynomial<T> temp = result.get(i, j);
					temp.round();
					result.set(i, j, temp);
				}

		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					Polynomial<T> temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
					rowChanges++;
				}
			} else {
				y++;
				if (x == _rows -1)
					break;
				continue;
			}
		}
		for (int i = x; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				Polynomial<T> n = -(result.get(i, y) / result.get(x, y));
				for (int j = 0; j < _cols; j++) {
					result.set(i, j, result.get(i, j) + n * result.get(x, j));
				}
			}
		}
		x++;
		y++;
	}
	Polynomial<T> determinant = 1;
	for (int n = 0; n < _rows; n++)
		determinant *= result.get(n, n);
	if (rowChanges % 2 == 1)
		determinant *= -1;
	determinant.round();
	return determinant;
}

// Returns the inverse of this matrix
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::inverse() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	if (determinant() == 0)
		throw std::runtime_error("Matrix is singular, inverse doesn't exist");
	PolynomialMatrix<T> m = PolynomialMatrix<T>(_rows, 2 * _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			m.set(i, j, get(i, j));
	for (int n = 0; n < _rows; n++)
		m.set(n, n + _cols, 1);
	m = m.rref();
	PolynomialMatrix<T> result = PolynomialMatrix<T>(_rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, m.get(i, j + _cols));
	return result;
}

// Returns a vector of vectors representing the special solutions of this matrix
template<typename T>
std::vector<std::vector<Polynomial<T> > > PolynomialMatrix<T>::specialSolutions() {
	std::vector<std::vector<Polynomial<T> > > result;
	PolynomialMatrix<T> r = rref();
	std::vector<int> pivotColumns;
	for (int i = 0; i < r._rows; i++) {
		std::vector<Polynomial<T> > pivotColumn;
		for (int n = 0; n < r._rows; n++) {
			if (n == i)
				pivotColumn.push_back(Polynomial<T>(1));
			else
				pivotColumn.push_back(Polynomial<T>());
		}
		bool foundPivotColumn = false;
		for (int j = 0; j < r._cols; j++) {
			bool equal = true;
			std::vector<Polynomial<T> > column = r.getColumn(j);
			if (column.size() != pivotColumn.size())
				equal = false;
			for (int n = 0; n < column.size(); n++)
				if (column[n] != pivotColumn[n])
					equal = false;
			if (equal) {
				pivotColumns.push_back(j);
				foundPivotColumn = true;
			}
		}
		if (!foundPivotColumn)
			break;
	}
	for (int j = 0; j < r._cols; j++) {
		bool isPivotColumn = false;
		for (int n = 0; n < pivotColumns.size(); n++)
			if (j == pivotColumns[n])
				isPivotColumn = true;
		if (isPivotColumn)
			continue;

		std::vector<Polynomial<T> > specialSolution;
		for (int n = 0; n < r._cols; n++)
			specialSolution.push_back(Polynomial<T>());
		specialSolution[j] = 1;
		for (int i = 0; i < r._rows; i++) {
			for (int n = 0; n < r._cols; n++)
				if (n != j)
					if (r._matrix[i][n] != 0) {
						specialSolution[n] = -r._matrix[i][j];
						break;
					}
		}
		result.push_back(specialSolution);
	}
	return result;
}

// Returns the number of rows in this matrix
template<typename T>
int PolynomialMatrix<T>::rows() {
	return _rows;
}

// Returns the number of columns in this matrix
template<typename T>
int PolynomialMatrix<T>::cols() {
	return _cols;
}

// Returns a vector representing the specified row of this matrix
template<typename T>
std::vector<Polynomial<T> > PolynomialMatrix<T>::getRow(int m) {
	std::vector<Polynomial<T> > result;
	for (int i = 0; i < _cols; i++)
		result.push_back(_matrix[m][i]);
	return result;
}

// Returns a vector representing the specified column of this matrix
template<typename T>
std::vector<Polynomial<T> > PolynomialMatrix<T>::getColumn(int n) {
	std::vector<Polynomial<T> > result;
	for (int i = 0; i < _rows; i++)
		result.push_back(_matrix[i][n]);
	return result;
}

// Fills this entire matrix with a given value
template<typename T>
void PolynomialMatrix<T>::fill(T value) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			_matrix[i][j] = value;
}

// sets the values of the matrix given a two dimensional array of values
template<typename T>
void PolynomialMatrix<T>::setMatrix(T** matrix) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			_matrix[i][j] = Polynomial<T>(matrix[i][j]);
		}
}

// sets the values of this matrix given a vector of values
template<typename T>
void PolynomialMatrix<T>::setVector(std::vector<T> values) {
	if (values.size() != _rows * _cols)
		throw std::runtime_error("Incorrect number of values to fill matrix");
	for (int i = 0; i < _rows * _cols; i++) {
		_matrix[i / _cols][i % _cols] = Polynomial<T>(values[i]);
	}
}

// sets the specified element of this matrix to a given value
template<typename T>
void PolynomialMatrix<T>::set(int i, int j, T value) {
	_matrix[i][j] = value;
}

// sets the values of the matrix given a two dimensional array of values
template<typename T>
void PolynomialMatrix<T>::setMatrix(Polynomial<T>** matrix) {
	_matrix = matrix;
}

// sets the values of this matrix given a vector of values
template<typename T>
void PolynomialMatrix<T>::setVector(std::vector<Polynomial<T> > values) {
	if (values.size() != _rows * _cols)
		throw std::runtime_error("Incorrect number of values to fill matrix");
	for (int i = 0; i < _rows * _cols; i++)
		_matrix[i / _cols][i % _cols] = values[i];
}

// sets the specified element of this matrix to a given value
template<typename T>
void PolynomialMatrix<T>::set(int i, int j, Polynomial<T> value) {
	_matrix[i][j] = value;
}

// Returns the values of this matrix in a two dimensional array
template<typename T>
Polynomial<T>** PolynomialMatrix<T>::getMatrix() {
	return _matrix;
}

// Returns the values of this matrix in a vector
template<typename T>
std::vector<Polynomial<T> > PolynomialMatrix<T>::getVector() {
	std::vector<Polynomial<T> > values;
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values.push_back(_matrix[i][j]);
	return values;
}

// Returns the values of this matrix in a one dimensional array
template<typename T>
Polynomial<T>* PolynomialMatrix<T>::getArray() {
	Polynomial<T>* values = new Polynomial<T> [_rows * _cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values[i * _cols + j] = _matrix[i][j];
	return values;
}

// Returns the value of the specified element of this matrix
template<typename T>
Polynomial<T> PolynomialMatrix<T>::get(int i, int j) {
	return _matrix[i][j];
}

// Returns the values of this matrix in a two dimensional array
template<typename T>
T** PolynomialMatrix<T>::getMatrixConstants() {
	T** matrix = new T*[_rows];
	for (int i = 0; i < _rows; i++)
		matrix[i] = new T[_cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; i < _cols; j++)
			matrix[i][j] = _matrix[i][j].value();
	return matrix;
}

// Returns the values of this matrix in a vector
template<typename T>
std::vector<T> PolynomialMatrix<T>::getVectorConstants() {
	std::vector<T> values;
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values.push_back(_matrix[i][j].value());
	return values;
}

// Returns the values of this matrix in a one dimensional array
template<typename T>
T* PolynomialMatrix<T>::getArrayConstants() {
	T* values = new T[_rows * _cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values[i * _cols + j] = _matrix[i][j].value();
	return values;
}

// Returns the value of the specified element of this matrix
template<typename T>
T PolynomialMatrix<T>::getConstant(int i, int j) {
	return _matrix[i][j].value();
}

// Returns a vector of strings representing this matrix
template<typename T>
std::vector<std::string> PolynomialMatrix<T>::toStringVector() {
	std::vector<std::string> strings;
	std::string** arr = new std::string*[_rows];
	for (int i = 0; i < _rows; i++) {
		arr[i] = new std::string[_cols];
		for (int j = 0; j < _cols; j++) {
			arr[i][j] = _matrix[i][j].toString();
		}
	}
	for (int j = 0; j < _cols; j++) {
		int maxLength = 0;
		for (int i = 0; i < _rows; i++)
			if (arr[i][j].length() > maxLength)
				maxLength = arr[i][j].length();
		for (int i = 0; i < _rows; i++)
			while (arr[i][j].length() < maxLength)
				arr[i][j] = " " + arr[i][j];
	}
	for (int i = 0; i < _rows; i++) {
		std::string str = "";
		for (int j = 0; j < _cols; j++) {
			if (j == 0)
				str += "[";
			str += " " + arr[i][j] + " ";
			if (j == _cols - 1)
				str += "]";
		}
		strings.push_back(str);
	}
	return strings;
}

// Prints the string representation of this matrix to the standard output stream
template<typename T>
void PolynomialMatrix<T>::print() {
	std::vector<std::string> strings = toStringVector();
	for (int i = 0; i < strings.size(); i++)
		std::cout << strings[i] << std::endl;
	std::cout << std::endl;
}

// Allows for the addition of two matrices with the + operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator+(PolynomialMatrix<T> rhs) {
	return add(rhs);
}

// Allows for the subtraction of two matrices with the - operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator-(PolynomialMatrix<T> rhs) {
	return add(rhs.scale(-1));
}

// Allows for the negation of a matrix with the - operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator-() {
	return scale(-1);
}

// Allows for the scaling of a matrix with the * operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator*(T rhs) {
	return scale(rhs);
}

// Allows for the multiplication of two matrices with the * operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator*(PolynomialMatrix<T> rhs) {
	return mul(rhs);
}

// Allows for the division of two matrices with the / operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator/(PolynomialMatrix<T> rhs) {
	return mul(rhs.inverse());
}

// Allows for the scaling of a matrix with the / operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator/(T rhs) {
	return scale(1 / rhs);
}

// Allows for the exponentiation of two matrices with the ^ operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator^(int rhs) {
	PolynomialMatrix<T> result = *this;
	for (int i = 0; i < rhs; i++)
		result = result.mul(result);
	return result;
}

// Allows for the left multiplication of two matrices with the << operator
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::operator<<(PolynomialMatrix<T> rhs) {
	return rhs.mul(*this);
}

// Returns a matrix of the specified size filled with zeros
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::zeros(int m, int n) {
	PolynomialMatrix<T> result = PolynomialMatrix<T>(m, n);
	return result;
}

// Returns a matrix of the specified size filled with ones
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::ones(int m, int n) {
	PolynomialMatrix<T> result = PolynomialMatrix<T>(m, n);
	result.fill(1);
	return result;
}

// Returns the identity matrix of the specified size
template<typename T>
PolynomialMatrix<T> PolynomialMatrix<T>::identity(int size) {
	PolynomialMatrix<T> result = PolynomialMatrix<T>(size, size);
	for (int n = 0; n < size; n++)
		result.set(n, n, 1);
	return result;
}

// Explicit instantiation of template classes
template class PolynomialMatrix<float> ;
template class PolynomialMatrix<double> ;
template class PolynomialMatrix<long double> ;
template PolynomialMatrix<float>::PolynomialMatrix(PolynomialMatrix<float>);
template PolynomialMatrix<float>::PolynomialMatrix(PolynomialMatrix<double>);
template PolynomialMatrix<float>::PolynomialMatrix(PolynomialMatrix<long double>);
template PolynomialMatrix<double>::PolynomialMatrix(PolynomialMatrix<float>);
template PolynomialMatrix<double>::PolynomialMatrix(PolynomialMatrix<double>);
template PolynomialMatrix<double>::PolynomialMatrix(PolynomialMatrix<long double>);
template PolynomialMatrix<long double>::PolynomialMatrix(PolynomialMatrix<float>);
template PolynomialMatrix<long double>::PolynomialMatrix(PolynomialMatrix<double>);
template PolynomialMatrix<long double>::PolynomialMatrix(PolynomialMatrix<long double>);
