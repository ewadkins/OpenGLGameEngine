/*
 * Triangle.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Triangle.h"

Triangle::Triangle(GLVertex v1, GLVertex v2, GLVertex v3) {
	_triangles.push_back(GLTriangle(v1, v2, v3));
	_lines.push_back(GLLine(GLVertex(v1.getPosition()), GLVertex(v2.getPosition())));
	_lines.push_back(GLLine(GLVertex(v2.getPosition()), GLVertex(v3.getPosition())));
	_lines.push_back(GLLine(GLVertex(v3.getPosition()), GLVertex(v1.getPosition())));

	setColor(0.0, 1.0, 0.0);
}

Triangle::Triangle(Triangle* other) {
	for (int i = 0; i < other->_triangles.size(); i++)
		_triangles.push_back(other->_triangles[i]);
	for (int i = 0; i < other->_lines.size(); i++)
		_lines.push_back(other->_lines[i]);
}

Triangle::Triangle() {
	GLVertex v1 = GLVertex(0.0, 0.5, 0.0);
	GLVertex v2 = GLVertex(-0.5, -0.5, 0.0);
	GLVertex v3 = GLVertex(0.5, -0.5, 0.0);

	_triangles.push_back(GLTriangle(v1, v2, v3));
	_lines.push_back(GLLine(v1, v2));
	_lines.push_back(GLLine(v2, v3));
	_lines.push_back(GLLine(v3, v1));

	setColor(0.0, 1.0, 0.0);
}

Drawable* Triangle::clone() {
	return new Triangle(this);
}

