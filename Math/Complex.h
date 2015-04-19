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
	Complex<T> reciprocal();
	Complex clone();
	bool isConstant();
	bool equals(T rhs);
	bool equals(Complex rhs);
	std::string toString();
	void print();
	std::vector<T> coeffs();
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
	//operator int();
	//operator float();
	//operator double();
	//operator long double();
private:
	void set(Complex other);
	void simplify();
	static std::string trimNumber(std::string str);
	std::vector<T> _numCoeffs;
	std::vector<T> _denCoeffs;
	static std::string variable;
};

#endif /* COMPLEX_H_ */
