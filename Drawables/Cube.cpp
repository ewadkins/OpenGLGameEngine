/*
 * Cube.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Cube.h"

Cube::Cube() {

	/*GLVertex v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex v2 = GLVertex(-0.5, -0.5, 0.5);
	GLVertex v3 = GLVertex(-0.5, 0.5, -0.5);
	GLVertex v4 = GLVertex(-0.5, 0.5, 0.5);
	GLVertex v5 = GLVertex(0.5, -0.5, -0.5);
	GLVertex v6 = GLVertex(0.5, -0.5, 0.5);
	GLVertex v7 = GLVertex(0.5, 0.5, -0.5);
	GLVertex v8 = GLVertex(0.5, 0.5, 0.5);*/

	GLVertex v1 = GLVertex(-0.5, -0.5, -0.5);
	GLVertex v2 = GLVertex(-0.5, -0.5, 0.5);
	GLVertex v3 = GLVertex(0.5, -0.5, 0.5);
	GLVertex v4 = GLVertex(0.5, -0.5, -0.5);
	GLVertex v5 = GLVertex(-0.5, 0.5, -0.5);
	GLVertex v6 = GLVertex(-0.5, 0.5, 0.5);
	GLVertex v7 = GLVertex(0.5, 0.5, 0.5);
	GLVertex v8 = GLVertex(0.5, 0.5, -0.5);

	_triangles.push_back(GLTriangle(v5, v1, v6));
	_triangles.push_back(GLTriangle(v2, v6, v1));

	_triangles.push_back(GLTriangle(v7, v3, v8));
	_triangles.push_back(GLTriangle(v4, v8, v3));

	_triangles.push_back(GLTriangle(v8, v4, v5));
	_triangles.push_back(GLTriangle(v1, v5, v4));

	_triangles.push_back(GLTriangle(v6, v2, v7));
	_triangles.push_back(GLTriangle(v3, v7, v2));

	_triangles.push_back(GLTriangle(v2, v1, v3));
	_triangles.push_back(GLTriangle(v4, v3, v1));

	_triangles.push_back(GLTriangle(v5, v6, v8));
	_triangles.push_back(GLTriangle(v7, v8, v6));

	_lines.push_back(GLLine(v1, v2));
	_lines.push_back(GLLine(v2, v3));
	_lines.push_back(GLLine(v3, v4));
	_lines.push_back(GLLine(v4, v1));
	_lines.push_back(GLLine(v5, v6));
	_lines.push_back(GLLine(v6, v7));
	_lines.push_back(GLLine(v7, v8));
	_lines.push_back(GLLine(v8, v5));
	_lines.push_back(GLLine(v1, v5));
	_lines.push_back(GLLine(v2, v6));
	_lines.push_back(GLLine(v3, v7));
	_lines.push_back(GLLine(v4, v8));

	setColor(1.0, 0.0, 0.0);
}

Cube::Cube(Cube* other) {
	cloneComponents(other);
}

Drawable* Cube::clone() {
	return new Cube(this);
}

