/*
 * Matrix.h
 *
 *  Created on: Mar 24, 2015
 *      Author: ericwadkins
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "PolynomialMatrix.h"
#include "ComplexMatrix.h"
#include "Polynomial.h"
#include "Complex.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>
#include <typeinfo>

template<typename T>
class Matrix {
public:
	Matrix(int m, int n);
	Matrix(int size);
	template<typename S> Matrix(Matrix<S> other);
	virtual ~Matrix() {
	}
	Matrix add(Matrix other);
	Matrix scale(T k);
	Matrix transpose();
	Matrix mul(Matrix other);
	Matrix rref();
	Matrix upperTriangular();
	T determinant();
	Matrix inverse();
	std::vector<std::vector<T> > specialSolutions();
	std::vector<Complex<T> > eigenvalues();
	std::vector<std::vector<Complex<T> > > eigenvectors();
	int rows();
	int cols();
	std::vector<T> getRow(int m);
	std::vector<T> getColumn(int n);
	void fill(T value);
	void setMatrix(T** matrix);
	void setVector(std::vector<T> values);
	void set(int row, int col, T value);
	T** getMatrix();
	std::vector<T> getVector();
	T* getArray();
	T get(int i, int j);
	PolynomialMatrix<T> toPolynomialMatrix();
	ComplexMatrix<T> toComplexMatrix();
	std::vector<std::string> toStringVector();
	void print();
	Matrix operator+(Matrix rhs);
	Matrix operator-(Matrix rhs);
	Matrix operator-();
	Matrix operator*(T rhs);
	Matrix operator*(Matrix rhs);
	Matrix operator/(T rhs);
	Matrix operator/(Matrix rhs);
	Matrix operator^(int rhs);
	Matrix operator<<(Matrix rhs);
	static Matrix zeros(int m, int n);
	static Matrix ones(int m, int n);
	static Matrix identity(int size);
private:
	int _rows;
	int _cols;
	T** _matrix;
};

#endif /* MATRIX_H_ */
