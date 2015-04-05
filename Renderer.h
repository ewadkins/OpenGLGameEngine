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
#include "Matrix.h"

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
	void setProjectionMatrix(Matrix<float> projectionMatrix);
	ShaderProgram* _shaderProgram1;
	ShaderProgram* _currentProgram;
private:
	void setupShaders();
	void updateUniforms();
	OpenGLApplication* _application;
	GLuint vao, vbo;
	Matrix<float> _projectionMatrix;
};

#endif /* RENDERER_H_ */
