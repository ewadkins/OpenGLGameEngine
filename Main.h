/*
 * Main.h
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class OpenGLApplication {
public:
	OpenGLApplication(int screenSizeX, int screenSizeY, bool fullScreen) {
		_window = nullptr;
		_screenSizeX = screenSizeX;
		_screenSizeY = screenSizeY;
		_fullScreen = fullScreen;
		shaderProgram = nullptr;
	}
	virtual ~OpenGLApplication() {
	}
	int start();
	const static int VERSION_MAJOR = 4;
	const static int VERSION_MINOR = 1;
	GLFWwindow* _window;
	int _screenSizeX;
	int _screenSizeY;
	bool _fullScreen;
	ShaderProgram* shaderProgram;
private:
	void setupWindow();
	void setupDisplay();
	void setupShaders();
	void initialize();
	void gameLoop();

};

#endif /* MAIN_H_ */
