/*
 * Polynomial.h
 *
 *  Created on: Apr 3, 2015
 *      Author: ericwadkins
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

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
	virtual ~Polynomial() {
	}
	T value(T x);
	T value();
	Polynomial add(Polynomial other);
	Polynomial mul(T n);
	Polynomial mul(Polynomial other);
	std::vector<T> roots();
	Polynomial<T> reciprocal();
	Polynomial clone();
	bool isConstant();
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
	//operator int();
	//operator float();
	//operator double();
	//operator long double();
protected:
	virtual std::string getVariable() {
		return "x";
	}
	std::vector<T> _numCoeffs;
	std::vector<T> _denCoeffs;
	void set(Polynomial other);
	static std::string trimNumber(std::string str);
};

#endif /* POLYNOMIAL_H_ */
