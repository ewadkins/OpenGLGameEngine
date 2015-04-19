/*
 * ComplexMatrix.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#include "ComplexMatrix.h"
#include "Matrix.h"

// Basic constructor
template<typename T>
ComplexMatrix<T>::ComplexMatrix(int rows, int cols) :
		Matrix<T>(rows, cols) {
}

// Square matrix constructor
template<typename T>
ComplexMatrix<T>::ComplexMatrix(int size) :
		Matrix<T>(size) {
}

// Constructor that allows matrix casting
template<typename T>
template<typename S>
ComplexMatrix<T>::ComplexMatrix(ComplexMatrix<S> other) :
		Matrix<T>(other) {
}

// Returns a vector of the eigenvalues of this matrix
template<typename T>
std::vector<Complex<T> > ComplexMatrix<T>::eigenvalues() {
	throw std::runtime_error(
			"Eigenvalues function of ComplexMatrix is not supported");
}

// Returns a generic version of this matrix
template<typename T>
GenericMatrix<T>* GenericMatrix<T>::toGenericMatrix() {
	GenericMatrix<T>* m = new GenericMatrix<T>(this->_rows);
	std::vector<T> polyValues = this->getVector();
	std::vector<T> values;
	for (int i = 0; i < values.size(); i++)
		values.push_back(polyValues[i].value());
	m->setVector(values);
	return m;
}

// Returns a polynomial version of this matrix
template<typename T>
PolynomialMatrix<T>* ComplexMatrix<T>::toPolynomialMatrix() {
	throw std::runtime_error(
			"Cannot cast from complex to polynomial matrix");
}

// Returns a complex version of this matrix
template<typename T>
ComplexMatrix<T>* GenericMatrix<T>::toComplexMatrix() {
	return this->clone();
}

// Returns a vector of strings representing this matrix
template<typename T>
std::vector<std::string> ComplexMatrix<T>::toStringVector() {
	std::vector<std::string> strings;
	std::string** arr = new std::string*[this->_rows];
	for (int i = 0; i < this->_rows; i++) {
		arr[i] = new std::string[this->_cols];
		for (int j = 0; j < this->_cols; j++) {
			std::string str = (this->_matrix[i][j]).toString();
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
	for (int j = 0; j < this->_cols; j++) {
		int maxLength = 0;
		for (int i = 0; i < this->_rows; i++)
			if (arr[i][j].length() > maxLength)
				maxLength = arr[i][j].length();
		for (int i = 0; i < this->_rows; i++)
			while (arr[i][j].length() < maxLength)
				arr[i][j] = " " + arr[i][j];
	}
	for (int i = 0; i < this->_rows; i++) {
		std::string str = "";
		for (int j = 0; j < this->_cols; j++) {
			if (j == 0)
				str += "[";
			str += " " + arr[i][j] + " ";
			if (j == this->_cols - 1)
				str += "]";
		}
		strings.push_back(str);
	}
	return strings;
}

// Explicit instantiation of template classes
template class ComplexMatrix<float> ;
template class ComplexMatrix<double> ;
template class ComplexMatrix<long double> ;
