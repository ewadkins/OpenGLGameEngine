/*
 * Drawable.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#include "Drawable.h"

Drawable::Drawable() {
	_x = 0;
	_y = 0;
	_z = 0;
	_scaleX = 1;
	_scaleY = 1;
	_scaleZ = 1;
	_rotationX = 0;
	_rotationY = 0;
	_rotationZ = 0;
	_needsUpdating = true;
	_drawOutline = true;
}

// Returns a transformed version of this drawable
void Drawable::applyTransformations() {

	Drawable* transformed = clone();

	std::vector<GLComponent*> originalComponents = getComponents();
	std::vector<GLComponent*> transformedComponents = transformed->getComponents();

	Matrix<float> scalarMatrix = GLMatrix::scalarMatrix(getScaleX(),
			getScaleY(), getScaleZ());
	Matrix<float> rotationMatrix = GLMatrix::rotationMatrixXYZ(getRotationX(),
			getRotationY(), getRotationZ());
	Matrix<float> translationMatrix = GLMatrix::translationMatrix(getX(),
			getY(), getZ());
	Matrix<float> originalMatrix = Matrix<float>(4, 1);

	std::vector<Vertex> originalVertices;
	std::vector<Vertex> transformedVertices;

	Vertex transformedVertex;
	Matrix<float> transformedMatrix(4);
	std::vector<float> pos;
	std::vector<float> norm;

	for (int i = 0; i < originalComponents.size(); i++) {
		originalVertices = originalComponents[i]->getVertices();
		transformedVertices.clear();

		for (int j = 0; j < originalVertices.size(); j++) {
			transformedVertex = originalVertices[j];

			// Applies transformations to the vertex's position
			pos = transformedVertex.getPosition();
			pos.push_back(1);
			originalMatrix.setVector(pos);

			transformedMatrix = originalMatrix << scalarMatrix
					<< rotationMatrix << translationMatrix;
			transformedVertex.setPosition(transformedMatrix.get(0, 0),
					transformedMatrix.get(1, 0), transformedMatrix.get(2, 0));

			// Applies rotation to the vertex's normal, other transformations are irrelevant
			norm = transformedVertex.getNormal();
			norm.push_back(1);
			originalMatrix.setVector(norm);
			transformedMatrix = originalMatrix << rotationMatrix;
			transformedVertex.setNormal(transformedMatrix.get(0, 0),
					transformedMatrix.get(1, 0), transformedMatrix.get(2, 0));

			transformedVertices.push_back(transformedVertex);
		}
		transformedComponents[i]->setVertices(transformedVertices);
	}
	setTransformed(transformed);
	_needsUpdating = false;
}

// Moves the drawable in the x direction by the specified distance
void Drawable::translateX(float x) {
	setX(getX() + x);
}

// Moves the drawable in the y direction by the specified distance
void Drawable::translateY(float y) {
	setY(getY() + y);
}

// Moves the drawable in the z direction by the specified distance
void Drawable::translateZ(float z) {
	setZ(getZ() + z);
}

// Moves the drawable by the distance specified in each direction
void Drawable::translateXYZ(float x, float y, float z) {
	setX(getX() + x);
	setY(getY() + y);
	setZ(getZ() + z);
}

// Scales the drawable in the x direction by the specified scalar
void Drawable::scaleX(float scaleX) {
	setScaleX(getScaleX() * scaleX);
}

// Scales the drawable in the y direction by the specified scalar
void Drawable::scaleY(float scaleY) {
	setScaleY(getScaleY() * scaleY);
}

// Scales the drawable in the z direction by the specified scalar
void Drawable::scaleZ(float scaleZ) {
	setScaleZ(getScaleZ() * scaleZ);
}

// Scales the drawable by the distance specified in each scalar
void Drawable::scaleXYZ(float scaleX, float scaleY, float scaleZ) {
	setScaleX(getScaleX() * scaleX);
	setScaleY(getScaleY() * scaleY);
	setScaleZ(getScaleZ() * scaleZ);
}

// Rotates the drawable around the x axis by the specified angle
void Drawable::rotateX(float theta) {
	setRotationX(getRotationX() + theta);
}

// Rotates the drawable around the y axis by the specified angle
void Drawable::rotateY(float theta) {
	setRotationY(getRotationY() + theta);
}

// Rotates the drawable around the z axis by the specified angle
void Drawable::rotateZ(float theta) {
	setRotationZ(getRotationZ() + theta);
}

// Rotates the drawable by the angle specified around each axis
void Drawable::rotateXYZ(float thetaX, float thetaY, float thetaZ) {
	setRotationX(getRotationX() + thetaX);
	setRotationY(getRotationY() + thetaY);
	setRotationZ(getRotationZ() + thetaZ);
}

// Returns the drawable's x coordinate
float Drawable::getX() {
	return _x;
}

// Returns the drawable's y coordinate
float Drawable::getY() {
	return _y;
}

// Returns the drawable's z coordinate
float Drawable::getZ() {
	return _z;
}

// Returns the drawable's x scalar
float Drawable::getScaleX() {
	return _scaleX;
}

// Returns the drawable's y scalar
float Drawable::getScaleY() {
	return _scaleY;
}

// Returns the drawable's z scalar
float Drawable::getScaleZ() {
	return _scaleZ;
}

// Returns the drawable's angle around the x axis
float Drawable::getRotationX() {
	return _rotationX;
}

// Returns the drawable's angle around the y axis
float Drawable::getRotationY() {
	return _rotationY;
}

// Returns the drawable's angle around the z axis
float Drawable::getRotationZ() {
	return _rotationZ;
}

// Sets the drawable's x coordinate
void Drawable::setX(float x) {
	_x = x;
	_needsUpdating = true;
}

// Sets the drawable's y coordinate
void Drawable::setY(float y) {
	_y = y;
	_needsUpdating = true;
}

// Sets the drawable's z coordinate
void Drawable::setZ(float z) {
	_z = z;
	_needsUpdating = true;
}

// Sets the drawable's x, y, and z coordinates
void Drawable::setXYZ(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
	_needsUpdating = true;
}

// Sets the drawable's x scalar
void Drawable::setScaleX(float scaleX) {
	_scaleX = scaleX;
	_needsUpdating = true;
}

// Sets the drawable's y scalar
void Drawable::setScaleY(float scaleY) {
	_scaleY = scaleY;
	_needsUpdating = true;
}

// Sets the drawable's z scalar
void Drawable::setScaleZ(float scaleZ) {
	_scaleZ = scaleZ;
	_needsUpdating = true;
}

// Sets the drawable's x, y, and z scalars
void Drawable::setScaleXYZ(float scaleX, float scaleY, float scaleZ) {
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;
	_needsUpdating = true;
}

// Sets the drawable's angle around the x axis
void Drawable::setRotationX(float rotationX) {
	_rotationX = rotationX;
	_needsUpdating = true;
}

// Sets the drawable's angle around the y axis
void Drawable::setRotationY(float rotationY) {
	_rotationY = rotationY;
	_needsUpdating = true;
}

// Sets the drawable's angle around the z axis
void Drawable::setRotationZ(float rotationZ) {
	_rotationZ = rotationZ;
	_needsUpdating = true;
}

// Sets the drawable's angle around the x, y, and z axes
void Drawable::setRotationXYZ(float rotationX, float rotationY,
		float rotationZ) {
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;
	_needsUpdating = true;
}

void Drawable::setColor(float r, float g, float b) {
	std::vector<GLTriangle*> triangles = getTriangles();
	for (int i = 0; i < triangles.size(); i++)
		triangles[i]->setColor(r, g, b);
}

void Drawable::setOutlineColor(float r, float g, float b) {
	std::vector<GLLine*> lines = getLines();
	for (int i = 0; i < lines.size(); i++)
		lines[i]->setColor(r, g, b);
}

void Drawable::drawOutline(bool drawOutline) {
	_drawOutline = drawOutline;
}

