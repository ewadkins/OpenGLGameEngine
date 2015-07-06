/*
 * Drawable.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Drawable.h"

Drawable::Drawable() {
	_transformed = nullptr;
	_drawOutline = true;
	_drawFaces = true;
}

void Drawable::cloneComponents(Drawable* other) {
	_triangles = other->_triangles;
	_lines = other->_lines;
	_points = other->_points;
}

// Updates transformed version of this drawable
void Drawable::applyTransformations() {

	_transformed = clone();

	Matrix<float> rotationMatrix = GLMatrix::rotationMatrixXYZ(getRotationX(),
			getRotationY(), getRotationZ());

	Matrix<float> modelTransformationMatrix = GLMatrix::modelTransformationMatrix(getX(),
			getY(), getZ(), getRotationX(), getRotationY(), getRotationZ(),
			getScaleX(), getScaleY(), getScaleZ());

	for (int i = 0; i < _transformed->_triangles.size(); i++)
		for (int j = 0; j < _transformed->_triangles[i]._vertices.size(); j++)
			_transformed->_triangles[i]._vertices[j].transform(modelTransformationMatrix, rotationMatrix);

	for (int i = 0; i < _transformed->_lines.size(); i++)
		for (int j = 0; j < _transformed->_lines[i]._vertices.size(); j++)
			_transformed->_lines[i]._vertices[j].transform(modelTransformationMatrix, rotationMatrix);

	for (int i = 0; i < _transformed->_points.size(); i++)
		for (int j = 0; j < _transformed->_points[i]._vertices.size(); j++)
			_transformed->_points[i]._vertices[j].transform(modelTransformationMatrix, rotationMatrix);

	_needsUpdating = false;
}

std::vector<GLTriangle> Drawable::getTransformedTriangles() {
	if (_needsUpdating)
		applyTransformations();
	return _transformed->_triangles;
}

std::vector<GLLine> Drawable::getTransformedLines() {
	if (_needsUpdating)
		applyTransformations();
	return _transformed->_lines;
}

std::vector<GLPoint> Drawable::getTransformedPoints() {
	if (_needsUpdating)
		applyTransformations();
	return _transformed->_points;
}

void Drawable::setColor(float r, float g, float b) {
	for (int i = 0; i < _triangles.size(); i++)
		_triangles[i].setColor(r, g, b);
}

void Drawable::setOutlineColor(float r, float g, float b) {
	for (int i = 0; i < _lines.size(); i++)
		_lines[i].setColor(r, g, b);
}

bool Drawable::getDrawFaces() {
	return _drawFaces;
}

void Drawable::setDrawFaces(bool drawFaces) {
	_drawFaces = drawFaces;
}

bool Drawable::getDrawOutline() {
	return _drawOutline;
}

void Drawable::setDrawOutline(bool drawOutline) {
	_drawOutline = drawOutline;
}

