/*
 * GenericMatrix.h
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#ifndef GENERICMATRIX_H_
#define GENERICMATRIX_H_

#include "Matrix.h"

template<typename T>
class GenericMatrix: public Matrix<T> {
public:
	GenericMatrix(int m, int n);
	GenericMatrix(int size);
	template<typename S> GenericMatrix(GenericMatrix<S> other);
	virtual ~GenericMatrix() {
	}
};

#endif /* GENERICMATRIX_H_ */
