/*
 * Matrix.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ericwadkins
 */

#include "Matrix.h"

// Basic constructor
template<typename T>
Matrix<T>::Matrix(int rows, int cols) {
	_rows = rows;
	_cols = cols;
	_matrix = new T*[_rows];
	for (int i = 0; i < _rows; i++) {
		_matrix[i] = new T[_cols];
		for (int j = 0; j < _cols; j++)
			_matrix[i][j] = 0;
	}
}

// Square matrix constructor
template<typename T>
Matrix<T>::Matrix(int size) {
	_rows = size;
	_cols = size;
	_matrix = new T*[_rows];
	for (int i = 0; i < _rows; i++) {
		_matrix[i] = new T[_cols];
		for (int j = 0; j < _cols; j++)
			_matrix[i][j] = 0;
	}
}

// Constructor that allows matrix casting
template<typename T>
template<typename S>
Matrix<T>::Matrix(Matrix<S> other) {
	_rows = other.rows();
	_cols = other.cols();
	_matrix = new T*[_rows];
	for (int i = 0; i < _rows; i++)
		_matrix[i] = new T[_cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			_matrix[i][j] = other.get(i, j);
		}
}

// Returns the sum of this matrix with another
template<typename T>
Matrix<T> Matrix<T>::add(Matrix other) {
	if (_rows != other._rows || _cols != other._cols)
		throw std::runtime_error("Matrix dimensions do not match");
	Matrix<T> result = Matrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, _matrix[i][j] + other.get(i, j));
	return result;
}

// Returns this matrix multiplied by a scalar
template<typename T>
Matrix<T> Matrix<T>::scale(T k) {
	Matrix<T> result = Matrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, _matrix[i][j] * k);
	return result;
}

// Returns the transpose of this matrix
template<typename T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> result = Matrix<T>(_cols, _rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			result.set(j, i, _matrix[i][j]);
		}
	return result;
}

// Returns the product of this matrix with another
template<typename T>
Matrix<T> Matrix<T>::mul(Matrix other) {
	if (_cols != other._rows)
		throw std::runtime_error("Matrix dimensions do not match");
	Matrix<T> result = Matrix<T>(_rows, other.cols());
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < other.cols(); j++) {
			T sum = 0;
			for (int k = 0; k < _cols; k++)
				sum += _matrix[i][k] * other.get(k, j);
			result.set(i, j, sum);
		}
	return result;
}

// Returns the reduced row echelon form of this matrix
template<typename T>
Matrix<T> Matrix<T>::rref() {
	Matrix<T> result = *this;
	int x = 0;
	int y = 0;
	while (x < _rows && y < _cols) {
		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					T temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
				}
			} else {
				y++;
				if (x == _rows - 1)
					break;
				continue;
			}
			/*std::cout << "Row exchange (Row " << x + 1 << " <-> Row "
			 << rowToExchange + 1 << ")" << std::endl;
			 result.print();*/
		}
		if (result.get(x, y) != 1 && result.get(x, y) != 0) {
			T k = result.get(x, y);
			for (int j = 0; j < _cols; j++)
				result.set(x, j, result.get(x, j) / k);
			/*std::cout << "Row division (Row " << x + 1 << " / " << k << ")"
			 << std::endl;
			 result.print();*/
		}
		for (int i = 0; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				T n = -(result.get(i, y) / result.get(x, y));
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
Matrix<T> Matrix<T>::upperTriangular() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	Matrix<T> result = *this;
	int x = 0;
	int y = 0;
	while (x < _rows && y < _cols) {
		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					T temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
				}
			} else {
				y++;
				if (x == _rows - 1)
					break;
				continue;
			}
		}
		for (int i = x; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				T n = -(result.get(i, y) / result.get(x, y));
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
T Matrix<T>::determinant() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	Matrix<T> result = *this;
	int rowChanges = 0;
	int x = 0;
	int y = 0;
	while (x < _rows && y < _cols) {
		if (result.get(x, y) == 0) {
			int rowToExchange = 0;
			for (int i = x; i < _rows; i++)
				if (result.get(i, y) != 0)
					rowToExchange = i;
			if (rowToExchange != 0) {
				for (int j = 0; j < _cols; j++) {
					T temp = result.get(x, j);
					result.set(x, j, result.get(rowToExchange, j));
					result.set(rowToExchange, j, temp);
					rowChanges++;
				}
			} else {
				y++;
				if (x == _rows - 1)
					break;
				continue;
			}
		}
		for (int i = x; i < _rows; i++) {
			if (i != x && result.get(i, y) != 0) {
				T n = -(result.get(i, y) / result.get(x, y));
				for (int j = 0; j < _cols; j++) {
					result.set(i, j, result.get(i, j) + n * result.get(x, j));
				}
			}
		}
		x++;
		y++;
	}
	T determinant = 1;
	for (int n = 0; n < _rows; n++)
		determinant *= result.get(n, n);
	if (rowChanges % 2 == 1)
		determinant *= -1;
	return determinant;
}

// Returns the inverse of this matrix
template<typename T>
Matrix<T> Matrix<T>::inverse() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	if (determinant() == 0)
		throw std::runtime_error(
				"Matrix is singular, inverse doesn't exist");

	Matrix<T> m = Matrix<T>(_rows, 2 * _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			m.set(i, j, get(i, j));
	for (int n = 0; n < _rows; n++)
		m.set(n, n + _cols, 1);
	m = m.rref();
	Matrix<T> result = Matrix<T>(_rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, m.get(i, j + _cols));
	return result;
}

// Returns a vector of vectors representing the special solutions of this matrix
template<typename T>
std::vector<std::vector<T> > Matrix<T>::specialSolutions() {
	std::vector<std::vector<T> > result;
	Matrix<T> r = rref();
	std::vector<int> pivotColumns;
	for (int i = 0; i < r._rows; i++) {
		std::vector<T> pivotColumn;
		for (int n = 0; n < r._rows; n++) {
			if (n == i)
				pivotColumn.push_back(1);
			else
				pivotColumn.push_back(0);
		}
		bool foundPivotColumn = false;
		for (int j = 0; j < r._cols; j++)
			if (r.getColumn(j) == pivotColumn) {
				pivotColumns.push_back(j);
				foundPivotColumn = true;
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

		std::vector<T> specialSolution;
		for (int n = 0; n < r._cols; n++)
			specialSolution.push_back(0);
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

// Returns a vector of the eigenvalues of this matrix
template<typename T>
std::vector<Complex<T> > Matrix<T>::eigenvalues() {
	if (_rows != _cols)
		throw std::runtime_error("Matrix must be a square matrix");
	PolynomialMatrix<T> m = toPolynomialMatrix();
	PolynomialMatrix<T> lambdaI = PolynomialMatrix<T>(_rows);
	T arr[] = { 0, 1 };
	std::vector<T> coeffs(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (int n = 0; n < _rows; n++)
		lambdaI.set(n, n, Polynomial<T>(coeffs, 1));

	m = m - lambdaI;
	std::vector<Complex<T> > result = m.determinant().roots();

	return result;
}

// Returns a vector of the eigenvectors of this matrix
template<typename T>
std::vector<std::vector<Complex<T> > > Matrix<T>::eigenvectors() {
	std::vector<std::vector<Complex<T> > > result;
	std::vector<Complex<T> > evalues;
	std::vector<Complex<T> > temp = eigenvalues();
	for (int i = 0; i < temp.size(); i++) {
		bool duplicate = false;
		for (int j = 0; j < evalues.size(); j++)
			if (evalues[j] == temp[i])
				duplicate = true;
		if (!duplicate)
			evalues.push_back(temp[i]);
	}
	for (int i = 0; i < evalues.size(); i++) {
		ComplexMatrix<T> m = toComplexMatrix();
		ComplexMatrix<T> lambdaI = ComplexMatrix<T>(_rows);
		for (int n = 0; n < _rows; n++)
			lambdaI.set(n, n, evalues[i]);
		m = m - lambdaI;

		std::vector<std::vector<Complex<T> > > specials = m.specialSolutions();
		for (int n = 0; n < specials.size(); n++)
			result.push_back(specials[n]);
	}
	return result;
}

// Returns the number of rows in this matrix
template<typename T>
int Matrix<T>::rows() {
	return _rows;
}

// Returns the number of columns in this matrix
template<typename T>
int Matrix<T>::cols() {
	return _cols;
}

// Returns a vector representing the specified row of this matrix
template<typename T>
std::vector<T> Matrix<T>::getRow(int m) {
	std::vector<T> result;
	for (int i = 0; i < _cols; i++)
		result.push_back(_matrix[m][i]);
	return result;
}

// Returns a vector representing the specified column of this matrix
template<typename T>
std::vector<T> Matrix<T>::getColumn(int n) {
	std::vector<T> result;
	for (int i = 0; i < _rows; i++)
		result.push_back(_matrix[i][n]);
	return result;
}

// Fills this entire matrix with a given value
template<typename T>
void Matrix<T>::fill(T value) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			_matrix[i][j] = value;
}

// sets the values of the matrix given a two dimensional array of values
template<typename T>
void Matrix<T>::setMatrix(T** matrix) {
	_matrix = matrix;
}

// sets the values of this matrix given a vector of values
template<typename T>
void Matrix<T>::setVector(std::vector<T> values) {
	if (values.size() != _rows * _cols)
		throw std::runtime_error("Incorrect number of values to fill matrix");
	for (int i = 0; i < _rows * _cols; i++)
		_matrix[i / _cols][i % _cols] = values[i];
}

// sets the specified element of this matrix to a given value
template<typename T>
void Matrix<T>::set(int i, int j, T value) {
	_matrix[i][j] = value;
}

// Returns the values of this matrix in a two dimensional array
template<typename T>
T** Matrix<T>::getMatrix() {
	T** matrix = new T*[_rows];
	for (int i = 0; i < _rows; i++)
		matrix[i] = new T[_cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; i < _cols; j++)
			matrix[i][j] = _matrix[i][j];
	return matrix;
}

// Returns the values of this matrix in a vector
template<typename T>
std::vector<T> Matrix<T>::getVector() {
	std::vector<T> values;
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values.push_back(_matrix[i][j]);
	return values;
}

// Returns the values of this matrix in a one dimensional array
template<typename T>
T* Matrix<T>::getArray() {
	T* values = new T[_rows * _cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values[i * _cols + j] = _matrix[i][j];
	return values;
}

// Returns the value of the specified element of this matrix
template<typename T>
T Matrix<T>::get(int i, int j) {
	return _matrix[i][j];
}

// Returns a polynomial version of this matrix
template<typename T>
PolynomialMatrix<T> Matrix<T>::toPolynomialMatrix() {
	PolynomialMatrix<T> m = PolynomialMatrix<T>(_rows);
	std::vector<T> values = getVector();
	std::vector<Polynomial<T> > polyValues;
	for (int i = 0; i < values.size(); i++)
		polyValues.push_back(Polynomial<T>(values[i]));
	m.setVector(polyValues);
	return m;
}

// Returns a complex version of this matrix
template<typename T>
ComplexMatrix<T> Matrix<T>::toComplexMatrix() {
	ComplexMatrix<T> m = ComplexMatrix<T>(_rows);
	std::vector<T> values = getVector();
	std::vector<Complex<T> > polyValues;
	for (int i = 0; i < values.size(); i++)
		polyValues.push_back(Complex<T>(values[i]));
	m.setVector(polyValues);
	return m;
}

// Returns a vector of strings representing this matrix
template<typename T>
std::vector<std::string> Matrix<T>::toStringVector() {
	std::vector<std::string> strings;
	std::string** arr = new std::string*[_rows];
	for (int i = 0; i < _rows; i++) {
		arr[i] = new std::string[_cols];
		for (int j = 0; j < _cols; j++) {
			std::string str = std::to_string(_matrix[i][j]);
			if (str.find(std::string(".")) != std::string::npos) {
				for (int c = str.length() - 1; c >= 0; c--) {
					if (str.at(c) != '0' || str.at(c - 1) == '.')
						break;
					str = str.substr(0, c);
				}
			}
			arr[i][j] = str;
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
void Matrix<T>::print() {
	std::vector<std::string> strings = toStringVector();
	for (int i = 0; i < strings.size(); i++)
		std::cout << strings[i] << std::endl;
	std::cout << std::endl;
}

// Allows for the addition of two matrices with the + operator
template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> rhs) {
	return add(rhs);
}

// Allows for the subtraction of two matrices with the - operator
template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> rhs) {
	return add(rhs.scale(-1));
}

// Allows for the negation of a matrix with the - operator
template<typename T>
Matrix<T> Matrix<T>::operator-() {
	return scale(-1);
}

// Allows for the scaling of a matrix with the * operator
template<typename T>
Matrix<T> Matrix<T>::operator*(T rhs) {
	return scale(rhs);
}

// Allows for the multiplication of two matrices with the * operator
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> rhs) {
	return mul(rhs);
}

// Allows for the division of two matrices with the / operator
template<typename T>
Matrix<T> Matrix<T>::operator/(Matrix<T> rhs) {
	return mul(rhs.inverse());
}

// Allows for the scaling of a matrix with the / operator
template<typename T>
Matrix<T> Matrix<T>::operator/(T rhs) {
	return scale(1 / rhs);
}

// Allows for the exponentiation of two matrices with the ^ operator
template<typename T>
Matrix<T> Matrix<T>::operator^(int rhs) {
	Matrix<T> result = *this;
	for (int i = 0; i < rhs; i++)
		result = result.mul(result);
	return result;
}

// Allows for the left multiplication of two matrices with the << operator
template<typename T>
Matrix<T> Matrix<T>::operator<<(Matrix<T> rhs) {
	return rhs.mul(*this);
}

// Returns a matrix of the specified size filled with zeros
template<typename T>
Matrix<T> Matrix<T>::zeros(int m, int n) {
	Matrix<T> result = Matrix<T>(m, n);
	return result;
}

// Returns a matrix of the specified size filled with ones
template<typename T>
Matrix<T> Matrix<T>::ones(int m, int n) {
	Matrix<T> result = Matrix<T>(m, n);
	result.fill(1);
	return result;
}

// Returns the identity matrix of the specified size
template<typename T>
Matrix<T> Matrix<T>::identity(int size) {
	Matrix<T> result = Matrix<T>(size, size);
	for (int n = 0; n < size; n++)
		result.set(n, n, 1);
	return result;
}

// Explicit instantiation of template classes
template class Matrix<float> ;
template class Matrix<double> ;
template class Matrix<long double> ;
template Matrix<float>::Matrix(Matrix<float>);
template Matrix<float>::Matrix(Matrix<double>);
template Matrix<float>::Matrix(Matrix<long double>);
template Matrix<double>::Matrix(Matrix<float>);
template Matrix<double>::Matrix(Matrix<double>);
template Matrix<double>::Matrix(Matrix<long double>);
template Matrix<long double>::Matrix(Matrix<float>);
template Matrix<long double>::Matrix(Matrix<double>);
template Matrix<long double>::Matrix(Matrix<long double>);
