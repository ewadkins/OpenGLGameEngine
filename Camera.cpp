/*
 * Camera.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ericwadkins
 */

#include "Camera.h"
#include "OpenGLApplication.h"

Camera::Camera(OpenGLApplication* application, float x, float y, float z,
		float rotationX, float rotationY, float rotationZ) {
	_application = application;
	_x = x;
	_y = y;
	_z = z;
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;
	_fovX = 70;
	_fovY = 70;
	_near = 0.01;
	_far = 1000;
}

void Camera::initialize() {
	updateProjectionMatrix();
	useView();
}

void Camera::useView() {

	GLMatrix<float> viewMatrix = GLMatrix<float>::identity(4);
	viewMatrix = viewMatrix
			<< rotate(getRotationX(), getRotationY(), getRotationZ())
			<< translate(getX(), getY(), getZ());

	//viewMatrix.print();

	_application->_renderer->currentProgram->setUniformMatrix4x4f("viewMatrix",
			viewMatrix.getValuesArray());

}

void Camera::updateProjectionMatrix() {

	GLMatrix<float> projectionMatrix = GLMatrix<float>::identity(4);
	// FIXME orhtographic matrix not calculated correctly
	/*
	 projectionMatrix = projectionMatrix
	 << orthographic(_application->_windowSizeX,
	 _application->_windowSizeY, getNear(), getFar());
	 */
	projectionMatrix = projectionMatrix
			<< perspective(getFovX(), getFovY(), getNear(), getFar());

	projectionMatrix.print();

	_application->_renderer->currentProgram->setUniformMatrix4x4f(
			"projectionMatrix", projectionMatrix.getValuesArray());

}

GLMatrix<float> Camera::translate(float deltaX, float deltaY, float deltaZ) {
	return GLMatrix<float>::translationMatrix(deltaX, deltaY, deltaZ);
}

GLMatrix<float> Camera::scale(float scaleX, float scaleY, float scaleZ) {
	return GLMatrix<float>::scalingMatrix(scaleX, scaleY, scaleZ);
}

GLMatrix<float> Camera::rotate(float thetaX, float thetaY, float thetaZ) {
	return GLMatrix<float>::rotationMatrixXYZ(thetaX, thetaY, thetaZ);
}

GLMatrix<float> Camera::orthographic(int width, int height, float near,
		float far) {
	return GLMatrix<float>::orthographicProjectionMatrix(width, height, near,
			far);
}

GLMatrix<float> Camera::perspective(int fovX, int fovY, float near, float far) {
	return GLMatrix<float>::perspectiveProjectionMatrix(fovX, fovY, near, far);
}

int Camera::getFovX() {
	return _fovX;
}

int Camera::getFovY() {
	return _fovY;
}

float Camera::getNear() {
	return _near;
}

float Camera::getFar() {
	return _far;
}

void Camera::setFovX(int fovX) {
	_fovX = fovX;
}

void Camera::setFovY(int fovY) {
	_fovY = fovY;
}

void Camera::setNear(float near) {
	_near = near;
}

void Camera::setFar(float far) {
	_far = far;
}

void Camera::rotateX(float theta) {
	setRotationX(getRotationX() + theta);
}

void Camera::rotateY(float theta) {
	setRotationY(getRotationY() + theta);
}

void Camera::rotateZ(float theta) {
	setRotationZ(getRotationZ() + theta);
}

float Camera::getX() {
	return _x;
}

float Camera::getY() {
	return _y;
}

float Camera::getZ() {
	return _z;
}

float Camera::getRotationX() {
	return _rotationX;
}

float Camera::getRotationY() {
	return _rotationY;
}

float Camera::getRotationZ() {
	return _rotationZ;
}

void Camera::setX(float x) {
	_x = x;
}

void Camera::setY(float y) {
	_y = y;
}

void Camera::setZ(float z) {
	_z = z;
}

void Camera::setRotationX(float rotationX) {
	_rotationX = rotationX;
}

void Camera::setRotationY(float rotationY) {
	_rotationY = rotationY;
}

void Camera::setRotationZ(float rotationZ) {
	_rotationZ = rotationZ;
}

