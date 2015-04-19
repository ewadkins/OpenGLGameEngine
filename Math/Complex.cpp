/*
 * Complex.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: ericwadkins
 */

#include "Complex.h"

template<typename T>
Complex<T>::Complex() :
		Polynomial<T>() {
}

template<typename T>
Complex<T>::Complex(std::vector<T> numCoeffs, std::vector<T> denCoeffs) :
		Polynomial<T>(numCoeffs, denCoeffs) {
	simplify();
}

template<typename T>
Complex<T>::Complex(std::vector<T> numCoeffs, T den) :
		Polynomial<T>(numCoeffs, den) {
	simplify();
}

template<typename T>
Complex<T>::Complex(std::vector<T> numCoeffs) :
		Polynomial<T>(numCoeffs) {
}

template<typename T>
Complex<T>::Complex(T num, std::vector<T> denCoeffs) :
		Polynomial<T>(num, denCoeffs) {
	simplify();
}

template<typename T>
Complex<T>::Complex(T num, T den) :
		Polynomial<T>(num, den) {
	simplify();
}

template<typename T>
Complex<T>::Complex(T value) :
		Polynomial<T>(value) {
}

template<typename T>
template<typename S>
Complex<T>::Complex(Complex<S> other) :
		Polynomial<T>(other) {
	simplify();
}

template<typename T>
void Complex<T>::simplify() {

	// Check for 0 division
	if (this->_denCoeffs.size() == 1 && this->_denCoeffs[0] == 0)
		throw std::runtime_error("Polynomial division by zero");

	// If any of the ending coefficients are 0, remove that term
	while (this->_numCoeffs.size() > 1 && this->_numCoeffs[this->_numCoeffs.size() - 1] == 0)
		this->_numCoeffs.pop_back();
	while (this->_denCoeffs.size() > 1 && this->_denCoeffs[this->_denCoeffs.size() - 1] == 0)
		this->_denCoeffs.pop_back();

	// If a variable can be factored out of all terms, do this until there is a constant that prevents it
	while (this->_numCoeffs.size() > 1 && this->_denCoeffs.size() > 1 && this->_numCoeffs[0] == 0
			&& this->_denCoeffs[0] == 0) {
		this->_numCoeffs.erase(this->_numCoeffs.begin());
		this->_denCoeffs.erase(this->_denCoeffs.begin());
	}

	// If the numerator and denominator are both constants, set the polynomial to the value/1
	if (this->isConstant() && this->_denCoeffs[0] != 1) {
		this->_numCoeffs[0] = this->value();
		this->_denCoeffs[0] = 1;
		return;
	}

	// If the denominator is just a constant, divide the top by the constant and make the bottom 1
	if (this->_denCoeffs.size() == 1) {
		for (int i = 0; i < this->_numCoeffs.size(); i++)
			this->_numCoeffs[i] *= (1.0 / this->_denCoeffs[0]);
		this->_denCoeffs[0] = 1;
	}

	// If the numerator is 0, regardless of the denominator, set the polynomial to 0/1
	if (this->_numCoeffs.size() == 1 && this->_numCoeffs[0] == 0) {
		std::vector<T> denCoeffs;
		denCoeffs.push_back(1);
		this->_denCoeffs = denCoeffs;
		return;
	}

	// Polynomial long division
	if (this->_denCoeffs.size() > 1 && this->_numCoeffs.size() >= this->_denCoeffs.size()) {
		Polynomial<T>* dividend = new Complex(this->_numCoeffs);
		Polynomial<T>* divisor = new Complex(this->_denCoeffs);
		Polynomial<T>* result = new Complex();
		Polynomial<T>* remainder = dividend;
		while (remainder != 0
				&& remainder->getNumCoeffs().size() >= divisor->getNumCoeffs().size()) {
			std::vector<T> remainderLead;
			for (int i = 0; i < remainder->getNumCoeffs().size() - 1; i++)
				remainderLead.push_back(0);
			remainderLead.push_back(
					remainder->getNumCoeffs()[remainder->getNumCoeffs().size() - 1]);

			std::vector<T> divisorLead;
			for (int i = 0; i < divisor->getNumCoeffs().size() - 1; i++)
				divisorLead.push_back(0);
			divisorLead.push_back(
					divisor->getNumCoeffs()[divisor->getNumCoeffs().size() - 1]);

			Polynomial<T>* temp = new Complex(remainderLead, divisorLead);
			(*result) += (*temp);
			(*remainder) -= ((*temp) * (*divisor));
		}
		if (remainder == 0) {
			this->_numCoeffs = result->getNumCoeffs();
			this->_denCoeffs = result->getDenCoeffs();
		}
	}

	while (this->_numCoeffs.size() > 2)
		this->_numCoeffs[this->_numCoeffs.size() - 3] -= this->_numCoeffs[this->_numCoeffs.size() - 1];
	while (this->_denCoeffs.size() > 2)
		this->_denCoeffs[this->_denCoeffs.size() - 3] -= this->_denCoeffs[this->_denCoeffs.size() - 1];
}

// Explicit instantiation of template classes
template class Complex<int> ;
template class Complex<float> ;
template class Complex<double> ;
template class Complex<long double> ;
