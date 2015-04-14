/*
 * PolynomialMatrix.h
 *
 *  Created on: Apr 5, 2015
 *      Author: ericwadkins
 */

#ifndef MATH_POLYNOMIALMATRIX_H_
#define MATH_POLYNOMIALMATRIX_H_

#include "../Math/Polynomial.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>
#include <typeinfo>

template<typename T>
class PolynomialMatrix {
public:
	PolynomialMatrix(int m, int n);
	PolynomialMatrix(int size);
	template<typename S> PolynomialMatrix(PolynomialMatrix<S> other);
	virtual ~PolynomialMatrix() {
	}
	PolynomialMatrix add(PolynomialMatrix other);
	PolynomialMatrix scale(T k);
	PolynomialMatrix transpose();
	PolynomialMatrix mul(PolynomialMatrix other);
	PolynomialMatrix rref();
	PolynomialMatrix upperTriangular();
	Polynomial<T> determinant();
	PolynomialMatrix inverse();
	int rows();
	int cols();
	void fill(T value);
	void setMatrix(T** matrix);
	void setVector(std::vector<T> values);
	void set(int row, int col, T value);
	void setMatrix(Polynomial<T>** matrix);
	void setVector(std::vector<Polynomial<T> > values);
	void set(int row, int col, Polynomial<T> value);
	Polynomial<T>** getMatrix();
	std::vector<Polynomial<T> > getVector();
	Polynomial<T>* getArray();
	Polynomial<T> get(int i, int j);
	T** getMatrixConstants();
	std::vector<T> getVectorConstants();
	T* getArrayConstants();
	T getConstant(int i, int j);
	PolynomialMatrix clone();
	std::vector<std::string> toStringVector();
	void print();
	PolynomialMatrix operator+(PolynomialMatrix rhs);
	PolynomialMatrix operator-(PolynomialMatrix rhs);
	PolynomialMatrix operator-();
	PolynomialMatrix operator*(T rhs);
	PolynomialMatrix operator*(PolynomialMatrix rhs);
	PolynomialMatrix operator/(T rhs);
	PolynomialMatrix operator/(PolynomialMatrix rhs);
	PolynomialMatrix operator^(int rhs);
	PolynomialMatrix operator<<(PolynomialMatrix rhs);
	static PolynomialMatrix zeros(int m, int n);
	static PolynomialMatrix ones(int m, int n);
	static PolynomialMatrix identity(int size);
private:
	int _rows;
	int _cols;
	Polynomial<T>** _matrix;
};

#endif /* MATH_POLYNOMIALMATRIX_H_ */
