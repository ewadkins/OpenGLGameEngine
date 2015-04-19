/*
 * ComplexMatrix.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#include "ComplexMatrix.h"

// Basic constructor
template<typename T>
ComplexMatrix<T>::ComplexMatrix(int rows, int cols) {
	_rows = rows;
	_cols = cols;
	_matrix = new Complex<T>*[_rows];
	for (int i = 0; i < _rows; i++)
		_matrix[i] = new Complex<T> [_cols];
	fill(0);
}

// Square matrix constructor
template<typename T>
ComplexMatrix<T>::ComplexMatrix(int size) {
	_rows = size;
	_cols = size;
	_matrix = new Complex<T>*[_rows];
	for (int i = 0; i < _rows; i++)
		_matrix[i] = new Complex<T> [_cols];
	fill(0);
}

// Constructor that allows matrix casting
template<typename T>
template<typename S>
ComplexMatrix<T>::ComplexMatrix(ComplexMatrix<S> other) {
	_rows = other.rows();
	_cols = other.cols();
	_matrix = new Complex<T>*[_rows];
	for (int i = 0; i < _rows; i++)
		_matrix[i] = new Complex<T> [_cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			set(i, j, other.getMatrix()[i][j]);
		}
}

// Returns the sum of this matrix with another
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::add(ComplexMatrix other) {
	if (_rows != other._rows || _cols != other._cols)
		throw std::runtime_error("Matrix dimensions do not match");
	ComplexMatrix<T> result = ComplexMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, get(i, j) + other.get(i, j));
	return result;
}

// Returns this matrix multiplied by a scalar
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::scale(T k) {
	ComplexMatrix<T> result = ComplexMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, get(i, j) * k);
	return result;
}

// Returns the transpose of this matrix
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::transpose() {
	ComplexMatrix<T> result = ComplexMatrix<T>(_cols, _rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			result.set(j, i, get(i, j));
		}
	return result;
}

// Returns the product of this matrix with another
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::mul(ComplexMatrix other) {
	if (_cols != other._rows)
		throw std::runtime_error("Matrix dimensions do not match");
	ComplexMatrix<T> result = ComplexMatrix<T>(_rows, other.cols());
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < other.cols(); j++) {
			Complex<T> sum = Complex<T>(0, 1);
			for (int k = 0; k < _cols; k++)
				sum += get(i, k) * other.get(k, j);
			result.set(i, j, sum);
		}
	return result;
}

// Returns the reduced row echelon form of this matrix
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::rref() {
	ComplexMatrix<T> result = clone();
	int x = 0;
	int y = 0;
	while (x < _rows) {
		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) == 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					Complex<T> temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
				}
			} else {
				y++;
				continue;
			}
			/*std::cout << "Row exchange (Row " << x + 1 << " <-> Row "
			 << rowToExchange + 1 << ")" << std::endl;
			 result.print();*/
		}
		if (result.get(x, y) != 1 && result.get(x, y) != 0) {
			Complex<T> k = result.get(x, y);
			for (int j = 0; j < _cols; j++)
				result.set(x, j, result.get(x, j) / k);
			/*std::cout << "Row division (Row " << x + 1 << " / " << k.toString() << ")"
			 << std::endl;
			 result.print();*/
		}
		for (int i = 0; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				Complex<T> n = -(result.get(i, y) / result.get(x, y));
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
ComplexMatrix<T> ComplexMatrix<T>::upperTriangular() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	ComplexMatrix<T> result = clone();
	int x = 0;
	int y = 0;
	while (x < _rows) {
		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					Complex<T> temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
				}
			} else {
				y++;
				continue;
			}
		}
		for (int i = x; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				Complex<T> n = -(result.get(i, y) / result.get(x, y));
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
Complex<T> ComplexMatrix<T>::determinant() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	ComplexMatrix<T> result = clone();
	int rowChanges = 0;
	int x = 0;
	int y = 0;
	while (x < _rows) {
		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					Complex<T> temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
					rowChanges++;
				}
			} else {
				y++;
				continue;
			}
		}
		for (int i = x; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				Complex<T> n = -(result.get(i, y) / result.get(x, y));
				for (int j = 0; j < _cols; j++) {
					result.set(i, j, result.get(i, j) + n * result.get(x, j));
				}
			}
		}
		x++;
		y++;
	}
	Complex<T> determinant = 1;
	for (int n = 0; n < _rows; n++)
		determinant *= result.get(n, n);
	if (rowChanges % 2 == 1)
		determinant *= -1;
	return determinant;
}

// Returns the inverse of this matrix
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::inverse() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	if (determinant() == 0)
		throw std::runtime_error("Matrix is singular, inverse doesn't exist");
	ComplexMatrix<T> m = ComplexMatrix<T>(_rows, 2 * _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			m.set(i, j, get(i, j));
	for (int n = 0; n < _rows; n++)
		m.set(n, n + _cols, 1);
	m = m.rref();
	ComplexMatrix<T> result = ComplexMatrix<T>(_rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, m.get(i, j + _cols));
	return result;
}

// Returns the number of rows in this matrix
template<typename T>
int ComplexMatrix<T>::rows() {
	return _rows;
}

// Returns the number of columns in this matrix
template<typename T>
int ComplexMatrix<T>::cols() {
	return _cols;
}

// Fills this entire matrix with a given value
template<typename T>
void ComplexMatrix<T>::fill(T value) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			set(i, j, value);
}

// sets the values of the matrix given a two dimensional array of values
template<typename T>
void ComplexMatrix<T>::setMatrix(T** matrix) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			set(i, j, Complex<T>(matrix[i][j]));
		}
}

// sets the values of this matrix given a vector of values
template<typename T>
void ComplexMatrix<T>::setVector(std::vector<T> values) {
	if (values.size() != _rows * _cols)
		throw std::runtime_error("Incorrect number of values to fill matrix");
	for (int i = 0; i < _rows * _cols; i++) {
		set(i / _cols, i % _cols, Complex<T>(values[i]));
	}
}

// sets the specified element of this matrix to a given value
template<typename T>
void ComplexMatrix<T>::set(int i, int j, T value) {
	_matrix[i][j] = value;
}

// sets the values of the matrix given a two dimensional array of values
template<typename T>
void ComplexMatrix<T>::setMatrix(Complex<T>** matrix) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			set(i, j, matrix[i][j]);
		}
}

// sets the values of this matrix given a vector of values
template<typename T>
void ComplexMatrix<T>::setVector(std::vector<Complex<T> > values) {
	if (values.size() != _rows * _cols)
		throw std::runtime_error("Incorrect number of values to fill matrix");
	for (int i = 0; i < _rows * _cols; i++) {
		set(i / _cols, i % _cols, values[i]);
	}
}

// sets the specified element of this matrix to a given value
template<typename T>
void ComplexMatrix<T>::set(int i, int j, Complex<T> value) {
	_matrix[i][j] = value;
}

// Returns the values of this matrix in a two dimensional array
template<typename T>
Complex<T>** ComplexMatrix<T>::getMatrix() {
	return _matrix;
}

// Returns the values of this matrix in a vector
template<typename T>
std::vector<Complex<T> > ComplexMatrix<T>::getVector() {
	std::vector<Complex<T> > values;
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values.push_back(_matrix[i][j]);
	return values;
}

// Returns the values of this matrix in a one dimensional array
template<typename T>
Complex<T>* ComplexMatrix<T>::getArray() {
	Complex<T>* values = new Complex<T> [_rows * _cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values[i * _cols + j] = _matrix[i][j];
	return values;
}

// Returns the value of the specified element of this matrix
template<typename T>
Complex<T> ComplexMatrix<T>::get(int i, int j) {
	return _matrix[i][j];
}

// Returns the values of this matrix in a two dimensional array
template<typename T>
T** ComplexMatrix<T>::getMatrixConstants() {
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
std::vector<T> ComplexMatrix<T>::getVectorConstants() {
	std::vector<T> values;
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values.push_back(_matrix[i][j].value());
	return values;
}

// Returns the values of this matrix in a one dimensional array
template<typename T>
T* ComplexMatrix<T>::getArrayConstants() {
	T* values = new T[_rows * _cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values[i * _cols + j] = _matrix[i][j].value();
	return values;
}

// Returns the value of the specified element of this matrix
template<typename T>
T ComplexMatrix<T>::getConstant(int i, int j) {
	return _matrix[i][j].value();
}

// Returns a copy of this object (another matrix with the same values)
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::clone() {
	ComplexMatrix<T> result = ComplexMatrix<T>(_rows, _cols);
	result.setMatrix(_matrix);
	return result;
}

// Returns a vector of strings representing this matrix
template<typename T>
std::vector<std::string> ComplexMatrix<T>::toStringVector() {
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
void ComplexMatrix<T>::print() {
	std::vector<std::string> strings = toStringVector();
	for (int i = 0; i < strings.size(); i++)
		std::cout << strings[i] << std::endl;
	std::cout << std::endl;
}

// Allows for the addition of two matrices with the + operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator+(ComplexMatrix<T> rhs) {
	return add(rhs);
}

// Allows for the subtraction of two matrices with the - operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator-(ComplexMatrix<T> rhs) {
	return add(rhs.scale(-1));
}

// Allows for the negation of a matrix with the - operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator-() {
	return scale(-1);
}

// Allows for the scaling of a matrix with the * operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator*(T rhs) {
	return scale(rhs);
}

// Allows for the multiplication of two matrices with the * operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator*(ComplexMatrix<T> rhs) {
	return mul(rhs);
}

// Allows for the division of two matrices with the / operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator/(ComplexMatrix<T> rhs) {
	return mul(rhs.inverse());
}

// Allows for the scaling of a matrix with the / operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator/(T rhs) {
	return scale(1 / rhs);
}

// Allows for the exponentiation of two matrices with the ^ operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator^(int rhs) {
	ComplexMatrix<T> result = clone();
	for (int i = 0; i < rhs; i++)
		result = result.mul(result);
	return result;
}

// Allows for the left multiplication of two matrices with the << operator
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::operator<<(ComplexMatrix<T> rhs) {
	return rhs.mul(clone());
}

// Returns a matrix of the specified size filled with zeros
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::zeros(int m, int n) {
	ComplexMatrix<T> result = ComplexMatrix<T>(m, n);
	return result;
}

// Returns a matrix of the specified size filled with ones
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::ones(int m, int n) {
	ComplexMatrix<T> result = ComplexMatrix<T>(m, n);
	result.fill(1);
	return result;
}

// Returns the identity matrix of the specified size
template<typename T>
ComplexMatrix<T> ComplexMatrix<T>::identity(int size) {
	ComplexMatrix<T> result = ComplexMatrix<T>(size, size);
	for (int n = 0; n < size; n++)
		result.set(n, n, 1);
	return result;
}

// Explicit instantiation of template classes
template class ComplexMatrix<float> ;
template class ComplexMatrix<double> ;
template class ComplexMatrix<long double> ;
