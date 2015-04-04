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
#include <cmath>
#include <string>

template<typename T>
class Polynomial {
public:
	Polynomial();
	Polynomial(std::vector<T> numCoeffs, std::vector<T> denCoeffs);
	Polynomial(std::vector<T> numCoeffs, T den);
	Polynomial(T num, std::vector<T> denCoeffs);
	Polynomial(T num, T den);
	template<typename S> Polynomial(Polynomial<S> other);
	T value(T x);
	Polynomial add(Polynomial other);
	Polynomial mul(T n);
	Polynomial mul(Polynomial other);
	std::vector<T> roots();
	Polynomial<T> reciprocal();
	Polynomial clone();
	void print();
	std::vector<T> coeffs();
	Polynomial operator+(Polynomial rhs);
	Polynomial operator-(Polynomial rhs);
	Polynomial operator*(T rhs);
	Polynomial operator*(Polynomial rhs);
	Polynomial operator/(T rhs);
	Polynomial operator/(Polynomial rhs);
	//Polynomial operator/(Polynomial rhs);
	Polynomial operator^(T rhs);
private:
	void trim();
	static std::string trimNumber(std::string str);
	std::vector<T> _numCoeffs;
	std::vector<T> _denCoeffs;
};

#endif /* POLYNOMIAL_H_ */
