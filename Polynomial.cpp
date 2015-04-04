/*
 * Polynomial.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: ericwadkins
 */

#include "Polynomial.h"

template<typename T>
Polynomial<T>::Polynomial() {
    std::vector<T> numCoeffs;
    numCoeffs.push_back(0);
	_numCoeffs = numCoeffs;
    std::vector<T> denCoeffs;
    denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
	trim();
}

template<typename T>
Polynomial<T>::Polynomial(std::vector<T> numCoeffs, std::vector<T> denCoeffs) {
	_numCoeffs = numCoeffs;
	_denCoeffs = denCoeffs;
	trim();
}

template<typename T>
Polynomial<T>::Polynomial(std::vector<T> numCoeffs, T den) {
	_numCoeffs = numCoeffs;
    std::vector<T> denCoeffs;
    denCoeffs.push_back(den);
	_denCoeffs = denCoeffs;
	trim();
}

template<typename T>
Polynomial<T>::Polynomial(T num, std::vector<T> denCoeffs) {
    std::vector<T> numCoeffs;
    numCoeffs.push_back(num);
	_numCoeffs = numCoeffs;
	_denCoeffs = denCoeffs;
	trim();
}

template<typename T>
Polynomial<T>::Polynomial(T num, T den) {
    std::vector<T> numCoeffs;
    numCoeffs.push_back(num);
	_numCoeffs = numCoeffs;
    std::vector<T> denCoeffs;
    denCoeffs.push_back(den);
	_denCoeffs = denCoeffs;
	trim();
}

template<typename T>
template<typename S>
Polynomial<T>::Polynomial(Polynomial<S> other) {
	_numCoeffs = other._numCoeffs;
	_denCoeffs = other._denCoeffs;
}

template<typename T>
T Polynomial<T>::value(T x) {
	T num = 0;
	for (int i = 0; i < _numCoeffs.size(); i++)
		num += _numCoeffs[i] * (std::pow(x, i));
	T den = 0;
	for (int i = 0; i < _denCoeffs.size(); i++)
		den += _denCoeffs[i] * (std::pow(x, i));

	return num / den;
}

template<typename T>
Polynomial<T> Polynomial<T>::add(Polynomial other) {
	Polynomial<T> cd = Polynomial<T>((Polynomial<T>(_denCoeffs, 1) * Polynomial<T>(other._denCoeffs, 1))._numCoeffs, 1);
	Polynomial<T> p1 = Polynomial<T>((Polynomial<T>(_numCoeffs, 1) * Polynomial<T>(other._denCoeffs, 1))._numCoeffs, cd._numCoeffs);
	Polynomial<T> p2 = Polynomial<T>((Polynomial<T>(other._numCoeffs, 1) * Polynomial<T>(_denCoeffs, 1))._numCoeffs, cd._numCoeffs);

	std::vector<T> numCoeffs(std::max(p1._numCoeffs.size(), p2._numCoeffs.size()));
	for (int i = 0; i < p1._numCoeffs.size(); i++)
		numCoeffs[i] += p1._numCoeffs[i];
	for (int i = 0; i < p2._numCoeffs.size(); i++)
		numCoeffs[i] += p2._numCoeffs[i];

	std::vector<T> denCoeffs(std::max(p1._denCoeffs.size(), p2._denCoeffs.size()));
	for (int i = 0; i < p1._denCoeffs.size(); i++)
		denCoeffs[i] += p1._denCoeffs[i];
	for (int i = 0; i < p2._denCoeffs.size(); i++)
		denCoeffs[i] += p2._denCoeffs[i];
	return Polynomial<T>(numCoeffs, denCoeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::mul(T n) {
	std::vector<T> numCoeffs;
	for (int i = 0; i < _numCoeffs.size(); i++)
		numCoeffs.push_back(n * _numCoeffs[i]);
	std::vector<T> denCoeffs;
	for (int i = 0; i < _denCoeffs.size(); i++)
		denCoeffs.push_back(n * _denCoeffs[i]);
	return Polynomial<T>(numCoeffs, denCoeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::mul(Polynomial other) {
    std::vector<T> numCoeffs;
    for (int i = 0; i < _numCoeffs.size(); i++)
        for (int j = 0; j < other._numCoeffs.size(); j++) {
            while(i + j >= numCoeffs.size())
                numCoeffs.push_back(0);
            numCoeffs[i+j] += _numCoeffs[i] * other._numCoeffs[j];
        }
    std::vector<T> denCoeffs;
    for (int i = 0; i < _denCoeffs.size(); i++)
        for (int j = 0; j < other._denCoeffs.size(); j++) {
            while(i + j >= denCoeffs.size())
                denCoeffs.push_back(0);
            denCoeffs[i+j] += _denCoeffs[i] * other._denCoeffs[j];
        }
    return Polynomial<T>(numCoeffs, denCoeffs);
}

template<typename T>
std::vector<T> Polynomial<T>::roots() {
	std::vector<T> result;

	return result;
}

template<typename T>
Polynomial<T> Polynomial<T>::reciprocal() {
	return Polynomial(_denCoeffs, _numCoeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::clone() {
	return Polynomial<T>(_numCoeffs, _denCoeffs);
}

template<typename T>
void Polynomial<T>::print() {
	std::string str = "";
	for (int i = 0; i < _numCoeffs.size(); i++) {
		if (i != 0)
			str += " + ";
		str += trimNumber(std::to_string(_numCoeffs[i]));
		if (i == 1)
			str += "x";
		else if (i > 1)
			str += "x^" + std::to_string(i);
	}
	std::cout << str << std::endl;
}

template<typename T>
std::vector<T> Polynomial<T>::coeffs() {
	return _numCoeffs;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator+(Polynomial rhs) {
	return add(rhs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator-(Polynomial rhs) {
	return add(rhs * -1);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator*(T rhs) {
	return mul(rhs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator*(Polynomial rhs) {
		return mul(rhs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator/(T rhs) {
	return mul(1/rhs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator/(Polynomial rhs) {
		return mul(rhs.reciprocal());
}

template<typename T>
Polynomial<T> Polynomial<T>::operator^(T rhs) {
	Polynomial<T> result = clone();
	int n = std::abs(rhs);
	for (int i = 0; i < n; i++)
		result = result.mul(result);
	if (rhs < 0)
		result = result.reciprocal();
	return result;
}

template<typename T>
void Polynomial<T>::trim() {
	while (_numCoeffs[_numCoeffs.size() - 1] == 0)
		_numCoeffs.pop_back();
}

template<typename T>
std::string Polynomial<T>::trimNumber(std::string str) {
	if (str.find(std::string(".")) != std::string::npos) {
		for (int c = str.length() - 1; c >= 0; c--) {
			if (str.at(c) != '0' || str.at(c - 1) == '.')
				break;
			str = str.substr(0, c);
		}
	}
	return str;
}

// Explicit instantiation of template classes
template class Polynomial<int> ;
template class Polynomial<float> ;
template class Polynomial<double> ;
template class Polynomial<long double> ;
