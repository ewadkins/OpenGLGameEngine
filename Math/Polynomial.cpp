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
}

template<typename T>
Polynomial<T>::Polynomial(std::vector<T> numCoeffs, std::vector<T> denCoeffs) {
	_numCoeffs = numCoeffs;
	_denCoeffs = denCoeffs;
}

template<typename T>
Polynomial<T>::Polynomial(std::vector<T> numCoeffs, T den) {
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(den);
	_denCoeffs = denCoeffs;
}

template<typename T>
Polynomial<T>::Polynomial(std::vector<T> numCoeffs) {
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
}

template<typename T>
Polynomial<T>::Polynomial(T num, std::vector<T> denCoeffs) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(num);
	_numCoeffs = numCoeffs;
	_denCoeffs = denCoeffs;
}

template<typename T>
Polynomial<T>::Polynomial(T num, T den) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(num / den);
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
}

template<typename T>
Polynomial<T>::Polynomial(T value) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(value);
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
}

template<typename T>
template<typename S>
Polynomial<T>::Polynomial(Polynomial<S> other) {
	_numCoeffs = other._numCoeffs;
	_denCoeffs = other._denCoeffs;
}

template<typename T>
T Polynomial<T>::value(T x) {
	T num = _numCoeffs[0];
	for (int i = 1; i < _numCoeffs.size(); i++)
		num += _numCoeffs[i] * (std::pow(x, i));
	T den = _denCoeffs[0];
	for (int i = 1; i < _denCoeffs.size(); i++)
		den += _denCoeffs[i] * (std::pow(x, i));

	return num / den;
}

template<typename T>
T Polynomial<T>::value() {
	return value(0);
}

template<typename T>
Polynomial<T> Polynomial<T>::add(Polynomial other) {
	if (_denCoeffs != other._denCoeffs) {
		Polynomial<T> cd = Polynomial<T>(
				(Polynomial<T>(_denCoeffs, 1)
						* Polynomial<T>(other._denCoeffs, 1))._numCoeffs, 1);
		Polynomial<T> p1 = Polynomial<T>(
				(Polynomial<T>(_numCoeffs, 1)
						* Polynomial<T>(other._denCoeffs, 1))._numCoeffs, 1);
		Polynomial<T> p2 = Polynomial<T>(
				(Polynomial<T>(other._numCoeffs, 1)
						* Polynomial<T>(_denCoeffs, 1))._numCoeffs, 1);

		std::vector<T> numCoeffs(
				std::max(p1._numCoeffs.size(), p2._numCoeffs.size()));
		for (int i = 0; i < p1._numCoeffs.size(); i++)
			numCoeffs[i] += p1._numCoeffs[i];
		for (int i = 0; i < p2._numCoeffs.size(); i++)
			numCoeffs[i] += p2._numCoeffs[i];

		return Polynomial<T>(numCoeffs, cd._numCoeffs);
	} else {
		std::vector<T> numCoeffs(
				std::max(_numCoeffs.size(), other._numCoeffs.size()));
		for (int i = 0; i < _numCoeffs.size(); i++)
			numCoeffs[i] += _numCoeffs[i];
		for (int i = 0; i < other._numCoeffs.size(); i++)
			numCoeffs[i] += other._numCoeffs[i];

		return Polynomial<T>(numCoeffs, _denCoeffs);
	}
}

template<typename T>
Polynomial<T> Polynomial<T>::mul(T n) {
	std::vector<T> numCoeffs(_numCoeffs.size());
	for (int i = 0; i < _numCoeffs.size(); i++)
		numCoeffs[i] = n * _numCoeffs[i];
	return Polynomial<T>(numCoeffs, _denCoeffs);
}

template<typename T>
Polynomial<T> Polynomial<T>::mul(Polynomial other) {
	std::vector<T> numCoeffs;
	for (int i = 0; i < _numCoeffs.size(); i++)
		for (int j = 0; j < other._numCoeffs.size(); j++) {
			while (i + j >= numCoeffs.size())
				numCoeffs.push_back(0);
			numCoeffs[i + j] += _numCoeffs[i] * other._numCoeffs[j];
		}
	std::vector<T> denCoeffs;
	for (int i = 0; i < _denCoeffs.size(); i++)
		for (int j = 0; j < other._denCoeffs.size(); j++) {
			while (i + j >= denCoeffs.size())
				denCoeffs.push_back(0);
			denCoeffs[i + j] += _denCoeffs[i] * other._denCoeffs[j];
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
bool Polynomial<T>::isConstant() {
	return _numCoeffs.size() == 1 && _denCoeffs.size() == 1 ? true : false;
}

template<typename T>
bool Polynomial<T>::equals(T rhs) {
	if (isConstant() && value() == rhs)
		return true;
	return false;
}

template<typename T>
bool Polynomial<T>::equals(Polynomial rhs) {
	if (isConstant() && rhs.isConstant())
		return value() == rhs.value();
	if (_numCoeffs.size() != rhs._numCoeffs.size()
			|| _numCoeffs.size() != rhs._numCoeffs.size())
		return false;
	bool result = true;
	for (int i = 0; i < _numCoeffs.size(); i++)
		if (_numCoeffs[i] != rhs._numCoeffs[i])
			return false;
	for (int i = 0; i < _denCoeffs.size(); i++)
		if (_denCoeffs[i] != rhs._denCoeffs[i])
			return false;
	return result;
}

template<typename T>
std::string Polynomial<T>::toString() {

	// Whether to display terms in order of decreasing order or increasing order
	const bool decreasingOrder = true;

	std::vector<T> num = _numCoeffs;
	std::vector<T> den = _denCoeffs;

	std::string str = "";
	std::string str1 = "";
	int numCount = 0;
	for (int i = 0; i < num.size(); i++) {
		int order;
		if (decreasingOrder)
			order = num.size() - (i + 1);
		else
			order = i;
		if (num[order] != 0 || num.size() == 1) {
			if (numCount != 0) {
				if (num[order] > 0)
					str1 += " + ";
				else
					str1 += " - ";
			}
			if (numCount == 0 && num[order] < 0)
				str1 += "-";
			if ((num[order] != 1 && num[order] != -1) || order == 0)
				str1 += trimNumber(std::to_string(std::abs(num[order])));
			if (order == 1)
				str1 += getVariable();
			else if (order > 1)
				str1 += getVariable() + "^" + std::to_string(order);
			numCount++;
		}
	}
	str = str1;

	if (den.size() > 1 || den[0] != 1) {
		if (numCount > 1)
			str1 = "(" + str1 + ")";
		std::string str2 = "";
		int denCount = 0;
		for (int i = 0; i < den.size(); i++) {
			int order;
			if (decreasingOrder)
				order = den.size() - (i + 1);
			else
				order = i;
			if (den[order] != 0 || den.size() == 1) {
				if (denCount != 0) {
					if (den[order] > 0)
						str2 += " + ";
					else
						str2 += " - ";
				}
				if (denCount == 0 && den[order] < 0)
					str2 += "-";
				if ((den[order] != 1 && den[order] != -1) || order == 0)
					str2 += trimNumber(std::to_string(std::abs(den[order])));
				if (order == 1)
					str2 += getVariable();
				else if (order > 1)
					str2 += getVariable() + "^" + std::to_string(order);
				denCount++;
			}
		}
		if (denCount > 1)
			str2 = "(" + str2 += ")";
		str = str1 + "/" + str2;
	}
	return str;
}

template<typename T>
void Polynomial<T>::print() {
	std::cout << toString() << std::endl;
}

template<typename T>
std::vector<T> Polynomial<T>::getNumCoeffs() {
	return _numCoeffs;
}

template<typename T>
std::vector<T> Polynomial<T>::getDenCoeffs() {
	return _numCoeffs;
}

template<typename T>
void Polynomial<T>::set(Polynomial other) {
	/*std::vector<T> numCoeffs;
	 for (int i = 0; i < other._numCoeffs.size(); i++)
	 _numCoeffs[i] = other._numCoeffs[i];
	 std::vector<T> denCoeffs;
	 for (int i = 0; i < other._denCoeffs.size(); i++)
	 _denCoeffs[i] = other._denCoeffs[i];*/
	_numCoeffs = other._numCoeffs;
	_denCoeffs = other._denCoeffs;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator+(Polynomial rhs) {
	return add(rhs);
}

template<typename T>
void Polynomial<T>::operator+=(Polynomial rhs) {
	set(add(rhs));
}

template<typename T>
Polynomial<T> Polynomial<T>::operator-(Polynomial rhs) {
	return add(rhs.mul(-1));
}

template<typename T>
void Polynomial<T>::operator-=(Polynomial rhs) {
	set(add(rhs.mul(-1)));
}

template<typename T>
Polynomial<T> Polynomial<T>::operator-() {
	return mul(-1);
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
void Polynomial<T>::operator*=(T rhs) {
	set(mul(rhs));
}

template<typename T>
void Polynomial<T>::operator*=(Polynomial rhs) {
	set(mul(rhs));
}

template<typename T>
Polynomial<T> Polynomial<T>::operator/(T rhs) {
	return mul(1 / rhs);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator/(Polynomial rhs) {
	return mul(rhs.reciprocal());
}

/*template<typename T>
 Polynomial<T> operator/(T lhs, Polynomial<T> rhs) {
 return rhs.reciprocal().mul(lhs);
 }*/

template<typename T>
void Polynomial<T>::operator/=(T rhs) {
	set(mul(1 / rhs));
}

template<typename T>
void Polynomial<T>::operator/=(Polynomial rhs) {
	set(mul(rhs.reciprocal()));
}

template<typename T>
Polynomial<T> Polynomial<T>::operator^(T rhs) {
	Polynomial<T> result = Polynomial(1);
	if (rhs == 0)
		return result;
	Polynomial<T> original = clone();
	int n = std::abs(rhs);
	for (int i = 0; i < n; i++) {
		result.set(result.mul(original));
	}
	if (rhs < 0)
		result.set(result.reciprocal());
	return result;
}

template<typename T>
bool Polynomial<T>::operator==(T rhs) {
	return equals(rhs);
}

template<typename T>
bool Polynomial<T>::operator==(Polynomial rhs) {
	return equals(rhs);
}

template<typename T>
bool Polynomial<T>::operator!=(T rhs) {
	return !equals(rhs);
}

template<typename T>
bool Polynomial<T>::operator!=(Polynomial rhs) {
	return !equals(rhs);
}

template<typename T>
void Polynomial<T>::operator=(T rhs) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(rhs);
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
}

template<typename T>
void Polynomial<T>::operator=(Polynomial rhs) {
	set(rhs);
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
