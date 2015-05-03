/*
 * PolynomialMatrix.h
 *
 *  Created on: Apr 5, 2015
 *      Author: ericwadkins
 */

#ifndef POLYNOMIALMATRIX_H_
#define POLYNOMIALMATRIX_H_

#include "Polynomial.h"
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
	std::vector<std::vector<Polynomial<T> > > specialSolutions();
	int rows();
	int cols();
	std::vector<Polynomial<T> > getRow(int m);
	std::vector<Polynomial<T> > getColumn(int n);
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

#endif /* POLYNOMIALMATRIX_H_ */
