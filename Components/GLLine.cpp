/*
 * Line.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "../Components/GLLine.h"

int GLLine::_type = GL_LINES;

GLLine::GLLine(GLVertex v1, GLVertex v2) {
	_vertices.push_back(v1);
	_vertices.push_back(v2);
}

GLLine::GLLine() {
}

std::vector<GLVertex> GLLine::getVertices() {
	return _vertices;
}

void GLLine::setVertices(std::vector<GLVertex> vertices) {
	_vertices = vertices;
}

GLLine* GLLine::clone() {
	return new GLLine(_vertices[0], _vertices[1]);
}

