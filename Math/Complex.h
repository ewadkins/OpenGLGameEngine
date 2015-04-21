/*
 * Complex.h
 *
 *  Created on: Apr 19, 2015
 *      Author: ericwadkins
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdexcept>

template<typename T>
class Complex {
public:
	Complex();
	Complex(std::vector<T> numCoeffs, std::vector<T> denCoeffs);
	Complex(std::vector<T> numCoeffs, T den);
	Complex(std::vector<T> numCoeffs);
	Complex(T num, std::vector<T> denCoeffs);
	Complex(T num, T den);
	Complex(T value);
	template<typename S> Complex(Complex<S> other);
	T value(T x);
	T value();
	Complex add(Complex other);
	Complex mul(T n);
	Complex mul(Complex other);
	Complex reciprocal();
	Complex conjugate();
	Complex clone();
	bool isConstant();
	bool almostEquals(T rhs);
	bool almostEquals(Complex rhs);
	bool equals(T rhs);
	bool equals(Complex rhs);
	std::string toString();
	void print();
	std::vector<T> getNumCoeffs();
	std::vector<T> getDenCoeffs();
	Complex operator+(Complex rhs);
	void operator+=(Complex rhs);
	Complex operator-(Complex rhs);
	void operator-=(Complex rhs);
	Complex operator-();
	Complex operator*(T rhs);
	Complex operator*(Complex rhs);
	void operator*=(T rhs);
	void operator*=(Complex rhs);
	Complex operator/(T rhs);
	Complex operator/(Complex rhs);
	void operator/=(T rhs);
	void operator/=(Complex rhs);
	Complex operator^(T rhs);
	bool operator==(T rhs);
	bool operator==(Complex rhs);
	bool operator!=(T rhs);
	bool operator!=(Complex rhs);
	void operator=(T rhs);
	void operator=(Complex rhs);
	void round();
private:
	void set(T rhs);
	void set(Complex other);
	void simplify();
	void removeTrailingZeros();
	void checkZeroDivision();
	void simplifyImaginaryTerms();
	void divideOutVariable();
	void simplifyConstant();
	void divideByConstant();
	void complexDivision();
	void simplifyIfNumeratorZero();
	static bool almostEqual(T lhs, T rhs);
	static std::string trimNumber(std::string str);
	std::vector<T> _numCoeffs;
	std::vector<T> _denCoeffs;
	static std::string variable;
};

#endif /* COMPLEX_H_ */
