/*
 * OpenGLApplication.h
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#ifndef OPENGLAPPLICATION_H_
#define OPENGLAPPLICATION_H_

#include "Renderer.h"
#include <string>
#include <ctime>
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
		renderer = nullptr;
	}
	virtual ~OpenGLApplication() {
	}
	int start();
	static void warn(const char*);
	static void stop(const char*);
	static void stop();
	const static int VERSION_MAJOR = 4;
	const static int VERSION_MINOR = 1;
	GLFWwindow* _window;
	int _screenSizeX;
	int _screenSizeY;
	bool _fullScreen;
private:
	void setupWindow();
	void setupDisplay();
	void setupShaders();
	void initialize();
	void gameLoop();
	Renderer* renderer;
};

#endif /* OPENGLAPPLICATION_H_ */
