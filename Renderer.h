/*
 * Renderer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLApplication;

class Renderer {
public:
	Renderer(OpenGLApplication* application);
	virtual ~Renderer() {
	}
	void initialize();
	void initTriangle();
	void renderTriangle();
	void display();
	void useProgram(ShaderProgram*);
	ShaderProgram* shaderProgram1;
	ShaderProgram* currentProgram;
private:
	void setupShaders();
	OpenGLApplication* _application;
	GLuint vao, vbo;
};

#endif /* RENDERER_H_ */
