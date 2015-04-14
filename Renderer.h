/*
 * Renderer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "Drawing/GLTriangle.h"
#include "Drawing/VBO.h"
#include "Drawing/Vertex.h"
#include "ShaderProgram.h"
#include "Math/Matrix.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application;

class Renderer {
public:
	Renderer(Application* application);
	virtual ~Renderer() {
	}
	void initialize();
	void initializeVBOs();
	void render();
	void display();
	void useProgram(ShaderProgram*);
	void setProjectionMatrix(Matrix<float> projectionMatrix);
	ShaderProgram* _shaderProgram1;
	ShaderProgram* _currentProgram;
private:
	void setupShaders();
	void updateUniforms();
	Application* _application;
	std::vector<VBOBase*> _vbos;
	Matrix<float> _projectionMatrix;
};

#endif /* RENDERER_H_ */
