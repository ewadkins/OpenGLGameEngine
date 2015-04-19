/*
 * GenericPolynomial.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: ericwadkins
 */

#include "GenericPolynomial.h"

template<typename T>
GenericPolynomial<T>::GenericPolynomial() :
		Polynomial<T>() {
}

template<typename T>
GenericPolynomial<T>::GenericPolynomial(std::vector<T> numCoeffs, std::vector<T> denCoeffs) :
		Polynomial<T>(numCoeffs, denCoeffs) {
	simplify();
}

template<typename T>
GenericPolynomial<T>::GenericPolynomial(std::vector<T> numCoeffs, T den) :
		Polynomial<T>(numCoeffs, den) {
	simplify();
}

template<typename T>
GenericPolynomial<T>::GenericPolynomial(std::vector<T> numCoeffs) :
		Polynomial<T>(numCoeffs) {
}

template<typename T>
GenericPolynomial<T>::GenericPolynomial(T num, std::vector<T> denCoeffs) :
		Polynomial<T>(num, denCoeffs) {
	simplify();
}

template<typename T>
GenericPolynomial<T>::GenericPolynomial(T num, T den) :
		Polynomial<T>(num, den) {
	simplify();
}

template<typename T>
GenericPolynomial<T>::GenericPolynomial(T value) :
		Polynomial<T>(value) {
}

template<typename T>
template<typename S>
GenericPolynomial<T>::GenericPolynomial(GenericPolynomial<S> other) :
		Polynomial<T>(other) {
	simplify();
}

template<typename T>
void GenericPolynomial<T>::simplify() {

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
		Polynomial<T>* dividend = new GenericPolynomial(this->_numCoeffs);
		Polynomial<T>* divisor = new GenericPolynomial(this->_denCoeffs);
		Polynomial<T>* result = new GenericPolynomial();
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

			Polynomial<T>* temp = new GenericPolynomial(remainderLead, divisorLead);
			(*result) += (*temp);
			(*remainder) -= ((*temp) * (*divisor));
		}
		if (remainder == 0) {
			this->_numCoeffs = result->getNumCoeffs();
			this->_denCoeffs = result->getDenCoeffs();
		}
	}
}

// Explicit instantiation of template classes
template class GenericPolynomial<int> ;
template class GenericPolynomial<float> ;
template class GenericPolynomial<double> ;
template class GenericPolynomial<long double> ;
