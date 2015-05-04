/*
 * Triangle.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Triangle.h"

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) {
	_triangle = new GLTriangle(v1, v2, v3);
	_l1 = new GLLine(Vertex(v1.getPosition()), Vertex(v2.getPosition()));
	_l2 = new GLLine(Vertex(v2.getPosition()), Vertex(v3.getPosition()));
	_l3 = new GLLine(Vertex(v3.getPosition()), Vertex(v1.getPosition()));

	_triangles.push_back(_triangle);
	_lines.push_back(_l1);
	_lines.push_back(_l2);
	_lines.push_back(_l3);

	setColor(0.0, 1.0, 0.0);
}

Triangle::Triangle() {
	Vertex v1 = Vertex(0.0, 0.5, 0.0);
	Vertex v2 = Vertex(-0.5, -0.5, 0.0);
	Vertex v3 = Vertex(0.5, -0.5, 0.0);
	_triangle = new GLTriangle(v1, v2, v3);
	_l1 = new GLLine(v1, v2);
	_l2 = new GLLine(v2, v3);
	_l3 = new GLLine(v3, v1);

	_triangles.push_back(_triangle);
	_lines.push_back(_l1);
	_lines.push_back(_l2);
	_lines.push_back(_l3);

	setColor(0.0, 1.0, 0.0);
}

std::vector<GLComponent*> Triangle::getComponents() {
	std::vector<GLComponent*> components;
	for (int i = 0; i < _triangles.size(); i++)
		components.push_back(_triangles[i]);
	for (int i = 0; i < _lines.size(); i++)
		components.push_back(_lines[i]);
	return components;
}

std::vector<GLTriangle*> Triangle::getTransformedTriangles() {
	if (_needsUpdating)
		applyTransformations();
	return ((Triangle*) _transformed)->_triangles;
}

std::vector<GLTriangle*> Triangle::getTriangles() {
	return _triangles;
}

std::vector<GLLine*> Triangle::getTransformedLines() {
	if(_needsUpdating)
		applyTransformations();
	return ((Triangle*) _transformed)->_lines;
}

std::vector<GLLine*> Triangle::getLines() {
	return _lines;
}

Drawable* Triangle::clone() {
	Triangle* d = new Triangle();
	d->_triangle = (GLTriangle*) _triangle->clone();
	d->_l1 = (GLLine*) _l1->clone();
	d->_l2 = (GLLine*) _l2->clone();
	d->_l3 = (GLLine*) _l3->clone();
	return d;
}

