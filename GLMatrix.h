/*
 * Matrix.h
 *
 *  Created on: Mar 24, 2015
 *      Author: ericwadkins
 */

#ifndef GLMATRIX_H_
#define GLMATRIX_H_

#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T>
class GLMatrix {
public:
	GLMatrix(int m, int n);
	template<typename S> GLMatrix(GLMatrix<S> rhs);
	virtual ~GLMatrix() {
	}
	GLMatrix add(GLMatrix other);
	GLMatrix scale(T k);
	GLMatrix transpose();
	GLMatrix mul(GLMatrix other);
	GLMatrix reducedRowEchelon();
	GLMatrix upperTriangular();
	GLMatrix lowerTriangular();
	int rows();
	int cols();
	void set(std::vector<T> values);
	void set(int row, int col, T value);
	T** matrix();
	GLMatrix clone();
	void print();
	//template<typename S> GLMatrix<T> operator=(GLMatrix<S> rhs);
private:
	int _rows;
	int _cols;
	T** _matrix;
};

#endif /* GLMATRIX_H_ */
