/*
 * Keyboard.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: ericwadkins
 */

#include "Keyboard.h"
#include "../OpenGLApplication.h"

const float Keyboard::PI = 3.1415926535897;

Keyboard::Keyboard(OpenGLApplication* application) {
	_application = application;
}

void Keyboard::update() {

	float translationSpeed = .05;
	float rotationSpeed = 1;

	Camera* camera = _application->_camera;

	if (isKeyDown(GLFW_KEY_A))
		camera->translateXYZ(
				translationSpeed * std::sin((camera->getRotationY() - 90) * PI / 180),
				0,
				translationSpeed * std::cos((camera->getRotationY() - 90) * PI / 180));
	if (isKeyDown(GLFW_KEY_D))
		camera->translateXYZ(
				translationSpeed * std::sin((camera->getRotationY() + 90) * PI / 180),
				0,
				translationSpeed * std::cos((camera->getRotationY() + 90) * PI / 180));
	if (isKeyDown(GLFW_KEY_W))
		camera->translateXYZ(
				-translationSpeed * std::sin(camera->getRotationY() * PI / 180),
				0,
				-translationSpeed * std::cos(camera->getRotationY() * PI / 180));
	if (isKeyDown(GLFW_KEY_S))
		camera->translateXYZ(
				translationSpeed * std::sin(camera->getRotationY() * PI / 180),
				0,
				translationSpeed
						* std::cos(camera->getRotationY() * PI / 180));
	if (isKeyDown(GLFW_KEY_SPACE))
		camera->translateY(translationSpeed);
	if (isKeyDown(GLFW_KEY_LEFT_SHIFT))
		camera->translateY(-translationSpeed);

	if (isKeyDown(GLFW_KEY_LEFT))
		camera->rotateY(rotationSpeed);
	if (isKeyDown(GLFW_KEY_RIGHT))
		camera->rotateY(-rotationSpeed);
	if (isKeyDown(GLFW_KEY_UP))
		camera->rotateX(rotationSpeed);
	if (isKeyDown(GLFW_KEY_DOWN))
		camera->rotateX(-rotationSpeed);

}

void Keyboard::dispatchEvent(int key, int scancode, int action, int mods) {

	// Handle key events
	if (action == GLFW_PRESS)
		_application->_logger->log("Key pressed ").log(char(key)).endLine();
	if (action == GLFW_RELEASE)
		_application->_logger->log("Key released ").log(char(key)).endLine();
	if (action == GLFW_REPEAT)
		_application->_logger->log("Key repeated ").log(char(key)).endLine();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(_application->_window, GL_TRUE);

	Camera* camera = _application->_camera;

	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		camera->setProjectionType(camera->ORTHOGRAPHIC);
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		camera->setProjectionType(camera->PERSPECTIVE);

}

bool Keyboard::isKeyDown(int key) {
	int state = getKeyState(key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

int Keyboard::getKeyState(int key) {
	return glfwGetKey(_application->_window, key);
}

