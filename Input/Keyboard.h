/*
 * Keyboard.h
 *
 *  Created on: Apr 12, 2015
 *      Author: ericwadkins
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLApplication;

class Keyboard {
public:
	Keyboard(OpenGLApplication* application);
	virtual ~Keyboard() {
	}
	void update();
	void dispatchEvent(int key, int scancode, int action,
			int mods);
	bool isKeyDown(int key);
	int getKeyState(int key);
private:
	OpenGLApplication* _application;
	static const float PI;
};

#endif /* KEYBOARD_H_ */
