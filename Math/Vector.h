/*
 * Vector.h
 *
 *  Created on: Apr 28, 2015
 *      Author: ericwadkins
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>
#include <exception>

template<typename T>
class Vector {
public:
	Vector();
	Vector(int size);
	Vector(T v1, T v2, T v3);
	Vector(T v1, T v2, T v3, T v4);
	template<typename S> Vector(Vector<S> other);
	virtual ~Vector() {
	}
	Vector add(Vector other);
	T dot(Vector other);
	void set(int i, T value);
	void setVector(std::vector<T> values);
	T get(int i);
	std::vector<T> getVector();
	T* operator[](int i);
private:
	std::vector<T*> _vector;
};

#endif /* VECTOR_H_ */
