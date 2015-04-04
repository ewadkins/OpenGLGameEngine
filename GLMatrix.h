/*
 * Matrix.h
 *
 *  Created on: Mar 24, 2015
 *      Author: ericwadkins
 */

#ifndef GLMATRIX_H_
#define GLMATRIX_H_

#include "Polynomial.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>
#include <typeinfo>

template<typename T>
class GLMatrix {
public:
	GLMatrix(int m, int n);
	template<typename S> GLMatrix(GLMatrix<S> other);
	virtual ~GLMatrix() {
	}
	GLMatrix add(GLMatrix other);
	GLMatrix scale(T k);
	GLMatrix transpose();
	GLMatrix mul(GLMatrix other);
	GLMatrix rref();
	GLMatrix upperTriangular();
	Polynomial<T> determinant();
	GLMatrix inverse();
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
	GLMatrix clone();
	std::vector<std::string> toStringVector();
	void print();
	GLMatrix operator+(GLMatrix rhs);
	GLMatrix operator-(GLMatrix rhs);
	GLMatrix operator-();
	GLMatrix operator*(T rhs);
	GLMatrix operator*(GLMatrix rhs);
	GLMatrix operator/(T rhs);
	GLMatrix operator/(GLMatrix rhs);
	GLMatrix operator^(int rhs);
	GLMatrix operator<<(GLMatrix rhs);
	static GLMatrix zeros(int m, int n);
	static GLMatrix ones(int m, int n);
	static GLMatrix identity(int size);
	static GLMatrix translationMatrix(T deltaX, T deltaY, T deltaZ);
	static GLMatrix scalarMatrix(T scaleX, T scaleY, T scaleZ);
	static GLMatrix rotationMatrixX(T theta);
	static GLMatrix rotationMatrixY(T theta);
	static GLMatrix rotationMatrixZ(T theta);
	static GLMatrix rotationMatrixXYZ(T thetaX, T thetaY, T thetaZ);
	static GLMatrix rotationMatrixLine(T a, T b, T c, T u, T v, T w, T theta);
	static GLMatrix orthographicProjectionMatrix(T width, T height, T near, T far);
	static GLMatrix perspectiveProjectionMatrix(T fovX, T fovY, T near, T far);
private:
	int _rows;
	int _cols;
	Polynomial<T>** _matrix;
	static const T PI;
};

#endif /* GLMATRIX_H_ */
