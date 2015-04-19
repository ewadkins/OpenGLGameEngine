/*
 * Logger.h
 *
 *  Created on: Feb 21, 2015
 *      Author: ericwadkins
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Math/Matrix.h"
#include "Math/Polynomial.h"
#include "Math/Complex.h"
#include <vector>
#include <string>
#include <iostream>

class Logger {
public:
	Logger();
	virtual ~Logger() {
	}
	Logger& log(const std::string str);
	Logger& log(const std::vector<std::string> strings);
	//template<typename T>
	//Logger& log(const T t);
	Logger& log(const char* c);
	Logger& log(const unsigned char* c);
	Logger& log(const int i);
	Logger& log(const float f);
	Logger& log(const double d);
	Logger& log(const long l);
	template<typename T> Logger& log(Matrix<T> m);
	template<typename T> Logger& log(Polynomial<T> p);
	template<typename T> Logger& log(Complex<T> c);
	Logger& endLine();
	Logger& increaseIndent();
	Logger& decreaseIndent();
	Logger& setIndent(int i);
	Logger& clear();
	std::vector<std::string> getLog();
private:
	std::string indent(std::string str);
	std::string trimNumber(std::string str);
	std::vector<std::string> _log;
	bool newLine;
	unsigned int numIndents;
	std::string indentString;
};

#endif /* LOGGER_H_ */
