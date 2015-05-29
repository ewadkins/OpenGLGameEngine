/*
 * Transformable.cpp
 *
 *  Created on: May 29, 2015
 *      Author: ericwadkins
 */

#include "Transformable.h"

Transformable::Transformable() {
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
}

// Moves the drawable in the x direction by the specified distance
void Transformable::translateX(float x) {
	this->setX(this->getX() + x);
}

// Moves the transformable in the y direction by the specified distance
void Transformable::translateY(float y) {
	this->setY(this->getY() + y);
}

// Moves the transformable in the z direction by the specified distance
void Transformable::translateZ(float z) {
	this->setZ(this->getZ() + z);
}

// Moves the transformable by the distance specified in each direction
void Transformable::translateXYZ(float x, float y, float z) {
	this->setX(this->getX() + x);
	this->setY(this->getY() + y);
	this->setZ(this->getZ() + z);
}

// Scales the transformable in each direction by the specified scalar
void Transformable::scale(float scale) {
	this->setScaleX(this->getScaleX() * scale);
	this->setScaleY(this->getScaleY() * scale);
	this->setScaleZ(this->getScaleZ() * scale);
}

// Scales the transformable in the x direction by the specified scalar
void Transformable::scaleX(float scaleX) {
	this->setScaleX(this->getScaleX() * scaleX);
}

// Scales the transformable in the y direction by the specified scalar
void Transformable::scaleY(float scaleY) {
	this->setScaleY(this->getScaleY() * scaleY);
}

// Scales the transformable in the z direction by the specified scalar
void Transformable::scaleZ(float scaleZ) {
	this->setScaleZ(this->getScaleZ() * scaleZ);
}

// Scales the transformable in each direction by the specified scalars
void Transformable::scaleXYZ(float scaleX, float scaleY, float scaleZ) {
	this->setScaleX(this->getScaleX() * scaleX);
	this->setScaleY(this->getScaleY() * scaleY);
	this->setScaleZ(this->getScaleZ() * scaleZ);
}

// Rotates the transformable around the x axis by the specified angle
void Transformable::rotateX(float theta) {
	this->setRotationX(this->getRotationX() + theta);
}

// Rotates the transformable around the y axis by the specified angle
void Transformable::rotateY(float theta) {
	this->setRotationY(this->getRotationY() + theta);
}

// Rotates the transformable around the z axis by the specified angle
void Transformable::rotateZ(float theta) {
	this->setRotationZ(this->getRotationZ() + theta);
}

// Rotates the transformable by the angle specified around each axis
void Transformable::rotateXYZ(float thetaX, float thetaY, float thetaZ) {
	this->setRotationX(this->getRotationX() + thetaX);
	this->setRotationY(this->getRotationY() + thetaY);
	this->setRotationZ(this->getRotationZ() + thetaZ);
}

// Returns the transformable's x coordinate
float Transformable::getX() {
	return _x;
}

// Returns the transformable's y coordinate
float Transformable::getY() {
	return _y;
}

// Returns the transformable's z coordinate
float Transformable::getZ() {
	return _z;
}

// Returns the transformable's x scalar
float Transformable::getScaleX() {
	return _scaleX;
}

// Returns the transformable's y scalar
float Transformable::getScaleY() {
	return _scaleY;
}

// Returns the transformable's z scalar
float Transformable::getScaleZ() {
	return _scaleZ;
}

// Returns the transformable's angle around the x axis
float Transformable::getRotationX() {
	return _rotationX;
}

// Returns the transformable's angle around the y axis
float Transformable::getRotationY() {
	return _rotationY;
}

// Returns the transformable's angle around the z axis
float Transformable::getRotationZ() {
	return _rotationZ;
}

// Sets the transformable's x coordinate
void Transformable::setX(float x) {
	_x = x;
	_needsUpdating = true;
}

// Sets the transformable's y coordinate
void Transformable::setY(float y) {
	_y = y;
	_needsUpdating = true;
}

// Sets the transformable's z coordinate
void Transformable::setZ(float z) {
	_z = z;
	_needsUpdating = true;
}

// Sets the transformable's x, y, and z coordinates
void Transformable::setXYZ(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
	_needsUpdating = true;
}

// Sets the transformable's x, y, and z scalars
void Transformable::setScale(float scale) {
	_scaleX = scale;
	_scaleY = scale;
	_scaleZ = scale;
	_needsUpdating = true;
}

// Sets the transformable's x scalar
void Transformable::setScaleX(float scaleX) {
	_scaleX = scaleX;
	_needsUpdating = true;
}

// Sets the transformable's y scalar
void Transformable::setScaleY(float scaleY) {
	_scaleY = scaleY;
	_needsUpdating = true;
}

// Sets the transformable's z scalar
void Transformable::setScaleZ(float scaleZ) {
	_scaleZ = scaleZ;
	_needsUpdating = true;
}

// Sets the transformable's x, y, and z scalars
void Transformable::setScaleXYZ(float scaleX, float scaleY, float scaleZ) {
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;
	_needsUpdating = true;
}

// Sets the transformable's angle around the x axis
void Transformable::setRotationX(float rotationX) {
	_rotationX = rotationX;
	_needsUpdating = true;
}

// Sets the transformable's angle around the y axis
void Transformable::setRotationY(float rotationY) {
	_rotationY = rotationY;
	_needsUpdating = true;
}

// Sets the transformable's angle around the z axis
void Transformable::setRotationZ(float rotationZ) {
	_rotationZ = rotationZ;
	_needsUpdating = true;
}

// Sets the transformable's angle around the x, y, and z axes
void Transformable::setRotationXYZ(float rotationX, float rotationY,
		float rotationZ) {
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;
	_needsUpdating = true;
}

