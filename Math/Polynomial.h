/*
 * Polynomial.h
 *
 *  Created on: Apr 3, 2015
 *      Author: ericwadkins
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include "Complex.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdexcept>

template<typename T>
class Polynomial {
public:
	Polynomial();
	Polynomial(std::vector<T> numCoeffs, std::vector<T> denCoeffs);
	Polynomial(std::vector<T> numCoeffs, T den);
	Polynomial(std::vector<T> numCoeffs);
	Polynomial(T num, std::vector<T> denCoeffs);
	Polynomial(T num, T den);
	Polynomial(T value);
	template<typename S> Polynomial(Polynomial<S> other);
	T value(T x);
	Complex<T> value(Complex<T> x);
	T value();
	Polynomial add(Polynomial other);
	Polynomial mul(T n);
	Polynomial mul(Polynomial other);
	std::vector<Complex<T> > roots();
	Polynomial reciprocal();
	Polynomial clone();
	bool isConstant();
	bool almostEquals(T rhs);
	bool almostEquals(Polynomial rhs);
	bool equals(T rhs);
	bool equals(Polynomial rhs);
	std::string toString();
	void print();
	std::vector<T> getNumCoeffs();
	std::vector<T> getDenCoeffs();
	Polynomial operator+(Polynomial rhs);
	void operator+=(Polynomial rhs);
	Polynomial operator-(Polynomial rhs);
	void operator-=(Polynomial rhs);
	Polynomial operator-();
	Polynomial operator*(T rhs);
	Polynomial operator*(Polynomial rhs);
	void operator*=(T rhs);
	void operator*=(Polynomial rhs);
	Polynomial operator/(T rhs);
	Polynomial operator/(Polynomial rhs);
	void operator/=(T rhs);
	void operator/=(Polynomial rhs);
	Polynomial operator^(T rhs);
	bool operator==(T rhs);
	bool operator==(Polynomial rhs);
	bool operator!=(T rhs);
	bool operator!=(Polynomial rhs);
	void operator=(T rhs);
	void operator=(Polynomial rhs);
	void round();
private:
	void set(T rhs);
	void set(Polynomial other);
	void simplify();
	void removeTrailingZeros();
	void checkZeroDivision();
	void divideOutVariable();
	void simplifyConstant();
	void divideByConstant();
	void polynomialDivision();
	void simplifyIfNumeratorZero();
	static bool almostEqual(T lhs, T rhs);
	static std::string trimNumber(std::string str);
	std::vector<T> _numCoeffs;
	std::vector<T> _denCoeffs;
	static std::string variable;
};

#endif /* POLYNOMIAL_H_ */
