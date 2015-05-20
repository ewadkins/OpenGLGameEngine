/*
 * Keyboard.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: ericwadkins
 */

#include "Keyboard.h"

#include "../Application.h"

Keyboard::Keyboard(Application* application) {
	_application = application;
}

void Keyboard::dispatchEvent(int key, int scancode, int action, int mods) {
	_application->onKeyEvent(key, action);
}

bool Keyboard::isKeyDown(int key) {
	int state = getKeyState(key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

int Keyboard::getKeyState(int key) {
	return glfwGetKey(_application->_window, key);
}

