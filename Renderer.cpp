/*
 * Renderer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#include "Renderer.h"

#include "Application.h"

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

	VBO<GLTriangle>* vbo = new VBO<GLTriangle>(VBOBase::STATIC);
	// Left face
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, -0.5, 0.0, 0.0, 1.0),
					new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0),
					new Vertex(-0.5, 0.5, 0.5, 0.0, 1.0, 0.0)));
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, -0.5, 0.0, 0.0, 1.0),
					new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(-0.5, 0.5, 0.5, 0.0, 1.0, 0.0)));
	// Right face
	vbo->add(
			new GLTriangle(new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, -0.5, 0.5, 0.0, 1.0, 0.0),
					new Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0)));
	vbo->add(
			new GLTriangle(new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, 0.5, -0.5, 0.0, 1.0, 0.0),
					new Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0)));
	// Back face
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, -0.5, 0.0, 0.0, 1.0),
					new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, 0.5, -0.5, 0.0, 1.0, 0.0)));
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, -0.5, 0.0, 0.0, 1.0),
					new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, 0.5, -0.5, 0.0, 1.0, 0.0)));
	// Front face
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, -0.5, 0.5, 0.0, 1.0, 0.0),
					new Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0)));
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0),
					new Vertex(-0.5, 0.5, 0.5, 0.0, 1.0, 0.0),
					new Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0)));
	// Bottom face
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, -0.5, 0.0, 0.0, 1.0),
					new Vertex(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, -0.5, 0.5, 0.0, 1.0, 0.0)));
	vbo->add(
			new GLTriangle(new Vertex(-0.5, -0.5, -0.5, 0.0, 0.0, 1.0),
					new Vertex(0.5, -0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, -0.5, 0.5, 0.0, 1.0, 0.0)));
	// Top face
	vbo->add(
			new GLTriangle(new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(-0.5, 0.5, 0.5, 0.0, 1.0, 0.0),
					new Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0)));
	vbo->add(
			new GLTriangle(new Vertex(-0.5, 0.5, -0.5, 1.0, 0.0, 0.0),
					new Vertex(0.5, 0.5, -0.5, 0.0, 1.0, 0.0),
					new Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0)));

	vbo->updateData();
	_vbos.push_back(vbo);

	for (int i = 0; i < _vbos.size(); i++)
		_vbos[i]->create();

}

void Renderer::render() {

	// Clear everything
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw each vbo
	for (int i = 0; i < _vbos.size(); i++)
		_vbos[i]->draw();
}

// Displays the rendered scene
void Renderer::display() {
	// Swaps the display buffers (displays what was drawn)
	glfwSwapBuffers(_application->_window);
	glfwPollEvents();
	//glfwWaitEvents();
}

