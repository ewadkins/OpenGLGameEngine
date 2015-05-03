/*
 * ComplexMatrix.h
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#ifndef COMPLEXMATRIX_H_
#define COMPLEXMATRIX_H_

#include "Complex.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>
#include <typeinfo>

template<typename T>
class ComplexMatrix {
public:
	ComplexMatrix(int m, int n);
	ComplexMatrix(int size);
	template<typename S> ComplexMatrix(ComplexMatrix<S> other);
	virtual ~ComplexMatrix() {
	}
	ComplexMatrix add(ComplexMatrix other);
	ComplexMatrix scale(T k);
	ComplexMatrix transpose();
	ComplexMatrix mul(ComplexMatrix other);
	ComplexMatrix rref();
	ComplexMatrix upperTriangular();
	Complex<T> determinant();
	ComplexMatrix inverse();
	std::vector<std::vector<Complex<T> > > specialSolutions();
	int rows();
	int cols();
	std::vector<Complex<T> > getRow(int m);
	std::vector<Complex<T> > getColumn(int n);
	void fill(T value);
	void setMatrix(T** matrix);
	void setVector(std::vector<T> values);
	void set(int row, int col, T value);
	void setMatrix(Complex<T>** matrix);
	void setVector(std::vector<Complex<T> > values);
	void set(int row, int col, Complex<T> value);
	Complex<T>** getMatrix();
	std::vector<Complex<T> > getVector();
	Complex<T>* getArray();
	Complex<T> get(int i, int j);
	T** getMatrixConstants();
	std::vector<T> getVectorConstants();
	T* getArrayConstants();
	T getConstant(int i, int j);
	std::vector<std::string> toStringVector();
	void print();
	ComplexMatrix operator+(ComplexMatrix rhs);
	ComplexMatrix operator-(ComplexMatrix rhs);
	ComplexMatrix operator-();
	ComplexMatrix operator*(T rhs);
	ComplexMatrix operator*(ComplexMatrix rhs);
	ComplexMatrix operator/(T rhs);
	ComplexMatrix operator/(ComplexMatrix rhs);
	ComplexMatrix operator^(int rhs);
	ComplexMatrix operator<<(ComplexMatrix rhs);
	static ComplexMatrix zeros(int m, int n);
	static ComplexMatrix ones(int m, int n);
	static ComplexMatrix identity(int size);
private:
	int _rows;
	int _cols;
	Complex<T>** _matrix;
};

#endif /* COMPLEXMATRIX_H_ */
