/*
 * Triangle.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "GLTriangle.h"

int GLTriangle::_type = GL_TRIANGLES;

GLTriangle::GLTriangle(GLVertex v1, GLVertex v2, GLVertex v3) {
	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);

	if (!v1.hasNormal() && !v2.hasNormal() && !v3.hasNormal())
		useFaceNormal();
}

GLTriangle::GLTriangle() {
}

Vector<float> GLTriangle::getFaceNormal() {
	std::vector<float> pos1 = _vertices[0].getPosition();
	std::vector<float> pos2 = _vertices[1].getPosition();
	std::vector<float> pos3 = _vertices[2].getPosition();
	Vector<float> v1 = Vector<float>(pos2[0] - pos1[0], pos2[1] - pos1[1], pos2[2] - pos1[2]);
	Vector<float> v2 = Vector<float>(pos3[0] - pos1[0], pos3[1] - pos1[1], pos3[2] - pos1[2]);
	Vector<float> normal = v1.cross(v2);
	normal.normalize();
	return normal;
}

void GLTriangle::useFaceNormal() {
	Vector<float> normal = getFaceNormal();
	_vertices[0].setNormal(normal[0], normal[1], normal[2]);
	_vertices[1].setNormal(normal[0], normal[1], normal[2]);
	_vertices[2].setNormal(normal[0], normal[1], normal[2]);
}

