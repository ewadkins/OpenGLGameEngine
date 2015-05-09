/*
 * Logger.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: ericwadkins
 */

#include "Logger.h"

#include "Application.h"

Logger::Logger() {
	newLine = true;
	numIndents = 0;
	indentString = "  ";
	_log.push_back(std::string(""));
}

// Logs a string, adding an indent if at the start of a new line
Logger& Logger::log(std::string str) {
	if (newLine)
		str = indent(str);
	_log[_log.size() - 1] += str;
	std::cout << str << std::flush;
	return *this;
}

Logger& Logger::log(std::vector<std::string> strings) {
	for (int i = 0; i < strings.size(); i++)
		log(strings[i]).endLine();
	return *this;
}

/*template<typename T>
 Logger& Logger::log(T t) {
 return log(std::to_string(t));
 }*/

// Logs a character array
Logger& Logger::log(const char* c) {
	return log(std::string(c));
}

// Logs an unsigned character array, possibly unsafe conversion
Logger& Logger::log(const unsigned char* c) {
	return log(std::string(reinterpret_cast<const char*>(c)));
}

// Logs an int
Logger& Logger::log(const int i) {
	return log(std::to_string(i));
}

// Logs a float
Logger& Logger::log(const float f) {
	return log(trimNumber(std::to_string(f)));
}

// Logs a double
Logger& Logger::log(const double d) {
	return log(trimNumber(std::to_string(d)));
}

// Logs a long
Logger& Logger::log(const long l) {
	return log(std::to_string(l));
}

// Logs a Matrix
template<typename T>
Logger& Logger::log(Matrix<T> m) {
	return log(m.toStringVector());
}

// Logs a Polynomial
template<typename T>
Logger& Logger::log(Polynomial<T> p) {
	return log(p.toString());
}

// Logs a Complex
template<typename T>
Logger& Logger::log(Complex<T> c) {
	return log(c.toString());
}

// Creates a new line
Logger& Logger::endLine() {
	_log.push_back(std::string(""));
	newLine = true;
	std::cout << std::endl;
	return *this;
}

// Increases the number of indents
Logger& Logger::increaseIndent() {
	numIndents++;
	return *this;
}

// Decreases the number of indents
Logger& Logger::decreaseIndent() {
	if (numIndents > 0)
		numIndents--;
	return *this;
}

// Sets the number of indents
Logger& Logger::setIndent(int i) {
	numIndents = i;
	return *this;
}

// Adds indents to the string
std::string Logger::indent(std::string str) {
	for (int i = 0; i < numIndents; i++)
		str = indentString + str;
	newLine = false;
	return str;
}

// Trims the excess zeros off decimals
std::string Logger::trimNumber(std::string str) {
	if (str.find(std::string(".")) != std::string::npos) {
		for (int c = str.length() - 1; c >= 0; c--) {
			if (str.at(c) != '0' || str.at(c - 1) == '.')
				break;
			str = str.substr(0, c);
		}
	}
	return str;
}

// Clears the log of all entries
Logger& Logger::clear() {
	_log.empty();
	return *this;
}

// Returns a copy of the log
std::vector<std::string> Logger::getLog() {
	return _log;
}

// Explicit instantiation of template functions
template Logger& Logger::log(Matrix<float>);
template Logger& Logger::log(Matrix<double>);
template Logger& Logger::log(Matrix<long double>);
template Logger& Logger::log(Polynomial<float>);
template Logger& Logger::log(Polynomial<double>);
template Logger& Logger::log(Polynomial<long double>);
template Logger& Logger::log(Complex<float>);
template Logger& Logger::log(Complex<double>);
template Logger& Logger::log(Complex<long double>);

