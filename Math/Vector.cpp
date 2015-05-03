/*
 * Vector.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: ericwadkins
 */

#include "Vector.h"

template<typename T>
Vector<T>::Vector() {
}

template<typename T>
Vector<T>::Vector(int size) {
	for (int i = 0; i < size; i ++)
		_vector.push_back(0);
}

template<typename T>
Vector<T>::Vector(T v1, T v2, T v3) {
	_vector.push_back(&v1);
	_vector.push_back(&v2);
	_vector.push_back(&v3);
}

template<typename T>
Vector<T>::Vector(T v1, T v2, T v3, T v4) {
	_vector.push_back(&v1);
	_vector.push_back(&v2);
	_vector.push_back(&v3);
	_vector.push_back(&v4);
}

template<typename T>
template<typename S>
Vector<T>::Vector(Vector<S> other) {
	std::vector<S> otherValues = other.getVector();
	for (int i = 0; i < otherValues.size(); i++)
		set(i, otherValues[i]);
}

template<typename T>
Vector<T> Vector<T>::add(Vector other) {
	std::vector<T> otherValues = other.getVector();
	Vector result = Vector<T>(std::max(_vector.size(), otherValues.size()));
	for (int i = 0; i < _vector.size(); i++)
		result.set(i, result.get(i) + get(i));
	for (int i = 0; i < otherValues.size(); i++)
		result.set(i, result.get(i) + otherValues[i]);
}

template<typename T>
T Vector<T>::dot(Vector other) { // FIXME Finish

}

// FIXME add size() function

template<typename T>
void Vector<T>::set(int i, T value) {
	if (i < _vector.size() - 1)
		throw std::runtime_error("Index out of bounds");
	_vector[i] = &value;
}

template<typename T>
void Vector<T>::setVector(std::vector<T> values) {
	if (values.size() > _vector.size())
		throw std::runtime_error("Index out of bounds");
	for (int i = 0; i < values.size(); i++)
		_vector[i] = &values[i];
}

template<typename T>
T Vector<T>::get(int i) {
	return *_vector[i];
}

template<typename T>
std::vector<T> Vector<T>::getVector() {
	std::vector<T> result;
	for (int i = 0; i < _vector.size(); i++)
		result.push_back(*_vector[i]);
	return result;
}

template<typename T> // FIXME Make this work with reference and value return types
T* Vector<T>::operator[](int i) {
	return _vector[i];
}

// Explicit instantiation of template classes
template class Vector<float> ;
template class Vector<double> ;
template class Vector<long double> ;
template Vector<float>::Vector(Vector<float>);
template Vector<float>::Vector(Vector<double>);
template Vector<float>::Vector(Vector<long double>);
template Vector<double>::Vector(Vector<float>);
template Vector<double>::Vector(Vector<double>);
template Vector<double>::Vector(Vector<long double>);
template Vector<long double>::Vector(Vector<float>);
template Vector<long double>::Vector(Vector<double>);
template Vector<long double>::Vector(Vector<long double>);
