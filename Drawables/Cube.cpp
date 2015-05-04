/*
 * Cube.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Cube.h"

Cube::Cube() {
	// Left
	GLVertex f1t1v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex f1t1v2 = GLVertex(-0.5, -0.5, 0.5);
	GLVertex f1t1v3 = GLVertex(-0.5, 0.5, 0.5);
	GLVertex f1t2v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex f1t2v2 = GLVertex(-0.5, 0.5, -0.5);
	GLVertex f1t2v3 = GLVertex(-0.5, 0.5, 0.5);
	// Right
	GLVertex f2t1v1 = GLVertex(0.5, -0.5, -0.5);
	GLVertex f2t1v2 = GLVertex(0.5, -0.5, 0.5);
	GLVertex f2t1v3 = GLVertex(0.5, 0.5, 0.5);
	GLVertex f2t2v1 = GLVertex(0.5, -0.5, -0.5);
	GLVertex f2t2v2 = GLVertex(0.5, 0.5, -0.5);
	GLVertex f2t2v3 = GLVertex(0.5, 0.5, 0.5);
	// Back
	GLVertex f3t1v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex f3t1v2 = GLVertex(0.5, -0.5, -0.5);
	GLVertex f3t1v3 = GLVertex(0.5, 0.5, -0.5);
	GLVertex f3t2v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex f3t2v2 = GLVertex(-0.5, 0.5, -0.5);
	GLVertex f3t2v3 = GLVertex(0.5, 0.5, -0.5);
	// Front
	GLVertex f4t1v1 = GLVertex(-0.5, -0.5, 0.5);
	GLVertex f4t1v2 = GLVertex(0.5, -0.5, 0.5);
	GLVertex f4t1v3 = GLVertex(0.5, 0.5, 0.5);
	GLVertex f4t2v1 = GLVertex(-0.5, -0.5, 0.5);
	GLVertex f4t2v2 = GLVertex(-0.5, 0.5, 0.5);
	GLVertex f4t2v3 = GLVertex(0.5, 0.5, 0.5);
	// Bottom
	GLVertex f5t1v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex f5t1v2 = GLVertex(-0.5, -0.5, 0.5);
	GLVertex f5t1v3 = GLVertex(0.5, -0.5, 0.5);
	GLVertex f5t2v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex f5t2v2 = GLVertex(0.5, -0.5, -0.5);
	GLVertex f5t2v3 = GLVertex(0.5, -0.5, 0.5);
	// Top
	GLVertex f6t1v1 = GLVertex(-0.5, 0.5, -0.5);
	GLVertex f6t1v2 = GLVertex(-0.5, 0.5, 0.5);
	GLVertex f6t1v3 = GLVertex(0.5, 0.5, 0.5);
	GLVertex f6t2v1 = GLVertex(-0.5, 0.5, -0.5);
	GLVertex f6t2v2 = GLVertex(0.5, 0.5, -0.5);
	GLVertex f6t2v3 = GLVertex(0.5, 0.5, 0.5);

	_triangles.push_back(GLTriangle(f1t1v1, f1t1v2, f1t1v3));
	_triangles.push_back(GLTriangle(f1t2v1, f1t2v2, f1t2v3));
	_triangles.push_back(GLTriangle(f2t1v1, f2t1v2, f2t1v3));
	_triangles.push_back(GLTriangle(f2t2v1, f2t2v2, f2t2v3));
	_triangles.push_back(GLTriangle(f3t1v1, f3t1v2, f3t1v3));
	_triangles.push_back(GLTriangle(f3t2v1, f3t2v2, f3t2v3));
	_triangles.push_back(GLTriangle(f4t1v1, f4t1v2, f4t1v3));
	_triangles.push_back(GLTriangle(f4t2v1, f4t2v2, f4t2v3));
	_triangles.push_back(GLTriangle(f5t1v1, f5t1v2, f5t1v3));
	_triangles.push_back(GLTriangle(f5t2v1, f5t2v2, f5t2v3));
	_triangles.push_back(GLTriangle(f6t1v1, f6t1v2, f6t1v3));
	_triangles.push_back(GLTriangle(f6t2v1, f6t2v2, f6t2v3));

	_lines.push_back(GLLine(f1t1v1, f1t1v2));
	_lines.push_back(GLLine(f1t1v2, f1t1v3));
	_lines.push_back(GLLine(f1t2v1, f1t2v2));
	_lines.push_back(GLLine(f1t2v2, f1t2v3));
	_lines.push_back(GLLine(f2t1v1, f2t1v2));
	_lines.push_back(GLLine(f2t1v2, f2t1v3));
	_lines.push_back(GLLine(f2t2v1, f2t2v2));
	_lines.push_back(GLLine(f2t2v2, f2t2v3));
	_lines.push_back(GLLine(f1t1v1, f2t1v1));
	_lines.push_back(GLLine(f1t1v2, f2t1v2));
	_lines.push_back(GLLine(f1t2v2, f2t2v2));
	_lines.push_back(GLLine(f1t2v3, f2t2v3));

	setColor(1.0, 0.0, 0.0);
}

Cube::Cube(Cube* other) {
	for (int i = 0; i < other->_triangles.size(); i++)
		_triangles.push_back(other->_triangles[i]);
	for (int i = 0; i < other->_lines.size(); i++)
		_lines.push_back(other->_lines[i]);
}

Drawable* Cube::clone() {
	return new Cube(this);
}

