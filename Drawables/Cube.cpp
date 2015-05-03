/*
 * Cube.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Cube.h"

Cube::Cube() {
	// Left
	Vertex* f1t1v1 = new Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f1t1v2 = new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f1t1v3 = new Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f1t2v1 = new Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f1t2v2 = new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f1t2v3 = new Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	// Right
	Vertex* f2t1v1 = new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f2t1v2 = new Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f2t1v3 = new Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f2t2v1 = new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f2t2v2 = new Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f2t2v3 = new Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	// Back
	Vertex* f3t1v1 = new Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f3t1v2 = new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f3t1v3 = new Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f3t2v1 = new Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f3t2v2 = new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f3t2v3 = new Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	// Front
	Vertex* f4t1v1 = new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f4t1v2 = new Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f4t1v3 = new Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f4t2v1 = new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f4t2v2 = new Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f4t2v3 = new Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	// Bottom
	Vertex* f5t1v1 = new Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f5t1v2 = new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f5t1v3 = new Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f5t2v1 = new Vertex(-0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f5t2v2 = new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f5t2v3 = new Vertex(0.5, -0.5, 0.5, 1.0, 0.0, 0.0);
	// Top
	Vertex* f6t1v1 = new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f6t1v2 = new Vertex(-0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f6t1v3 = new Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);
	Vertex* f6t2v1 = new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f6t2v2 = new Vertex(0.5, 0.5, -0.5, 1.0, 0.0, 0.0);
	Vertex* f6t2v3 = new Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0);

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

	_l1 = new GLLine(new Vertex(f1t1v1->getPosition()),
			new Vertex(f1t1v2->getPosition()));
	_l2 = new GLLine(new Vertex(f1t1v2->getPosition()),
			new Vertex(f1t1v3->getPosition()));
	_l3 = new GLLine(new Vertex(f1t2v1->getPosition()),
			new Vertex(f1t2v2->getPosition()));
	_l4 = new GLLine(new Vertex(f1t2v2->getPosition()),
			new Vertex(f1t2v3->getPosition()));
	_l5 = new GLLine(new Vertex(f2t1v1->getPosition()),
			new Vertex(f2t1v2->getPosition()));
	_l6 = new GLLine(new Vertex(f2t1v2->getPosition()),
			new Vertex(f2t1v3->getPosition()));
	_l7 = new GLLine(new Vertex(f2t2v1->getPosition()),
			new Vertex(f2t2v2->getPosition()));
	_l8 = new GLLine(new Vertex(f2t2v2->getPosition()),
			new Vertex(f2t2v3->getPosition()));
	_l9 = new GLLine(new Vertex(f1t1v1->getPosition()),
			new Vertex(f2t1v1->getPosition()));
	_l10 = new GLLine(new Vertex(f1t1v2->getPosition()),
			new Vertex(f2t1v2->getPosition()));
	_l11 = new GLLine(new Vertex(f1t2v2->getPosition()),
			new Vertex(f2t2v2->getPosition()));
	_l12 = new GLLine(new Vertex(f1t2v3->getPosition()),
			new Vertex(f2t2v3->getPosition()));

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
	if(_needsUpdating)
		applyTransformations();
	return ((Cube*) _transformed)->_triangles;
}

std::vector<GLTriangle*> Cube::getTriangles() {
	return _triangles;
}

std::vector<GLLine*> Cube::getTransformedLines() {
	if(_needsUpdating)
		applyTransformations();
	return ((Cube*) _transformed)->_lines;
}

std::vector<GLLine*> Cube::getLines() {
	return _lines;
}

Drawable* Cube::clone() {
	Cube* d = new Cube();
	d->_f1t1 = (GLTriangle*) _f1t1->clone();
	d->_f1t2 = (GLTriangle*) _f1t2->clone();
	d->_f2t1 = (GLTriangle*) _f2t1->clone();
	d->_f2t2 = (GLTriangle*) _f2t2->clone();
	d->_f3t1 = (GLTriangle*) _f3t1->clone();
	d->_f3t2 = (GLTriangle*) _f3t2->clone();
	d->_f4t1 = (GLTriangle*) _f4t1->clone();
	d->_f4t2 = (GLTriangle*) _f4t2->clone();
	d->_f5t1 = (GLTriangle*) _f5t1->clone();
	d->_f5t2 = (GLTriangle*) _f5t2->clone();
	d->_f6t1 = (GLTriangle*) _f6t1->clone();
	d->_f6t2 = (GLTriangle*) _f6t2->clone();
	d->_l1 = (GLLine*) _l1->clone();
	d->_l2 = (GLLine*) _l2->clone();
	d->_l3 = (GLLine*) _l3->clone();
	d->_l4 = (GLLine*) _l4->clone();
	d->_l5 = (GLLine*) _l5->clone();
	d->_l6 = (GLLine*) _l6->clone();
	d->_l7 = (GLLine*) _l7->clone();
	d->_l8 = (GLLine*) _l8->clone();
	d->_l9 = (GLLine*) _l9->clone();
	d->_l10 = (GLLine*) _l10->clone();
	d->_l11 = (GLLine*) _l11->clone();
	d->_l12 = (GLLine*) _l12->clone();
	return d;
}

