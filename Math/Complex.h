/*
 * Complex.h
 *
 *  Created on: Apr 18, 2015
 *      Author: ericwadkins
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

#include "Polynomial.h"

template<typename T>
class Complex: public Polynomial<T> {
public:
	Complex();
	Complex(std::vector<T> numCoeffs, std::vector<T> denCoeffs);
	Complex(std::vector<T> numCoeffs, T den);
	Complex(std::vector<T> numCoeffs);
	Complex(T num, std::vector<T> denCoeffs);
	Complex(T num, T den);
	Complex(T value);
	template<typename S> Complex(Complex<S> other);
	virtual ~Complex() {
	}
protected:
	virtual std::string getVariable() {
		return "i";
	}
private:
	void simplify();
};

#endif /* COMPLEX_H_ */
