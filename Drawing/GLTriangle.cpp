/*
 * Triangle.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "GLTriangle.h"

int GLTriangle::type = GL_TRIANGLES;

GLTriangle::GLTriangle(Vertex* v1, Vertex* v2, Vertex* v3) {
	_v1 = v1;
	_v2 = v2;
	_v3 = v3;
}

std::vector<Vertex*> GLTriangle::getVertices() {
	std::vector<Vertex*> vertices;
	vertices.push_back(_v1);
	vertices.push_back(_v2);
	vertices.push_back(_v3);
	return vertices;
}

