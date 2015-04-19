/*
 * ComplexMatrix.h
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#ifndef COMPLEXMATRIX_H_
#define COMPLEXMATRIX_H_

#include "Complex.h"
#include <stdexcept>
#include <vector>
#include <string>

template<typename T>
class Matrix;
template<typename T>
class GenericMatrix;
template<typename T>
class PolynomialMatrix;

template<typename T>
class ComplexMatrix: public Matrix<Complex<T> > {
public:
	ComplexMatrix(int m, int n);
	ComplexMatrix(int size);
	template<typename S> ComplexMatrix(ComplexMatrix<S> other);
	virtual ~ComplexMatrix() {
	}
	virtual std::vector<Complex<T> > eigenvalues();
	virtual GenericMatrix<T>* toGenericMatrix();
	virtual PolynomialMatrix<T>* toPolynomialMatrix();
	virtual ComplexMatrix<T>* toComplexMatrix();
	virtual std::vector<std::string> toStringVector();
};

#endif /* COMPLEXMATRIX_H_ */
