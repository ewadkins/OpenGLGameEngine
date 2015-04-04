/*
 * Camera.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ericwadkins
 */

#include "Camera.h"
#include "OpenGLApplication.h"

// Basic constructor
Camera::Camera(OpenGLApplication* application, float x, float y, float z,
		float rotationX, float rotationY, float rotationZ) :
		_orthographic(GLMatrix<float>::identity(4)), _perspective(
				GLMatrix<float>::identity(4)) {
	_application = application;
	_x = x;
	_y = y;
	_z = z;
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;
	_fovX = 70;
	_fovY = 70;
	_near = -0.01;
	_far = 1000;
	_projectionType = ORTHOGRAPHIC;
}

// Initialization method ran on startup
void Camera::initialize() {
	updateProjectionMatrices();
	useView();
}

// Creates and sets a view matrix representing the view of the camera
void Camera::useView() {

	GLMatrix<float> viewMatrix = GLMatrix<float>::identity(4);
	viewMatrix = viewMatrix
			<< rotate(getRotationX(), getRotationY(), getRotationZ())
			<< translate(getX(), getY(), getZ());

	//_application->_logger->log("View matrix:").endLine().log(viewMatrix);

	_application->_renderer->_currentProgram->setUniformMatrix4x4f("viewMatrix",
			viewMatrix.getValuesArray());

}

// Updates the projection matrices as well as setting the desired projection matrix
void Camera::updateProjectionMatrices() {

	_orthographic = orthographic(_application->_windowSizeX/100,
			_application->_windowSizeY/100, getNear(), getFar());

	_perspective = perspective(getFovX(), getFovY(), getNear(), getFar());

	_application->_logger->log("Orthographic matrix:").endLine().increaseIndent();
	_application->_logger->log("Window dimensions: ").log(
			_application->_windowSizeX).log(" x ").log(
			_application->_windowSizeY).endLine().log("Z near: ").log(getNear()).endLine().log(
			"Z far: ").log(getFar()).endLine();
	_application->_logger->log(_orthographic).decreaseIndent();

	_application->_logger->log("Perspective matrix:").endLine().increaseIndent();
	_application->_logger->log("FOV X: ").log(getFovX()).endLine().log(
			"FOV Y: ").log(getFovY()).endLine().log("Z near: ").log(getNear()).endLine().log(
			"Z far: ").log(getFar()).endLine();
	_application->_logger->log(_perspective).decreaseIndent();

	useProjectionMatrix();

}

// Sets the desired projection matrix
void Camera::useProjectionMatrix() {
	if (_projectionType == ORTHOGRAPHIC) {
		_application->_renderer->setProjectionMatrix(_orthographic);
		_application->_logger->log("Using orthographic matrix..").endLine();
	} else if (_projectionType == PERSPECTIVE) {
		_application->_renderer->setProjectionMatrix(_perspective);
		_application->_logger->log("Using perspective matrix..").endLine();
	}
}

// Sets the desired projection matrix type
void Camera::setProjectionType(ProjectionType type) {
	_projectionType = type;
	useProjectionMatrix();
}

// Returns the corresponding translation matrix
GLMatrix<float> Camera::translate(float deltaX, float deltaY, float deltaZ) {
	return GLMatrix<float>::translationMatrix(deltaX, deltaY, deltaZ);
}

// Returns the corresponding scalar matrix
GLMatrix<float> Camera::scale(float scaleX, float scaleY, float scaleZ) {
	return GLMatrix<float>::scalarMatrix(scaleX, scaleY, scaleZ);
}

// Returns the corresponding rotation matrix
GLMatrix<float> Camera::rotate(float thetaX, float thetaY, float thetaZ) {
	return GLMatrix<float>::rotationMatrixXYZ(thetaX, thetaY, thetaZ);
}

// Returns the corresponding orthographic projection matrix
GLMatrix<float> Camera::orthographic(int width, int height, float near,
		float far) {
	return GLMatrix<float>::orthographicProjectionMatrix(width, height, near,
			far);
}

// Returns the corresponding perspective projection matrix
GLMatrix<float> Camera::perspective(int fovX, int fovY, float near, float far) {
	return GLMatrix<float>::perspectiveProjectionMatrix(fovX, fovY, near, far);
}

// Returns the x field of view
int Camera::getFovX() {
	return _fovX;
}

// Returns the y field of view
int Camera::getFovY() {
	return _fovY;
}

// Returns the near clipping plane
float Camera::getNear() {
	return _near;
}

// Returns the far clipping plane
float Camera::getFar() {
	return _far;
}

// Sets the x field of view
void Camera::setFovX(int fovX) {
	_fovX = fovX;
}

// Sets the y field of view
void Camera::setFovY(int fovY) {
	_fovY = fovY;
}

// Sets the near clipping plane
void Camera::setNear(float near) {
	_near = near;
}

// Sets the far clipping plane
void Camera::setFar(float far) {
	_far = far;
}

// Rotates the camera around the x axis by the specified angle
void Camera::rotateX(float theta) {
	setRotationX(getRotationX() + theta);
}

// Rotates the camera around the y axis by the specified angle
void Camera::rotateY(float theta) {
	setRotationY(getRotationY() + theta);
}

// Rotates the camera around the z axis by the specified angle
void Camera::rotateZ(float theta) {
	setRotationZ(getRotationZ() + theta);
}

// Returns the camera's x coordinate
float Camera::getX() {
	return _x;
}

// Returns the camera's y coordinate
float Camera::getY() {
	return _y;
}

// Returns the camera's z coordinate
float Camera::getZ() {
	return _z;
}

// Returns the camera's angle around the x axis
float Camera::getRotationX() {
	return _rotationX;
}

// Returns the camera's angle around the y axis
float Camera::getRotationY() {
	return _rotationY;
}

// Returns the camera's angle around the z axis
float Camera::getRotationZ() {
	return _rotationZ;
}

// Sets the camera's x coordinate
void Camera::setX(float x) {
	_x = x;
}

// Sets the camera's y coordinate
void Camera::setY(float y) {
	_y = y;
}

// Sets the camera's z coordinate
void Camera::setZ(float z) {
	_z = z;
}

// Sets the camera's angle around the x axis
void Camera::setRotationX(float rotationX) {
	_rotationX = rotationX;
}

// Sets the camera's angle around the y axis
void Camera::setRotationY(float rotationY) {
	_rotationY = rotationY;
}

// Sets the camera's angle around the z axis
void Camera::setRotationZ(float rotationZ) {
	_rotationZ = rotationZ;
}

