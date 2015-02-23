/*
 * Logger.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: ericwadkins
 */

#include "Logger.h"
#include "OpenGLApplication.h"

Logger::Logger() {
	newLine = true;
	numIndents = 0;
	indentString = "    ";
	_log.push_back(std::string(""));
}

Logger& Logger::log(std::string str) {
	if(newLine)
		str = indent(str);
	_log[_log.size() - 1] += str;
	std::cout << str << std::flush;
	return *this;
}

/*template<typename T>
Logger& Logger::log(T t) {
	return log(std::to_string(t));
}*/

Logger& Logger::log(const char* c) {
	return log(std::string(c));
}

Logger& Logger::log(const unsigned char* c) {
	return log(std::string(reinterpret_cast<const char*>(c)));
}

Logger& Logger::log(const int i) {
	return log(std::to_string(i));
}

Logger& Logger::log(const float f) {
	return log(std::to_string(f));
}

Logger& Logger::log(const double d) {
	return log(std::to_string(d));
}

Logger& Logger::log(const long l) {
	return log(std::to_string(l));
}

Logger& Logger::endLine() {
	_log.push_back(std::string(""));
	newLine = true;
	std::cout << std::endl;
	return *this;
}

Logger& Logger::increaseIndent() {
	numIndents++;
	return *this;
}

Logger& Logger::decreaseIndent() {
	if(numIndents > 0)
		numIndents--;
	return *this;
}

std::string Logger::indent(std::string str) {
	for(int i = 0; i < numIndents; i++)
		str = indentString + str;
	newLine = false;
	return str;
}

Logger& Logger::clear() {
	_log.empty();
	return *this;
}

std::vector<std::string> Logger::getLog() {
	return _log;
}

