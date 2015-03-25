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

}

void Camera::useView() {

	GLMatrix<float> viewMatrix = GLMatrix<float>(4, 1);
	viewMatrix = viewMatrix << rotate(getRotationX(), getRotationY(), getRotationZ())
			<< translate(getX(), getY(), getZ());
	_application->_renderer->currentProgram->setUniformMatrix4x4f("viewMatrix", viewMatrix.getValuesArray());

	/*
	 glm::mat4 camera = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0),
	 glm::vec3(0, 1, 0));
	 //FIXME create suitable setUniform function
	 //_application->_renderer->currentProgram->setUniform("camera", camera);
	 */
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

void Camera::setX() {

}

void Camera::setY() {

}

void Camera::setZ() {

}

void Camera::setRotationX() {

}

void Camera::setRotationY() {

}

void Camera::setRotationZ() {

}

