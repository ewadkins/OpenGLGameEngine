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

	useFaceNormal();
}

GLTriangle::GLTriangle() {
}

std::vector<GLVertex> GLTriangle::getVertices() {
	return _vertices;
}

void GLTriangle::setVertices(std::vector<GLVertex> vertices) {
	_vertices = vertices;
}

void GLTriangle::useFaceNormal() {
	std::vector<float> pos1 = _vertices[0].getPosition();
	std::vector<float> pos2 = _vertices[1].getPosition();
	std::vector<float> pos3 = _vertices[2].getPosition();
	Vector<float> v1 = Vector<float>(pos2[0] - pos1[0], pos2[1] - pos1[1], pos2[2] - pos1[2]);
	Vector<float> v2 = Vector<float>(pos3[0] - pos1[0], pos3[1] - pos1[1], pos3[2] - pos1[2]);
	Vector<float> normal = v1.cross(v2);
	normal.normalize();
	_vertices[0].setNormal(normal[0], normal[1], normal[2]);
	_vertices[1].setNormal(normal[0], normal[1], normal[2]);
	_vertices[2].setNormal(normal[0], normal[1], normal[2]);
}

