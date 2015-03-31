/*
 * GLMatrix.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: ericwadkins
 */

#include "GLMatrix.h"

template<typename T>
const T GLMatrix<T>::PI = 3.1415926535897;

// Basic constructor
template<typename T>
GLMatrix<T>::GLMatrix(int rows, int cols) {
	_rows = rows;
	_cols = cols;
	_matrix = new T*[_rows];
	for (int i = 0; i < _rows; i++)
		_matrix[i] = new T[_cols];
	fill(0);
}

// Constructor that allows matrix casting
template<typename T>
template<typename S>
GLMatrix<T>::GLMatrix(GLMatrix<S> other) {
	_rows = other.rows();
	_cols = other.cols();
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			set(i, j, other.matix()[i][j]);
		}
}

// Returns the sum of this matrix with another
template<typename T>
GLMatrix<T> GLMatrix<T>::add(GLMatrix other) {
	if (_rows != other._rows || _cols != other._cols)
		throw std::invalid_argument("Matrix dimensions do not match");
	GLMatrix<T> result = GLMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, get(i, j) + other.get(i, j));
	return result;
}

// Returns this matrix multiplied by a scalar
template<typename T>
GLMatrix<T> GLMatrix<T>::scale(T k) {
	GLMatrix<T> result = GLMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, k * get(i, j));
	return result;
}

// Returns the transpose of this matrix
template<typename T>
GLMatrix<T> GLMatrix<T>::transpose() {
	GLMatrix<T> result = GLMatrix<T>(_cols, _rows);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			result.set(j, i, get(i, j));
		}
	return result;
}

// Returns the product of this matrix with another
template<typename T>
GLMatrix<T> GLMatrix<T>::mul(GLMatrix other) {
	GLMatrix<T> result = GLMatrix<T>(_rows, other.cols());
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < other.cols(); j++) {
			T sum = 0;
			for (int k = 0; k < _cols; k++)
				sum += get(i, k) * other.get(k, j);
			result.set(i, j, sum);
		}
	return result;
}

// Returns the reduced row echelon form of this matrix
template<typename T>
GLMatrix<T> GLMatrix<T>::rref() {
	GLMatrix<T> result = clone();
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
					T temp = result.get(x, j);
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
					result.set(i, j, result.get(i, j) + n * result.get(x, j));
				}
			}
		}
		x++;
		y++;
		/*std::cout << "Row elimination" << std::endl;
		 result.print();*/
	}
	/*
	 // Change negative zeros from floating point error to normal zeros
	 for (int i = 0; i < _rows; i++)
	 for (int j = 0; j < _cols; j++)
	 if (result.get(i, j) == 0) {
	 result.set(i, j, 0);
	 }*/
	return result;
}

// Returns the upper triangular factorization of this matrix
template<typename T>
GLMatrix<T> GLMatrix<T>::upperTriangular() {
	if (_rows != _cols)
		throw std::invalid_argument("Matrix must be a square matrix");

	GLMatrix<T> result = clone();
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
					T temp = result.get(x, j);
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
				T n = -(result.get(i, y) / result.get(x, y));
				for (int j = 0; j < _cols; j++) {
					result.set(i, j, result.get(i, j) + n * result.get(x, j));
				}
			}
		}
		x++;
		y++;
	}
	/*
	 // Change negative zeros from floating point error to normal zeros
	 for (int i = 0; i < _rows; i++)
	 for (int j = 0; j < _cols; j++)
	 if (result.get(i, j) == 0) {
	 result.set(i, j, 0);
	 }*/
	return result;
}

// Returns the determinant of this matrix
template<typename T>
T GLMatrix<T>::determinant() {
	if (_rows != _cols)
		throw std::invalid_argument("Matrix must be a square matrix");

	GLMatrix<T> result = clone();
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
					T temp = result.get(x, j);
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
GLMatrix<T> GLMatrix<T>::inverse() {
	if (_rows != _cols)
		throw std::invalid_argument("Matrix must be a square matrix");
	if (determinant() == 0)
		throw std::invalid_argument(
				"Matrix is singular, inverse doesn't exist");

	GLMatrix<T> m = GLMatrix<T>(_rows, 2 * _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			m.set(i, j, get(i, j));
	for (int n = 0; n < _rows; n++)
		m.set(n, n + _cols, 1);
	m = m.rref();
	GLMatrix<T> result = GLMatrix<T>(_rows, _cols);
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			result.set(i, j, m.get(i, j + _cols));
	return result;
}

// Returns the number of rows in this matrix
template<typename T>
int GLMatrix<T>::rows() {
	return _rows;
}

// Returns the number of columns in this matrix
template<typename T>
int GLMatrix<T>::cols() {
	return _cols;
}

// Fills this entire matrix with a given value
template<typename T>
void GLMatrix<T>::fill(T value) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			set(i, j, value);
}

// Sets the values of the matrix given a two dimensional array of values
template<typename T>
void GLMatrix<T>::setMatrix(T** matrix) {
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++) {
			set(i, j, matrix[i][j]);
		}
}

// Sets the values of this matrix given a vector of values
template<typename T>
void GLMatrix<T>::setValues(std::vector<T> values) {
	if (values.size() != _rows * _cols)
		throw std::invalid_argument(
				"Incorrect number of input values to fill matrix");

	for (int i = 0; i < _rows * _cols; i++) {
		set(i / _cols, i % _cols, values[i]);
	}
}

// Sets the specified element of this matrix to a given value
template<typename T>
void GLMatrix<T>::set(int i, int j, T value) {
	_matrix[i][j] = value;
}

// Returns the values of this matrix in a two dimensional array
template<typename T>
T** GLMatrix<T>::getMatrix() {
	return _matrix;
}

// Returns the values of this matrix in a vector
template<typename T>
std::vector<T> GLMatrix<T>::getValues() {
	std::vector<T> values;
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values.push_back(_matrix[i][j]);
	return values;
}

// Returns the values of this matrix in a one dimensional array
template<typename T>
T* GLMatrix<T>::getValuesArray() {
	T* values = new T[_rows * _cols];
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			values[i * _cols + j] = _matrix[i][j];
	return values;
}

// Returns the value of the specified element of this matrix
template<typename T>
T GLMatrix<T>::get(int i, int j) {
	return _matrix[i][j];
}

// Returns a copy of this object (another matrix with the same values)
template<typename T>
GLMatrix<T> GLMatrix<T>::clone() {
	GLMatrix<T> result = GLMatrix<T>(_rows, _cols);
	result.setMatrix(_matrix);
	return result;
}

// Returns the vector of strings representing this matrix
template<typename T>
std::vector<std::string> GLMatrix<T>::toStringVector() {
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
void GLMatrix<T>::print() {
	std::vector<std::string> strings = toStringVector();
	for (int i = 0; i < strings.size(); i++)
		std::cout << strings[i] << std::endl;
	std::cout << std::endl;
}

// Allows for the addition of two matrices with the + operator
template<typename T>
GLMatrix<T> GLMatrix<T>::operator+(GLMatrix<T> rhs) {
	return add(rhs);
}

// Allows for the subtraction of two matrices with the - operator
template<typename T>
GLMatrix<T> GLMatrix<T>::operator-(GLMatrix<T> rhs) {
	return add(rhs.scale(-1));
}

// Allows for the scaling of a matrix with the * operator
template<typename T>
GLMatrix<T> GLMatrix<T>::operator*(T rhs) {
	return scale(rhs);
}

// Allows for the multiplication of two matrices with the * operator
template<typename T>
GLMatrix<T> GLMatrix<T>::operator*(GLMatrix<T> rhs) {
	return mul(rhs);
}

// Allows for the division of two matrices with the / operator
template<typename T>
GLMatrix<T> GLMatrix<T>::operator/(GLMatrix<T> rhs) {
	return mul(rhs.inverse());
}

// Allows for the left multiplication of two matrices with the << operator
template<typename T>
GLMatrix<T> GLMatrix<T>::operator<<(GLMatrix<T> rhs) {
	return rhs.mul(clone());
}

// Returns a matrix of the specified size filled with zeros
template<typename T>
GLMatrix<T> GLMatrix<T>::zeros(int m, int n) {
	GLMatrix<T> result = GLMatrix<T>(m, n);
	return result;
}

// Returns a matrix of the specified size filled with ones
template<typename T>
GLMatrix<T> GLMatrix<T>::ones(int m, int n) {
	GLMatrix<T> result = GLMatrix<T>(m, n);
	result.fill(1);
	return result;
}

// Returns the identity matrix of the specified size
template<typename T>
GLMatrix<T> GLMatrix<T>::identity(int size) {
	GLMatrix<T> result = GLMatrix<T>(size, size);
	for (int n = 0; n < size; n++)
		result.set(n, n, 1);
	return result;
}

// Returns the translation matrix given the desired change in x, y, and z coordinates
template<typename T>
GLMatrix<T> GLMatrix<T>::translationMatrix(T deltaX, T deltaY, T deltaZ) {
	GLMatrix<T> result = identity(4);
	result.set(0, 3, deltaX);
	result.set(1, 3, deltaY);
	result.set(2, 3, deltaZ);
	return result;
}

// Returns the scalar matrix given the desired scale in the x, y, and z directions
template<typename T>
GLMatrix<T> GLMatrix<T>::scalarMatrix(T scaleX, T scaleY, T scaleZ) {
	GLMatrix<T> result = identity(4);
	result.set(0, 0, scaleX);
	result.set(1, 1, scaleY);
	result.set(2, 2, scaleZ);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the x axis
template<typename T>
GLMatrix<T> GLMatrix<T>::rotationMatrixX(T theta) {
	GLMatrix<T> result = identity(4);
	T rads = theta * PI / 180;
	result.set(1, 1, std::cos(rads));
	result.set(1, 2, -std::sin(rads));
	result.set(2, 1, std::sin(rads));
	result.set(2, 2, std::cos(rads));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the y axis
template<typename T>
GLMatrix<T> GLMatrix<T>::rotationMatrixY(T theta) {
	GLMatrix<T> result = identity(4);
	T rads = theta * PI / 180;
	result.set(0, 0, std::cos(rads));
	result.set(0, 2, std::sin(rads));
	result.set(2, 0, -std::sin(rads));
	result.set(2, 2, std::cos(rads));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the z axis
template<typename T>
GLMatrix<T> GLMatrix<T>::rotationMatrixZ(T theta) {
	GLMatrix<T> result = identity(4);
	T rads = theta * PI / 180;
	result.set(0, 0, std::cos(rads));
	result.set(0, 1, -std::sin(rads));
	result.set(1, 0, std::sin(rads));
	result.set(1, 1, std::cos(rads));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the x, y, and z axes
template<typename T>
GLMatrix<T> GLMatrix<T>::rotationMatrixXYZ(T thetaX, T thetaY, T thetaZ) {
	GLMatrix<T> result = identity(4);
	T radsX = thetaX * PI / 180;
	T radsY = thetaY * PI / 180;
	T radsZ = thetaZ * PI / 180;
	result.set(0, 0, std::cos(radsY) * std::cos(radsZ));
	result.set(0, 1,
			std::cos(radsZ) * std::sin(radsX) * std::sin(radsY)
					- std::cos(radsX) * std::sin(radsZ));
	result.set(0, 2,
			std::cos(radsX) * std::cos(radsZ) * std::sin(radsY)
					+ std::sin(radsX) * std::sin(radsZ));
	result.set(1, 0, std::cos(radsY) * std::sin(radsZ));
	result.set(1, 1,
			std::cos(radsX) * std::cos(radsZ)
					+ std::sin(radsX) * std::sin(radsY) * std::sin(radsZ));
	result.set(1, 2,
			std::cos(radsX) * std::sin(radsY) * std::sin(radsZ)
					- std::cos(radsZ) * std::sin(radsX));
	result.set(2, 0, -std::sin(radsY));
	result.set(2, 1, std::cos(radsY) * std::sin(radsX));
	result.set(2, 2, std::cos(radsX) * std::cos(radsY));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the line through (x, y, z) with the direction (u, v, w)
template<typename T>
GLMatrix<T> GLMatrix<T>::rotationMatrixLine(T x, T y, T z, T u, T v, T w,
		T theta) {
	GLMatrix<T> result = identity(4);
	T rads = theta * PI / 180;
	result.set(0, 0,
			(u * u + (v * v + w * w) * std::cos(rads))
					/ (u * u + v * v + w * w));
	result.set(0, 1,
			(u * v * (1 - std::cos(rads))
					- w * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(0, 2,
			(u * w * (1 - std::cos(rads))
					+ v * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(0, 3,
			((x * (v * v + w * w) - u * (y * v + z * w)) * (1 - std::cos(rads))
					+ (y * w - z * v) * std::sqrt(u * u + v * v + w * w)
							* std::sin(rads)) / (u * u + v * v + w * w));
	result.set(1, 0,
			(u * v * (1 - std::cos(rads))
					+ w * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 1,
			(v * v + (u * u + w * w) * std::cos(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 2,
			(v * w * (1 - std::cos(rads))
					- u * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 3,
			((y * (u * u + w * w) - v * (x * u + z * w)) * (1 - std::cos(rads))
					+ (z * u - x * w) * std::sqrt(u * u + v * v + w * w)
							* std::sin(rads)) / (u * u + v * v + w * w));
	result.set(2, 0,
			(u * w * (1 - std::cos(rads))
					- v * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 1,
			(v * w * (1 - std::cos(rads))
					+ u * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 2,
			(w * w + (u * u + v * v) * std::cos(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 3,
			((z * (u * u + v * v) - w * (x * u + y * v)) * (1 - std::cos(rads))
					+ (x * v - y * u) * std::sqrt(u * u + v * v + w * w)
							* std::sin(rads)) / (u * u + v * v + w * w));
	return result;
}

// Returns the orthographic projection matrix given the dimensions of the window and the near and far clipping planes
template<typename T>
GLMatrix<T> GLMatrix<T>::orthographicProjectionMatrix(T width, T height, T near,
		T far) {
	GLMatrix<T> result = identity(4);
	result.set(0, 0, 1 / width);
	result.set(1, 1, 1 / height);
	result.set(2, 2, -2 / (far - near));
	result.set(2, 3, (far + near) / (far - near));
	return result;
}

// Returns the perspective projection matrix given the x and y field of view and the near and far clipping planes
template<typename T>
GLMatrix<T> GLMatrix<T>::perspectiveProjectionMatrix(T fovX, T fovY, T near,
		T far) {
	GLMatrix<T> result = zeros(4, 4);
	T fovXRads = fovX * PI / 180;
	T fovYRads = fovY * PI / 180;
	result.set(0, 0, std::atan(fovXRads / 2));
	result.set(1, 1, std::atan(fovYRads / 2));
	result.set(2, 2, -(far + near) / (far - near));
	result.set(2, 3, -2 * (near * far) / (far - near));
	result.set(3, 2, -1);
	return result;
}

// Explicit instantiation of template classes
template class GLMatrix<float> ;
template class GLMatrix<double> ;
template class GLMatrix<long double> ;

