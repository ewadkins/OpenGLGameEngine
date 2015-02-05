/*
 * Main.h
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class OpenGLApplication {
public:
	OpenGLApplication(){}
	virtual ~OpenGLApplication(){}
	int start();
private:
	void initialize();
	GLFWwindow* _window;

};

#endif /* MAIN_H_ */
