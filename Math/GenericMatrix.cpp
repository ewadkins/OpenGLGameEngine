/*
 * GenericMatrix.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#include "GenericMatrix.h"

// Basic constructor
template<typename T>
GenericMatrix<T>::GenericMatrix(int rows, int cols) :
		Matrix<T>(rows, cols) {
}

// Square matrix constructor
template<typename T>
GenericMatrix<T>::GenericMatrix(int size) :
		Matrix<T>(size) {
}

// Constructor that allows matrix casting
template<typename T>
template<typename S>
GenericMatrix<T>::GenericMatrix(GenericMatrix<S> other) :
		Matrix<T>(other) {
}

