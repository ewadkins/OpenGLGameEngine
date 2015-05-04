/*
 * Triangle.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "../Components/GLTriangle.h"

int GLTriangle::_type = GL_TRIANGLES;

GLTriangle::GLTriangle(Vertex v1, Vertex v2, Vertex v3) {
	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);
}

std::vector<Vertex> GLTriangle::getVertices() {
	return _vertices;
}

void GLTriangle::setVertices(std::vector<Vertex> vertices) {
	_vertices = vertices;
}

GLComponent* GLTriangle::clone() {
	return new GLTriangle(_vertices[0], _vertices[1], _vertices[2]);
}

void GLTriangle::useFaceNormal() { // FIXME Finish

}

