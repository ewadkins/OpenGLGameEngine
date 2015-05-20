/*
 * Triangle.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Triangle.h"

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

Triangle::Triangle(GLVertex v1, GLVertex v2, GLVertex v3) {
	_triangles.push_back(GLTriangle(v1, v2, v3));
	_lines.push_back(
			GLLine(GLVertex(v1.getPosition()), GLVertex(v2.getPosition())));
	_lines.push_back(
			GLLine(GLVertex(v2.getPosition()), GLVertex(v3.getPosition())));
	_lines.push_back(
			GLLine(GLVertex(v3.getPosition()), GLVertex(v1.getPosition())));

	if (!v1.hasColor() && !v2.hasColor() && !v3.hasColor())
		setColor(0.0, 1.0, 0.0);

	// Draws normals
	/*GLVertex v10 = _triangles[0]._vertices[0];
	GLVertex v20 = _triangles[0]._vertices[1];
	GLVertex v30 = _triangles[0]._vertices[2];
	GLVertex v12 = GLVertex(v10.getPosition());
	GLVertex v22 = GLVertex(v20.getPosition());
	GLVertex v32 = GLVertex(v30.getPosition());

	float arr[] = { 1, 0, 0 };
	std::vector<float> color(arr, arr + sizeof(arr) / sizeof(arr[0]));

	_lines.push_back(
			GLLine(v12,
					GLVertex(
							(Vector<float>(v10.getPosition()).add(
									Vector<float>(v10.getNormal()))).getVector(), color)));
	_lines.push_back(
			GLLine(v22,
					GLVertex(
							(Vector<float>(v20.getPosition()).add(
									Vector<float>(v20.getNormal()))).getVector(), color)));
	_lines.push_back(
			GLLine(v32,
					GLVertex(
							(Vector<float>(v30.getPosition()).add(
									Vector<float>(v30.getNormal()))).getVector(), color)));*/
}

Triangle::Triangle(Triangle* other) {
	cloneComponents(other);
}

Drawable* Triangle::clone() {
	return new Triangle(this);
}

