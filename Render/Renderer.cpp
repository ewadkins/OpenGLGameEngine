/*
 * Renderer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#include "Renderer.h"

#include "../Application.h"

Renderer::Renderer(Application* application) :
		_projectionMatrix(Matrix<float>::identity(4)) {
	_application = application;
	_shaderProgram1 = nullptr;
	_currentProgram = nullptr;
}

// Sets up the shaders for use in rendering
void Renderer::setupShaders() {
	_shaderProgram1 = new ShaderProgram(_application, "Shader 1",
			"shaders/vertex.glsl", "shaders/fragment.glsl");
}

// Sets the shader program to be used in rendering
void Renderer::useProgram(ShaderProgram* program) {
	glUseProgram(program->getProgramId());
	_currentProgram = program;
	_application->_logger->log("Using shader program: ").log(program->getName()).endLine();
	updateUniforms();
}

// Sets the projection matrix to be used in rendering
void Renderer::setProjectionMatrix(Matrix<float> projectionMatrix) {
	_projectionMatrix = projectionMatrix;
	_currentProgram->setUniformMatrix4x4f("projectionMatrix",
			_projectionMatrix.getArray());
}

// Updates certain uniforms upon the use of a different shader program
void Renderer::updateUniforms() {
	_currentProgram->setUniformMatrix4x4f("projectionMatrix",
			_projectionMatrix.getArray());
}

// Initialization method ran on startup
void Renderer::initialize() {
	// Create shader programs
	setupShaders();

	// Attempt to assign a shader program
	if (_shaderProgram1->getProgramId() != 0)
		useProgram(_shaderProgram1);
	else
		throw "No shader assigned";

	initializeVBOs();
}

// Test: Initializes data that will draw a triangle
void Renderer::initializeVBOs() {

	createVBOs();

	Drawable* t1 = new Triangle();
	t1->setXYZ(-5, 0, 0);
	_staticDrawables.push_back(t1);

	Drawable* t2 = new Triangle();
	t2->setXYZ(-4, 0, 0);
	t2->rotateXYZ(45, 45, 45);
	_staticDrawables.push_back(t2);

	Drawable* t3 = new Triangle();
	t3->setXYZ(-3, 0, 0);
	t3->rotateXYZ(45, 45, 45);
	t3->scaleXYZ(1, 2, 1);
	_staticDrawables.push_back(t3);

	Drawable* t4 = new Triangle();
	t4->setXYZ(-2, 3, 0);
	t4->setColor(1, 0.5, 0);
	_streamDrawables.push_back(t4);

	Drawable* c1 = new Cube();
	c1->setRotationXYZ(45, 45, 45);
	c1->scaleXYZ(2, 2, 2);
	_staticDrawables.push_back(c1);

	Drawable* c2 = new Cube();
	c2->setXYZ(3, 0, 0);
	c2->setRotationXYZ(30, 30, 30);
	c2->scaleXYZ(1, 1, 2);
	c2->setColor(0, 0, 1);
	_staticDrawables.push_back(c2);

	Drawable* c3 = new Cube();
	c3->setXYZ(5, 0, 0);
	c3->setColor(1, 0, 1);
	_staticDrawables.push_back(c3);

	for (int i = 0; i < 1; i++) {
		Drawable* c4 = new Cube();
		c4->setXYZ(i, 5, 0);
		c4->setColor(1, 0, 0);
		_streamDrawables.push_back(c4);
	}

	Drawable* c5 = new Cube();
	c5->setXYZ(2, 3, 0);
	c5->setRotationXYZ(45, 0, 45);
	c5->setColor(0, 1, 0);
	_streamDrawables.push_back(c5);

	updateStaticVBOs();
	updateDynamicVBOs();
	updateStreamVBOs();

}

void Renderer::createVBOs() {

	_staticVBOs.clear();
	_dynamicVBOs.clear();
	_streamVBOs.clear();

	// Create static VBOs
	_staticTriangleVBO = new VBO<GLTriangle>(VBOBase::STATIC);
	_staticVBOs.push_back(_staticTriangleVBO);
	_staticLineVBO = new VBO<GLLine>(VBOBase::STATIC);
	_staticVBOs.push_back(_staticLineVBO);
	//updateStaticVBOs();
	for (int i = 0; i < _staticVBOs.size(); i++)
		_staticVBOs[i]->create();

	// Create dynamic VBOs
	_dynamicTriangleVBO = new VBO<GLTriangle>(VBOBase::DYNAMIC);
	_dynamicVBOs.push_back(_dynamicTriangleVBO);
	_dynamicLineVBO = new VBO<GLLine>(VBOBase::DYNAMIC);
	_dynamicVBOs.push_back(_dynamicLineVBO);
	//updateDynamicVBOs();
	for (int i = 0; i < _dynamicVBOs.size(); i++)
		_dynamicVBOs[i]->create();

	// Create stream VBOs
	_streamTriangleVBO = new VBO<GLTriangle>(VBOBase::STREAM);
	_streamVBOs.push_back(_streamTriangleVBO);
	_streamLineVBO = new VBO<GLLine>(VBOBase::STREAM);
	_streamVBOs.push_back(_streamLineVBO);
	//updateStreamVBOs();
	for (int i = 0; i < _streamVBOs.size(); i++)
		_streamVBOs[i]->create();
}

void Renderer::updateStaticVBOs() {
	_staticTriangleVBO->clear();
	for (int i = 0; i < _staticDrawables.size(); i++) {
		std::vector<GLTriangle*> triangles =
				_staticDrawables[i]->getTransformedTriangles();
		for (int j = 0; j < triangles.size(); j++)
			_staticTriangleVBO->add(triangles[j]);
	}
	_staticTriangleVBO->updateData();
	_staticTriangleVBO->pushToBuffer();

	_staticLineVBO->clear();
	for (int i = 0; i < _staticDrawables.size(); i++) {
		std::vector<GLLine*> lines = _staticDrawables[i]->getTransformedLines();
		for (int j = 0; j < lines.size(); j++)
			_staticLineVBO->add(lines[j]);
	}
	_staticLineVBO->updateData();
	_staticLineVBO->pushToBuffer();
}

void Renderer::updateDynamicVBOs() {
	_dynamicTriangleVBO->clear();
	for (int i = 0; i < _dynamicDrawables.size(); i++) {
		std::vector<GLTriangle*> triangles =
				_dynamicDrawables[i]->getTransformedTriangles();
		for (int j = 0; j < triangles.size(); j++)
			_dynamicTriangleVBO->add(triangles[j]);
	}
	_dynamicTriangleVBO->updateData();
	_dynamicTriangleVBO->pushToBuffer();

	_dynamicLineVBO->clear();
	for (int i = 0; i < _dynamicDrawables.size(); i++) {
		std::vector<GLLine*> lines =
				_dynamicDrawables[i]->getTransformedLines();
		for (int j = 0; j < lines.size(); j++)
			_dynamicLineVBO->add(lines[j]);
	}
	_dynamicLineVBO->updateData();
	_dynamicLineVBO->pushToBuffer();
}

void Renderer::updateStreamVBOs() {
	_streamTriangleVBO->clear();
	for (int i = 0; i < _streamDrawables.size(); i++) {
		std::vector<GLTriangle*> triangles =
				_streamDrawables[i]->getTransformedTriangles();
		for (int j = 0; j < triangles.size(); j++)
			_streamTriangleVBO->add(triangles[j]);
	}
	_streamTriangleVBO->updateData();
	_streamTriangleVBO->pushToBuffer();

	_streamLineVBO->clear();
	for (int i = 0; i < _streamDrawables.size(); i++) {
		std::vector<GLLine*> lines = _streamDrawables[i]->getTransformedLines();
		for (int j = 0; j < lines.size(); j++)
			_streamLineVBO->add(lines[j]);
	}
	_streamLineVBO->updateData();
	_streamLineVBO->pushToBuffer();
}

void Renderer::update() {
	for (int i = 0; i < _streamDrawables.size(); i++) {
		_streamDrawables[i]->rotateXYZ(0, 1, 0);
		_streamDrawables[i]->translateXYZ(0, 0.01, 0);
	}
}

void Renderer::render() {

	// Clear everything
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw each static vbo
	for (int i = 0; i < _staticVBOs.size(); i++)
		_staticVBOs[i]->draw();

	// Draw each dynamic vbo
	for (int i = 0; i < _dynamicVBOs.size(); i++)
		_dynamicVBOs[i]->draw();

	// Update and draw each stream vbo
	updateStreamVBOs();
	for (int i = 0; i < _streamVBOs.size(); i++)
		_streamVBOs[i]->draw();
}

// Displays the rendered scene
void Renderer::display() {
	// Swaps the display buffers (displays what was drawn)
	glfwSwapBuffers(_application->_window);
	glfwPollEvents();
	//glfwWaitEvents();
}

