/*
 * Cube.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Cube.h"

Cube::Cube(Cube* other) {
	_f1t1 = other->_f1t1->clone();
	_f1t2 = other->_f1t2->clone();
	_f2t1 = other->_f2t1->clone();
	_f2t2 = other->_f2t2->clone();
	_f3t1 = other->_f3t1->clone();
	_f3t2 = other->_f3t2->clone();
	_f4t1 = other->_f4t1->clone();
	_f4t2 = other->_f4t2->clone();
	_f5t1 = other->_f5t1->clone();
	_f5t2 = other->_f5t2->clone();
	_f6t1 = other->_f6t1->clone();
	_f6t2 = other->_f6t2->clone();
	_l1 = other->_l1->clone();
	_l2 = other->_l2->clone();
	_l3 = other->_l3->clone();
	_l4 = other->_l4->clone();
	_l5 = other->_l5->clone();
	_l6 = other->_l6->clone();
	_l7 = other->_l7->clone();
	_l8 = other->_l8->clone();
	_l9 = other->_l9->clone();
	_l10 = other->_l10->clone();
	_l11 = other->_l11->clone();
	_l12 = other->_l12->clone();

	_triangles.push_back(_f1t1);
	_triangles.push_back(_f1t2);
	_triangles.push_back(_f2t1);
	_triangles.push_back(_f2t2);
	_triangles.push_back(_f3t1);
	_triangles.push_back(_f3t2);
	_triangles.push_back(_f4t1);
	_triangles.push_back(_f4t2);
	_triangles.push_back(_f5t1);
	_triangles.push_back(_f5t2);
	_triangles.push_back(_f6t1);
	_triangles.push_back(_f6t2);

	_lines.push_back(_l1);
	_lines.push_back(_l2);
	_lines.push_back(_l3);
	_lines.push_back(_l4);
	_lines.push_back(_l5);
	_lines.push_back(_l6);
	_lines.push_back(_l7);
	_lines.push_back(_l8);
	_lines.push_back(_l9);
	_lines.push_back(_l10);
	_lines.push_back(_l11);
	_lines.push_back(_l12);
}

Cube::Cube() {
	// Left
	Vertex f1t1v1 = Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f1t1v2 = Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f1t1v3 = Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f1t2v1 = Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f1t2v2 = Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f1t2v3 = Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	// Right
	Vertex f2t1v1 = Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f2t1v2 = Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f2t1v3 = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f2t2v1 = Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f2t2v2 = Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f2t2v3 = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	// Back
	Vertex f3t1v1 = Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f3t1v2 = Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f3t1v3 = Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f3t2v1 = Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f3t2v2 = Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f3t2v3 = Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	// Front
	Vertex f4t1v1 = Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f4t1v2 = Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f4t1v3 = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f4t2v1 = Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f4t2v2 = Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f4t2v3 = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	// Bottom
	Vertex f5t1v1 = Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f5t1v2 = Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f5t1v3 = Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f5t2v1 = Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f5t2v2 = Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f5t2v3 = Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	// Top
	Vertex f6t1v1 = Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f6t1v2 = Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f6t1v3 = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex f6t2v1 = Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f6t2v2 = Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex f6t2v3 = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);

	_f1t1 = new GLTriangle(f1t1v1, f1t1v2, f1t1v3);
	_f1t2 = new GLTriangle(f1t2v1, f1t2v2, f1t2v3);
	_f2t1 = new GLTriangle(f2t1v1, f2t1v2, f2t1v3);
	_f2t2 = new GLTriangle(f2t2v1, f2t2v2, f2t2v3);
	_f3t1 = new GLTriangle(f3t1v1, f3t1v2, f3t1v3);
	_f3t2 = new GLTriangle(f3t2v1, f3t2v2, f3t2v3);
	_f4t1 = new GLTriangle(f4t1v1, f4t1v2, f4t1v3);
	_f4t2 = new GLTriangle(f4t2v1, f4t2v2, f4t2v3);
	_f5t1 = new GLTriangle(f5t1v1, f5t1v2, f5t1v3);
	_f5t2 = new GLTriangle(f5t2v1, f5t2v2, f5t2v3);
	_f6t1 = new GLTriangle(f6t1v1, f6t1v2, f6t1v3);
	_f6t2 = new GLTriangle(f6t2v1, f6t2v2, f6t2v3);

	_l1 = new GLLine(f1t1v1, f1t1v2);
	_l2 = new GLLine(f1t1v2, f1t1v3);
	_l3 = new GLLine(f1t2v1, f1t2v2);
	_l4 = new GLLine(f1t2v2, f1t2v3);
	_l5 = new GLLine(f2t1v1, f2t1v2);
	_l6 = new GLLine(f2t1v2, f2t1v3);
	_l7 = new GLLine(f2t2v1, f2t2v2);
	_l8 = new GLLine(f2t2v2, f2t2v3);
	_l9 = new GLLine(f1t1v1, f2t1v1);
	_l10 = new GLLine(f1t1v2, f2t1v2);
	_l11 = new GLLine(f1t2v2, f2t2v2);
	_l12 = new GLLine(f1t2v3, f2t2v3);

	_triangles.push_back(_f1t1);
	_triangles.push_back(_f1t2);
	_triangles.push_back(_f2t1);
	_triangles.push_back(_f2t2);
	_triangles.push_back(_f3t1);
	_triangles.push_back(_f3t2);
	_triangles.push_back(_f4t1);
	_triangles.push_back(_f4t2);
	_triangles.push_back(_f5t1);
	_triangles.push_back(_f5t2);
	_triangles.push_back(_f6t1);
	_triangles.push_back(_f6t2);

	_lines.push_back(_l1);
	_lines.push_back(_l2);
	_lines.push_back(_l3);
	_lines.push_back(_l4);
	_lines.push_back(_l5);
	_lines.push_back(_l6);
	_lines.push_back(_l7);
	_lines.push_back(_l8);
	_lines.push_back(_l9);
	_lines.push_back(_l10);
	_lines.push_back(_l11);
	_lines.push_back(_l12);
}

std::vector<GLComponent*> Cube::getComponents() {
	std::vector<GLComponent*> components;
	for (int i = 0; i < _triangles.size(); i++)
		components.push_back(_triangles[i]);
	for (int i = 0; i < _lines.size(); i++)
		components.push_back(_lines[i]);
	return components;
}

std::vector<GLTriangle*> Cube::getTransformedTriangles() {
	if (_needsUpdating)
		applyTransformations();
	return _transformed->_triangles;
}

std::vector<GLTriangle*> Cube::getTriangles() {
	return _triangles;
}

std::vector<GLLine*> Cube::getTransformedLines() {
	if (_needsUpdating)
		applyTransformations();
	return _transformed->_lines;
}

std::vector<GLLine*> Cube::getLines() {
	return _lines;
}

void Cube::setTransformed(Drawable* transformed) {
	_transformed = (Cube*) transformed;
}

Drawable* Cube::clone() {
	return new Cube(this);
}

