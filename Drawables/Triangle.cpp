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
	_components.push_back(_triangle);
	_components.push_back(_l1);
	_components.push_back(_l2);
	_components.push_back(_l3);
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
	_components.push_back(_triangle);
	_components.push_back(_l1);
	_components.push_back(_l2);
	_components.push_back(_l3);
}

std::vector<GLTriangle*> Triangle::getTriangles() {
	applyTransformations();
	Triangle* transformed = (Triangle*)_transformed;
	std::vector<GLTriangle*> triangles;
	triangles.push_back(transformed->_triangle);
	return triangles;
}

std::vector<GLLine*> Triangle::getLines() {
	applyTransformations();
	Triangle* transformed = (Triangle*)_transformed;
	std::vector<GLLine*> lines;
	lines.push_back(transformed->_l1);
	lines.push_back(transformed->_l2);
	lines.push_back(transformed->_l3);
	return lines;
}

Drawable* Triangle::clone() {
	Triangle* d = new Triangle();
	d->_triangle = (GLTriangle*)_triangle->clone();
	d->_l1 = (GLLine*)_l1->clone();
	d->_l2 = (GLLine*)_l2->clone();
	d->_l3 = (GLLine*)_l3->clone();
	return d;
}

