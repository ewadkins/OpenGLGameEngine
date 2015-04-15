/*
 * Line.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "GLLine.h"

int GLLine::type = GL_LINES;

GLLine::GLLine(Vertex* v1, Vertex* v2) {
	_v1 = v1;
	_v2 = v2;
}

std::vector<Vertex*> GLLine::getVertices() {
	std::vector<Vertex*> vertices;
	vertices.push_back(_v1);
	vertices.push_back(_v2);
	return vertices;
}

