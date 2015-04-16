/*
 * Triangle.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Triangle.h"

Triangle::Triangle(Vertex* v1, Vertex* v2, Vertex* v3) {
	_triangle = new GLTriangle(v1, v2, v3);
	_l1 = new GLLine(new Vertex(v1->getPosition()),
			new Vertex(v2->getPosition()));
	_l2 = new GLLine(new Vertex(v2->getPosition()),
			new Vertex(v3->getPosition()));
	_l3 = new GLLine(new Vertex(v3->getPosition()),
			new Vertex(v1->getPosition()));

	_triangles.push_back(_triangle);
	_lines.push_back(_l1);
	_lines.push_back(_l2);
	_lines.push_back(_l3);
}

Triangle::Triangle() {
	Vertex* t1v1 = new Vertex(0.0, 0.5, 0.0, 0.0, 1.0, 0.0);
	Vertex* t1v2 = new Vertex(-0.5, -0.5, 0.0, 0.0, 1.0, 0.0);
	Vertex* t1v3 = new Vertex(0.5, -0.5, 0.0, 0.0, 1.0, 0.0);
	Vertex* l1v1 = new Vertex(0.0, 0.5, 0.0);
	Vertex* l1v2 = new Vertex(-0.5, -0.5, 0.0);
	Vertex* l1v3 = new Vertex(0.5, -0.5, 0.0);
	_triangle = new GLTriangle(t1v1, t1v2, t1v3);
	_l1 = new GLLine(l1v1, l1v2);
	_l2 = new GLLine(l1v2, l1v3);
	_l3 = new GLLine(l1v3, l1v1);

	_triangles.push_back(_triangle);
	_lines.push_back(_l1);
	_lines.push_back(_l2);
	_lines.push_back(_l3);
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
	if(_needsUpdating)
		applyTransformations();
	std::vector<GLTriangle*> triangles;
	Triangle* transformed = (Triangle*) _transformed;
	for (int i = 0; i < transformed->_triangles.size(); i++)
		triangles.push_back(transformed->_triangles[i]);
	return triangles;
}

std::vector<GLTriangle*> Triangle::getTriangles() {
	return _triangles;
}

std::vector<GLLine*> Triangle::getLines() {
	if(_needsUpdating)
		applyTransformations();
	std::vector<GLLine*> lines;
	if (_drawOutline) {
		Triangle* transformed = (Triangle*) _transformed;
		for (int i = 0; i < transformed->_lines.size(); i++)
			lines.push_back(transformed->_lines[i]);
	}
	return lines;
}

std::vector<GLLine*> Triangle::getTransformedLines() {
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

