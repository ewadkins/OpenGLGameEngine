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
	for (int i = 0; i < size; i++)
		_vector.push_back(0);
}

template<typename T>
Vector<T>::Vector(T v1, T v2) {
	_vector.push_back(v1);
	_vector.push_back(v2);
}

template<typename T>
Vector<T>::Vector(T v1, T v2, T v3) {
	_vector.push_back(v1);
	_vector.push_back(v2);
	_vector.push_back(v3);
}

template<typename T>
Vector<T>::Vector(T v1, T v2, T v3, T v4) {
	_vector.push_back(v1);
	_vector.push_back(v2);
	_vector.push_back(v3);
	_vector.push_back(v4);
}

template<typename T>
Vector<T>::Vector(std::vector<T> vector) {
	_vector = vector;
}

template<typename T>
template<typename S>
Vector<T>::Vector(Vector<S> other) {
	for (int i = 0; i < other.size(); i++)
			_vector[i] = other.get(i);
}

template<typename T>
Vector<T> Vector<T>::scale(T k) {
	Vector<T> result = *this;
	for (int i = 0; i < result._vector.size(); i++)
		result._vector[i] *= k;
	return result;
}

template<typename T>
Vector<T> Vector<T>::add(Vector other) {
	Vector result = Vector<T>(std::max(_vector.size(), other._vector.size()));
	for (int i = 0; i < _vector.size(); i++)
		result._vector[i] = result._vector[i] + _vector[i];
	for (int i = 0; i < other._vector.size(); i++)
		result._vector[i] = result._vector[i] + other._vector[i];
	return result;
}

template<typename T>
T Vector<T>::dot(Vector other) {
	if (_vector.size() != other._vector.size())
		throw std::runtime_error("Vector dimensions don't match");
	T result = 0;
	for (int n = 0; n < _vector.size(); n++)
		result += _vector[n] * other._vector[n];
	return result;
}

template<typename T>
Vector<T> Vector<T>::cross(Vector other) {
	if (_vector.size() != 3 || other._vector.size() != 3)
		throw std::runtime_error("Vector dimensions don't match");
	return Vector<T>(
			_vector[1] * other._vector[2] - _vector[2] * other._vector[1],
			_vector[2] * other._vector[0] - _vector[0] * other._vector[2],
			_vector[0] * other._vector[1] - _vector[1] * other._vector[0]);
}

template<typename T>
T Vector<T>::magnitude() {
	T sum = 0;
	for (int i = 0; i < _vector.size(); i++)
		sum += _vector[i] * _vector[i];
	return std::sqrt(sum);
}

template<typename T>
Vector<T> Vector<T>::normalize() {
	return scale(1 / magnitude());
}

template<typename T>
int Vector<T>::size() {
	return _vector.size();
}

template<typename T>
void Vector<T>::set(int i, T value) {
	if (i < _vector.size() - 1)
		throw std::runtime_error("Index out of bounds");
	_vector[i] = value;
}

template<typename T>
void Vector<T>::setVector(std::vector<T> values) {
	_vector = values;
}

template<typename T>
T Vector<T>::get(int i) {
	return _vector[i];
}

template<typename T>
std::vector<T> Vector<T>::getVector() {
	return _vector;
}

template<typename T>
std::string Vector<T>::toString() {
	std::string str = "Vector(";
	for (int i = 0; i < _vector.size(); i++) {
		if (i != 0)
			str += ", ";
		str += std::to_string(_vector[i]);
	}
	str += ")";
	return str;
}

template<typename T>
T Vector<T>::operator[](int i) {
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
