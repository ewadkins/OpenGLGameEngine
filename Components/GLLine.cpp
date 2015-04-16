/*
 * Line.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "GLLine.h"

int GLLine::_type = GL_LINES;

GLLine::GLLine(Vertex* v1, Vertex* v2) {
	_vertices = std::vector<Vertex*>(2);
	_vertices[0] = v1;
	_vertices[1] = v2;
}

std::vector<Vertex*> GLLine::getVertices() {
	return _vertices;
}

void GLLine::setVertices(std::vector<Vertex*> vertices) {
	_vertices = vertices;
}

GLComponent* GLLine::clone() {
	return new GLLine(_vertices[0]->clone(), _vertices[1]->clone());
}

