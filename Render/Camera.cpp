/*
 * Camera.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ericwadkins
 */

#include "Camera.h"

#include "../Application.h"

// Basic constructor
Camera::Camera(Application* application, float x, float y, float z,
		float rotationX, float rotationY, float rotationZ) :
		_orthographic(Matrix<float>::identity(4)), _perspective(
				Matrix<float>::identity(4)) {
	_application = application;
	_x = x;
	_y = y;
	_z = z;
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;
	_fov = 70;
	_near = 0.01;
	_far = 1000;
	_projectionType = PERSPECTIVE;
}

// Initialization method ran on startup
void Camera::initialize() {
	updateProjectionMatrices();
	useView();
}

// Creates and sets a view matrix representing the view of the camera
void Camera::useView() {

	Matrix<float> viewMatrix = GLMatrix::cameraTransformationMatrix(getX(),
			getY(), getZ(), getRotationX(), getRotationY(), getRotationZ());

	/*GLMatrix::rotationMatrixXYZ(getRotationX(),
	 getRotationY(), getRotationZ())
	 << GLMatrix::translationMatrix(-getX(), -getY(), -getZ()).transpose();*/

	_application->_renderer->_currentProgram->setUniformMatrix4x4f("viewMatrix",
			viewMatrix.getArray());

	_application->_renderer->_currentProgram->setUniform3f("cameraPosition",
			getX(), getY(), getZ());

}

// Returns the camera's position vector
Vector<float> Camera::getPosition() {
	return Vector<float>(_x, _y, _z);
}

Vector<float> Camera::getEyeVector() {
	Vector<float> result = Vector<float>(
			sin(_rotationY * M_PI / 180) * cos(_rotationX * M_PI / 180),
			-sin(_rotationX * M_PI / 180),
			cos(_rotationY * M_PI / 180) * cos(_rotationX * M_PI / 180));
	result.normalize();
	return result;
}

// Updates the projection matrices as well as setting the desired projection matrix
void Camera::updateProjectionMatrices() {

	float aspect = (float) _application->getWindowWidth()
			/ (float) _application->getWindowHeight();

	_orthographic = GLMatrix::orthographicProjectionMatrix(aspect, 1, getNear(),
			getFar());
	_perspective = GLMatrix::perspectiveProjectionMatrix(getFOV(), aspect,
			getNear(), getFar());

	/*_application->_logger->log("Orthographic matrix:").endLine().increaseIndent();
	 _application->_logger->log("Aspect: ").log(aspect).endLine().log("Z near: ").log(
	 getNear()).endLine().log("Z far: ").log(getFar()).endLine();
	 _application->_logger->log(_orthographic).decreaseIndent();

	 _application->_logger->log("Perspective matrix:").endLine().increaseIndent();
	 _application->_logger->log("FOV: ").log(getFOV()).endLine().log("Aspect: ").log(
	 aspect).endLine().log("Z near: ").log(getNear()).endLine().log(
	 "Z far: ").log(getFar()).endLine();
	 _application->_logger->log(_perspective).decreaseIndent();*/

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

// Returns the field of view
float Camera::getFOV() {
	return _fov;
}

// Returns the near clipping plane
float Camera::getNear() {
	return _near;
}

// Returns the far clipping plane
float Camera::getFar() {
	return _far;
}

// Sets the field of view
void Camera::setFOV(float fov) {
	_fov = fov;
}

// Sets the near clipping plane
void Camera::setNear(float near) {
	_near = near;
}

// Sets the far clipping plane
void Camera::setFar(float far) {
	_far = far;
}

// Sets the camera's angle around the x axis
void Camera::setRotationX(float rotationX) {
	while (fabs(rotationX) > 180) {
		if (rotationX > 180)
			rotationX -= 360;
		else
			rotationX += 360;
	}
	if (rotationX > 90)
		rotationX = 90;
	if (rotationX < -90)
		rotationX = -90;
	_rotationX = rotationX;
}

// Sets the camera's angle around the y axis
void Camera::setRotationY(float rotationY) {
	while (fabs(rotationY) > 180) {
		if (rotationY > 180)
			rotationY -= 360;
		else
			rotationY += 360;
	}
	_rotationY = rotationY;
}

// Sets the camera's angle around the z axis
void Camera::setRotationZ(float rotationZ) {
	while (fabs(rotationZ) > 180) {
		if (rotationZ > 180)
			rotationZ -= 360;
		else
			rotationZ += 360;
	}
	_rotationZ = rotationZ;
}

// Sets the camera's angle around the x, y, and z axes
void Camera::setRotationXYZ(float rotationX, float rotationY, float rotationZ) {
	setRotationX(rotationX);
	setRotationY(rotationY);
	setRotationZ(rotationZ);
}

