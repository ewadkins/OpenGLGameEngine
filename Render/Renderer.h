/*
 * Renderer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "ShaderProgram.h"
#include "../Math/Matrix.h"
#include "../Drawables/Drawable.h"
#include "../Drawables/Triangle.h"
#include "../Drawables/Cube.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Components/GLLine.h"
#include "../Components/GLTriangle.h"
#include "VBO.h"
#include "../Components/Vertex.h"

class Application;

class Renderer {
public:
	Renderer(Application* application);
	virtual ~Renderer() {
	}
	void initialize();
	void initializeVBOs();
	void createVBOs();
	void updateStaticVBOs();
	void updateDynamicVBOs();
	void updateStreamVBOs();
	void update();
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

	VBO<GLTriangle>* _staticTriangleVBO;
	VBO<GLLine>* _staticLineVBO;
	VBO<GLTriangle>* _dynamicTriangleVBO;
	VBO<GLLine>* _dynamicLineVBO;
	VBO<GLTriangle>* _streamTriangleVBO;
	VBO<GLLine>* _streamLineVBO;

	std::vector<VBOBase*> _staticVBOs;
	std::vector<VBOBase*> _dynamicVBOs;
	std::vector<VBOBase*> _streamVBOs;

	std::vector<Drawable*> _staticDrawables;
	std::vector<Drawable*> _dynamicDrawables;
	std::vector<Drawable*> _streamDrawables;

	Matrix<float> _projectionMatrix;
};

#endif /* RENDERER_H_ */
