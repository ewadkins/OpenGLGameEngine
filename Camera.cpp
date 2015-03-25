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
}

void Camera::initialize() {
	setFovX(70);
	setFovY(70);
	setNear(0.01);
	setFar(1000);
	updateProjectionMatrix();
	useView();
}

void Camera::useView() {

	GLMatrix<float> viewMatrix = GLMatrix<float>::identity(4);
	viewMatrix = viewMatrix << rotate(getRotationX(), getRotationY(), getRotationZ())
			<< translate(getX(), getY(), getZ());

	viewMatrix.print();

	_application->_renderer->currentProgram->setUniformMatrix4x4f("viewMatrix", viewMatrix.getValuesArray());

}

void Camera::updateProjectionMatrix() {

	GLMatrix<float> projectionMatrix = GLMatrix<float>::identity(4);
	// FIXME orhtographic matrix not calculated correctly
	//projectionMatrix = projectionMatrix << orthographic<float>(_application->_windowSizeX, _application->_windowSizeY, getNear(), getFar());
	projectionMatrix = projectionMatrix << perspective<float>(getFovX(), getFovY(), getNear(), getFar());

	projectionMatrix.print();

}

template<typename T>
GLMatrix<T> Camera::translate(T deltaX, T deltaY, T deltaZ) {
	return GLMatrix<T>::translationMatrix(deltaX, deltaY, deltaZ);
}

template<typename T>
GLMatrix<T> Camera::scale(T scaleX, T scaleY, T scaleZ) {
	return GLMatrix<T>::scalingMatrix(scaleX, scaleY, scaleZ);
}

template<typename T>
GLMatrix<T> Camera::rotate(T thetaX, T thetaY, T thetaZ) {
	return GLMatrix<T>::rotationMatrixXYZ(thetaX, thetaY, thetaZ);
}

template<typename T>
GLMatrix<T> Camera::orthographic(int _width, int _height, float _near, float _far) {
	T width = (T) _width;
	T height = (T) _height;
	T near = (T) _near;
	T far = (T) _far;
	return GLMatrix<T>::orthographicProjectionMatrix(width, height, near, far);
}

template<typename T>
GLMatrix<T> Camera::perspective(int _fovX, int _fovY, float _near, float _far) {
	T fovX = (T) _fovX;
	T fovY = (T) _fovY;
	T near = (T) _near;
	T far = (T) _far;
	return GLMatrix<T>::perspectiveProjectionMatrix(fovX, fovY, near, far);
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

