/*
 * GenericPolynomial.h
 *
 *  Created on: Apr 18, 2015
 *      Author: ericwadkins
 */

#ifndef GENERICPOLYNOMIAL_H_
#define GENERICPOLYNOMIAL_H_

#include "Polynomial.h"

template<typename T>
class GenericPolynomial: public Polynomial<T> {
public:
	GenericPolynomial();
	GenericPolynomial(std::vector<T> numCoeffs, std::vector<T> denCoeffs);
	GenericPolynomial(std::vector<T> numCoeffs, T den);
	GenericPolynomial(std::vector<T> numCoeffs);
	GenericPolynomial(T num, std::vector<T> denCoeffs);
	GenericPolynomial(T num, T den);
	GenericPolynomial(T value);
	template<typename S> GenericPolynomial(GenericPolynomial<S> other);
	virtual ~GenericPolynomial() {
	}
protected:
	virtual std::string getVariable() {
		return "x";
	}
private:
	void simplify();
};

#endif /* GENERICPOLYNOMIAL_H_ */
