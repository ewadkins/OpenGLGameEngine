/*
 * OpenGLApplication.h
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#ifndef OPENGLAPPLICATION_H_
#define OPENGLAPPLICATION_H_

#include "Logger.h"
#include "Renderer.h"
#include "Camera.h"
#include <string>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLApplication {
public:
	OpenGLApplication(int screenSizeX, int screenSizeY, bool fullScreen);
	virtual ~OpenGLApplication() {
	}
	int start();
	void log(const char*);
	void warn(const char*);
	void stop(const char*);
	void stop();
	const static int VERSION_MAJOR = 4;
	const static int VERSION_MINOR = 1;
	OpenGLApplication* _application;
	GLFWwindow* _window;
	Logger* _logger;
	Renderer* _renderer;
	Camera* _camera;
	int _screenSizeX;
	int _screenSizeY;
	bool _fullScreen;
private:
	void setupWindow();
	void setupDisplay();
	void setupShaders();
	void initialize();
	void gameLoop();
};

#endif /* OPENGLAPPLICATION_H_ */
