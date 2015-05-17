/*
 * Line.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "GLLine.h"

int GLLine::_type = GL_LINES;

GLLine::GLLine(GLVertex v1, GLVertex v2) {
	_vertices.push_back(v1);
	_vertices.push_back(v2);
}

GLLine::GLLine() {
}

