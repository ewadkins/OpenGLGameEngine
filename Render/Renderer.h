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
#include "../Components/GLTriangle.h"
#include "../Components/GLLine.h"
#include "../Components/Vertex.h"
#include "../Render/VBO.h"
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
	void createStaticVBOs();
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
	std::vector<Drawable*> staticDrawables;
};

#endif /* RENDERER_H_ */