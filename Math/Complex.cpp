/*
 * Complex.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#include "Complex.h"

template<typename T>
std::string Complex<T>::variable = "i";

template<typename T>
Complex<T>::Complex() {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(0);
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
}

template<typename T>
Complex<T>::Complex(std::vector<T> numCoeffs, std::vector<T> denCoeffs) {
	_numCoeffs = numCoeffs;
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
Complex<T>::Complex(std::vector<T> numCoeffs, T den) {
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(den);
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
Complex<T>::Complex(std::vector<T> numCoeffs) {
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
Complex<T>::Complex(T num, std::vector<T> denCoeffs) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(num);
	_numCoeffs = numCoeffs;
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
Complex<T>::Complex(T num, T den) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(num / den);
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
Complex<T>::Complex(T value) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(value);
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
template<typename S>
Complex<T>::Complex(Complex<S> other) {
	std::vector<T> numCoeffs;
	for (int i = 0; i < other.getNumCoeffs().size(); i++)
		numCoeffs.push_back((T) other.getNumCoeffs()[i]);
	std::vector<T> denCoeffs;
	for (int i = 0; i < other.getDenCoeffs().size(); i++)
		denCoeffs.push_back((T) other.getDenCoeffs()[i]);
	_numCoeffs = numCoeffs;
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
T Complex<T>::value(T x) {
	T num = 0;
	for (int i = 0; i < _numCoeffs.size(); i++)
		num += _numCoeffs[i] * (std::pow(x, i));
	T den = 0;
	for (int i = 0; i < _denCoeffs.size(); i++)
		den += _denCoeffs[i] * (std::pow(x, i));

	return num / den;
}

template<typename T>
T Complex<T>::value() {
	return value(0);
}

template<typename T>
Complex<T> Complex<T>::add(Complex other) {
	if (_denCoeffs != other._denCoeffs) {
		Complex<T> cd =
				Complex<T>(
						(Complex<T>(_denCoeffs, 1)
								* Complex<T>(other._denCoeffs, 1))._numCoeffs,
						1);
		Complex<T> p1 =
				Complex<T>(
						(Complex<T>(_numCoeffs, 1)
								* Complex<T>(other._denCoeffs, 1))._numCoeffs,
						1);
		Complex<T> p2 =
				Complex<T>(
						(Complex<T>(other._numCoeffs, 1)
								* Complex<T>(_denCoeffs, 1))._numCoeffs, 1);

		std::vector<T> numCoeffs(
				std::max(p1._numCoeffs.size(), p2._numCoeffs.size()));
		for (int i = 0; i < p1._numCoeffs.size(); i++)
			numCoeffs[i] += p1._numCoeffs[i];
		for (int i = 0; i < p2._numCoeffs.size(); i++)
			numCoeffs[i] += p2._numCoeffs[i];

		return Complex(numCoeffs, cd._numCoeffs);
	} else {
		std::vector<T> numCoeffs(
				std::max(_numCoeffs.size(), other._numCoeffs.size()));
		for (int i = 0; i < _numCoeffs.size(); i++)
			numCoeffs[i] += _numCoeffs[i];
		for (int i = 0; i < other._numCoeffs.size(); i++)
			numCoeffs[i] += other._numCoeffs[i];

		return Complex(numCoeffs, _denCoeffs);
	}
}

template<typename T>
Complex<T> Complex<T>::mul(T n) {
	std::vector<T> numCoeffs(_numCoeffs.size());
	for (int i = 0; i < _numCoeffs.size(); i++)
		numCoeffs[i] = n * _numCoeffs[i];
	return Complex(numCoeffs, _denCoeffs);
}

template<typename T>
Complex<T> Complex<T>::mul(Complex other) {
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
	return Complex(numCoeffs, denCoeffs);
}

template<typename T>
Complex<T> Complex<T>::reciprocal() {
	return Complex(_denCoeffs, _numCoeffs);
}

template<typename T>
Complex<T> Complex<T>::conjugate() {
	if (_numCoeffs.size() > 2 || _denCoeffs.size() > 1)
		throw std::runtime_error(
				"Must be simplified before the conjugate can be found");
	std::vector<T> numCoeffs = _numCoeffs;
	numCoeffs[1] *= -1;
	std::vector<T> denCoeffs = _denCoeffs;
	return Complex(numCoeffs, denCoeffs);
}

template<typename T>
Complex<T> Complex<T>::clone() {
	Complex<T> result = Complex<T>();
	result._numCoeffs = _numCoeffs;
	result._denCoeffs = _denCoeffs;
	return result;
}

template<typename T>
bool Complex<T>::isConstant() {
	return _numCoeffs.size() == 1 && _denCoeffs.size() == 1 ? true : false;
}

template<typename T>
bool Complex<T>::almostEquals(T rhs) {
	if (isConstant() && almostEqual(value(), rhs))
		return true;

	Complex<T> temp = clone();
	temp.round();

	if (temp.isConstant() && almostEqual(temp.value(), rhs))
		return true;

	return false;
}

template<typename T>
bool Complex<T>::almostEquals(Complex rhs) {
	if (isConstant() && rhs.isConstant())
		return almostEqual(value(), rhs.value());

	Complex<T> temp = clone();
	temp.round();
	rhs.round();

	if (temp._numCoeffs.size() != rhs._numCoeffs.size()
			|| temp._numCoeffs.size() != rhs._numCoeffs.size())
		return false;
	bool result = true;
	for (int i = 0; i < temp._numCoeffs.size(); i++)
		if (!almostEqual(temp._numCoeffs[i], rhs._numCoeffs[i]))
			return false;
	for (int i = 0; i < temp._denCoeffs.size(); i++)
		if (!almostEqual(temp._denCoeffs[i], rhs._denCoeffs[i]))
			return false;

	return result;
}

template<typename T>
bool Complex<T>::almostEqual(T lhs, T rhs) {
	if (lhs == rhs)
		return true;
	T relativeError = std::abs((lhs - rhs) / std::max((T) 1, rhs));
	return relativeError < 1e-5;
}

template<typename T>
bool Complex<T>::equals(T rhs) {
	if (isConstant() && value() == rhs)
		return true;
	return false;
}

template<typename T>
bool Complex<T>::equals(Complex rhs) {
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
std::string Complex<T>::toString() {

	// Whether to display terms in order of decreasing order or increasing order
	const bool decreasingOrder = false;

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
				str1 += variable;
			else if (order > 1)
				str1 += variable + "^" + std::to_string(order);
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
					str2 += variable;
				else if (order > 1)
					str2 += variable + "^" + std::to_string(order);
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
void Complex<T>::print() {
	std::cout << toString() << std::endl;
}

template<typename T>
std::vector<T> Complex<T>::getNumCoeffs() {
	return _numCoeffs;
}

template<typename T>
std::vector<T> Complex<T>::getDenCoeffs() {
	return _denCoeffs;
}

template<typename T>
void Complex<T>::set(T rhs) {
	std::vector<T> numCoeffs;
	numCoeffs.push_back(rhs);
	_numCoeffs = numCoeffs;
	std::vector<T> denCoeffs;
	denCoeffs.push_back(1);
	_denCoeffs = denCoeffs;
	simplify();
}

template<typename T>
void Complex<T>::set(Complex other) {
	/*std::vector<T> numCoeffs;
	 for (int i = 0; i < other._numCoeffs.size(); i++)
	 _numCoeffs[i] = other._numCoeffs[i];
	 std::vector<T> denCoeffs;
	 for (int i = 0; i < other._denCoeffs.size(); i++)
	 _denCoeffs[i] = other._denCoeffs[i];*/
	_numCoeffs = other._numCoeffs;
	_denCoeffs = other._denCoeffs;
	simplify();
}

template<typename T>
void Complex<T>::simplify() {

	//round();

	removeTrailingZeros();
	checkZeroDivision();
	simplifyImaginaryTerms();
	divideOutVariable();
	simplifyConstant();
	divideByConstant();
	complexDivision();
	simplifyIfNumeratorZero();

}

template<typename T>
void Complex<T>::round() {
	// Round numbers with very small errors
	bool changed = false;
	for (int i = 0; i < _numCoeffs.size(); i++) {
		if (_numCoeffs[i] != (int) _numCoeffs[i]
				&& almostEqual(_numCoeffs[i], (int) _numCoeffs[i])) {
			_numCoeffs[i] = (int) _numCoeffs[i];
			changed = true;
		}
		if (_numCoeffs[i] != ((int) _numCoeffs[i]) + 0.5
				&& almostEqual(_numCoeffs[i], ((int) _numCoeffs[i]) + 0.5)) {
			_numCoeffs[i] = ((int) _numCoeffs[i]) + 0.5;
			changed = true;
		}
		if (_numCoeffs[i] != ((int) _numCoeffs[i]) + 1
				&& almostEqual(_numCoeffs[i], ((int) _numCoeffs[i]) + 1)) {
			_numCoeffs[i] = ((int) _numCoeffs[i]) + 1;
			changed = true;
		}
	}
	for (int i = 0; i < _denCoeffs.size(); i++) {
		if (_denCoeffs[i] != (int) _numCoeffs[i]
				&& almostEqual(_denCoeffs[i], (int) _numCoeffs[i])) {
			_denCoeffs[i] = (int) _numCoeffs[i];
			changed = true;
		}
		if (_denCoeffs[i] != ((int) _numCoeffs[i]) + 0.5
				&& almostEqual(_denCoeffs[i], ((int) _numCoeffs[i]) + 0.5)) {
			_denCoeffs[i] = ((int) _numCoeffs[i]) + 0.5;
			changed = true;
		}
		if (_denCoeffs[i] != ((int) _numCoeffs[i]) + 1
				&& almostEqual(_denCoeffs[i], ((int) _numCoeffs[i]) + 1)) {
			_denCoeffs[i] = ((int) _numCoeffs[i]) + 1;
			changed = true;
		}
	}

	if (changed)
		simplify();
}

template<typename T>
void Complex<T>::removeTrailingZeros() {
	// If any of the ending coefficients are 0, remove that term
	while (_numCoeffs.size() > 1 && _numCoeffs[_numCoeffs.size() - 1] == 0)
		_numCoeffs.pop_back();
	while (_denCoeffs.size() > 1 && _denCoeffs[_denCoeffs.size() - 1] == 0)
		_denCoeffs.pop_back();
}

template<typename T>
void Complex<T>::checkZeroDivision() {
	// Check for 0 division
	if (_denCoeffs.size() == 1 && _denCoeffs[0] == 0) {

		std::cout << "Numerator coeffs: ";
		for (int i = 0; i < _numCoeffs.size(); i++)
			std::cout << _numCoeffs[i] << ", ";
		std::cout << std::endl;
		std::cout << "Denominator coeffs: ";
		for (int i = 0; i < _denCoeffs.size(); i++)
			std::cout << _denCoeffs[i] << ", ";
		std::cout << std::endl;

		std::cout << "ZERO DIVISION: " << toString() << std::endl;

		throw std::runtime_error("Complex division by zero");
	}
}

template<typename T>
void Complex<T>::simplifyImaginaryTerms() {
	// Simplifies terms with an exponent greater than 1
	while (_numCoeffs.size() > 2) {
		_numCoeffs[_numCoeffs.size() - 3] -= _numCoeffs[_numCoeffs.size() - 1];
		_numCoeffs.pop_back();
	}
	while (_denCoeffs.size() > 2) {
		_denCoeffs[_denCoeffs.size() - 3] -= _denCoeffs[_denCoeffs.size() - 1];
		_denCoeffs.pop_back();
	}
}

template<typename T>
void Complex<T>::divideOutVariable() {
	// If a variable can be divided out of all terms, do this until there is a constant that prevents it
	while (_numCoeffs.size() > 1 && _denCoeffs.size() > 1 && _numCoeffs[0] == 0
			&& _denCoeffs[0] == 0) {
		_numCoeffs.erase(_numCoeffs.begin());
		_denCoeffs.erase(_denCoeffs.begin());
	}
}

template<typename T>
void Complex<T>::simplifyConstant() {
	// If the numerator and denominator are both constants, set the Complex to the value/1
	if (isConstant() && _denCoeffs[0] != 1) {
		_numCoeffs[0] = value();
		_denCoeffs[0] = 1;
		return;
	}
}

template<typename T>
void Complex<T>::divideByConstant() {
	// If the denominator is just a constant, divide the top by the constant and make the bottom 1
	if (_denCoeffs.size() == 1) {
		for (int i = 0; i < _numCoeffs.size(); i++)
			_numCoeffs[i] *= (1.0 / _denCoeffs[0]);
		_denCoeffs[0] = 1;
	}
}

template<typename T>
void Complex<T>::complexDivision() {
	// Complex number division
	if (_denCoeffs.size() > 1) {
		Complex<T> numerator = Complex(_numCoeffs);
		Complex<T> denominator = Complex(_denCoeffs);
		numerator *= denominator.conjugate();
		denominator *= denominator.conjugate();
		_numCoeffs = numerator._numCoeffs;
		_denCoeffs = denominator._numCoeffs;
	}
}

template<typename T>
void Complex<T>::simplifyIfNumeratorZero() {
	// If the numerator is 0, regardless of the denominator, set the Complex to 0/1
	if (_numCoeffs.size() == 1 && _numCoeffs[0] == 0) {
		std::vector<T> denCoeffs;
		denCoeffs.push_back(1);
		_denCoeffs = denCoeffs;
		return;
	}
}

template<typename T>
Complex<T> Complex<T>::operator+(Complex rhs) {
	return add(rhs);
}

template<typename T>
void Complex<T>::operator+=(Complex rhs) {
	set(add(rhs));
}

template<typename T>
Complex<T> Complex<T>::operator-(Complex rhs) {
	return add(rhs.mul(-1));
}

template<typename T>
void Complex<T>::operator-=(Complex rhs) {
	set(add(rhs.mul(-1)));
}

template<typename T>
Complex<T> Complex<T>::operator-() {
	return mul(-1);
}

template<typename T>
Complex<T> Complex<T>::operator*(T rhs) {
	return mul(rhs);
}

template<typename T>
Complex<T> Complex<T>::operator*(Complex rhs) {
	return mul(rhs);
}

template<typename T>
void Complex<T>::operator*=(T rhs) {
	set(mul(rhs));
}

template<typename T>
void Complex<T>::operator*=(Complex rhs) {
	set(mul(rhs));
}

template<typename T>
Complex<T> Complex<T>::operator/(T rhs) {
	return mul(1 / rhs);
}

template<typename T>
Complex<T> Complex<T>::operator/(Complex rhs) {
	return mul(rhs.reciprocal());
}

/*template<typename T>
 Complex<T> operator/(T lhs, Complex<T> rhs) {
 return rhs.reciprocal().mul(lhs);
 }*/

template<typename T>
void Complex<T>::operator/=(T rhs) {
	set(mul(1 / rhs));
}

template<typename T>
void Complex<T>::operator/=(Complex rhs) {
	set(mul(rhs.reciprocal()));
}

template<typename T>
Complex<T> Complex<T>::operator^(T rhs) {
	Complex<T> result = Complex(1);
	if (rhs == 0)
		return result;
	Complex<T> original = clone();
	int n = std::abs(rhs);
	for (int i = 0; i < n; i++) {
		result.set(result.mul(original));
	}
	if (rhs < 0)
		result.set(result.reciprocal());
	return result;
}

template<typename T>
bool Complex<T>::operator==(T rhs) {
	return equals(rhs);
}

template<typename T>
bool Complex<T>::operator==(Complex rhs) {
	return equals(rhs);
}

template<typename T>
bool Complex<T>::operator!=(T rhs) {
	return !equals(rhs);
}

template<typename T>
bool Complex<T>::operator!=(Complex rhs) {
	return !equals(rhs);
}

template<typename T>
void Complex<T>::operator=(T rhs) {
	set(rhs);
}

template<typename T>
void Complex<T>::operator=(Complex rhs) {
	set(rhs);
}

template<typename T>
std::string Complex<T>::trimNumber(std::string str) {
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
template class Complex<float> ;
template class Complex<double> ;
template class Complex<long double> ;
template Complex<float>::Complex(Complex<float>);
template Complex<float>::Complex(Complex<double>);
template Complex<float>::Complex(Complex<long double>);
template Complex<double>::Complex(Complex<float>);
template Complex<double>::Complex(Complex<double>);
template Complex<double>::Complex(Complex<long double>);
template Complex<long double>::Complex(Complex<float>);
template Complex<long double>::Complex(Complex<double>);
template Complex<long double>::Complex(Complex<long double>);
