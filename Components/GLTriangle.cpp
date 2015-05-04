/*
 * Triangle.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "../Components/GLTriangle.h"

int GLTriangle::_type = GL_TRIANGLES;

GLTriangle::GLTriangle(GLVertex v1, GLVertex v2, GLVertex v3) {
	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);
}

GLTriangle::GLTriangle() {
}

std::vector<GLVertex> GLTriangle::getVertices() {
	return _vertices;
}

void GLTriangle::setVertices(std::vector<GLVertex> vertices) {
	_vertices = vertices;
}

GLTriangle* GLTriangle::clone() {
	return new GLTriangle(_vertices[0], _vertices[1], _vertices[2]);
}

void GLTriangle::useFaceNormal() { // FIXME Finish

}

