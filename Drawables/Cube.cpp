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

	_face1Tri1 = new GLTriangle(f1t1v1, f1t1v2, f1t1v3);
	_face1Tri2 = new GLTriangle(f1t2v1, f1t2v2, f1t2v3);
	_face2Tri1 = new GLTriangle(f2t1v1, f2t1v2, f2t1v3);
	_face2Tri2 = new GLTriangle(f2t2v1, f2t2v2, f2t2v3);
	_face3Tri1 = new GLTriangle(f3t1v1, f3t1v2, f3t1v3);
	_face3Tri2 = new GLTriangle(f3t2v1, f3t2v2, f3t2v3);
	_face4Tri1 = new GLTriangle(f4t1v1, f4t1v2, f4t1v3);
	_face4Tri2 = new GLTriangle(f4t2v1, f4t2v2, f4t2v3);
	_face5Tri1 = new GLTriangle(f5t1v1, f5t1v2, f5t1v3);
	_face5Tri2 = new GLTriangle(f5t2v1, f5t2v2, f5t2v3);
	_face6Tri1 = new GLTriangle(f6t1v1, f6t1v2, f6t1v3);
	_face6Tri2 = new GLTriangle(f6t2v1, f6t2v2, f6t2v3);

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
}

std::vector<GLTriangle*> Cube::getTriangles() {
	std::vector<GLTriangle*> triangles;
	triangles.push_back(_face1Tri1);
	triangles.push_back(_face1Tri2);
	triangles.push_back(_face2Tri1);
	triangles.push_back(_face2Tri2);
	triangles.push_back(_face3Tri1);
	triangles.push_back(_face3Tri2);
	triangles.push_back(_face4Tri1);
	triangles.push_back(_face4Tri2);
	triangles.push_back(_face5Tri1);
	triangles.push_back(_face5Tri2);
	triangles.push_back(_face6Tri1);
	triangles.push_back(_face6Tri2);
	return triangles;
}

std::vector<GLLine*> Cube::getLines() {
	std::vector<GLLine*> lines;
	lines.push_back(_l1);
	lines.push_back(_l2);
	lines.push_back(_l3);
	lines.push_back(_l4);
	lines.push_back(_l5);
	lines.push_back(_l6);
	lines.push_back(_l7);
	lines.push_back(_l8);
	lines.push_back(_l9);
	lines.push_back(_l10);
	lines.push_back(_l11);
	lines.push_back(_l12);
	return lines;
}

