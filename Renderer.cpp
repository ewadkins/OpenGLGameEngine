/*
 * Renderer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#include "Renderer.h"
#include "OpenGLApplication.h"

Renderer::Renderer(OpenGLApplication* application) :
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

	Drawable* t1 = new Triangle();
	t1->setXYZ(-5, 0, 0);
	staticDrawables.push_back(t1);

	Drawable* t2 = new Triangle();
	t2->setXYZ(-4, 0, 0);
	t2->rotateXYZ(45, 45, 45);
	staticDrawables.push_back(t2);

	Drawable* t3 = new Triangle();
	t3->setXYZ(-3, 0, 0);
	t3->rotateXYZ(45, 45, 45);
	t3->scaleXYZ(1, 2, 1);
	staticDrawables.push_back(t3);

	Drawable* c1 = new Cube();
	c1->setXYZ(0, 0, 0);
	c1->setRotationXYZ(45, 45, 45);
	c1->scaleXYZ(2, 2, 2);
	staticDrawables.push_back(c1);

	Drawable* c2 = new Cube();
	c2->setXYZ(3, 0, 0);
	c2->setRotationXYZ(30, 30, 30);
	c2->scaleXYZ(1, 1, 2);
	c2->setColor(0, 0, 1);
	staticDrawables.push_back(c2);

	Drawable* c3 = new Cube();
	c3->setXYZ(5, 0, 0);
	c3->setColor(1, 0, 1);
	staticDrawables.push_back(c3);

	createStaticVBOs();
}

void Renderer::createStaticVBOs() {

	// Group all the triangles of the drawables and put them into a VBO
	VBO<GLTriangle>* triangleVBO = new VBO<GLTriangle>(VBOBase::STATIC);
	for (int i = 0; i < staticDrawables.size(); i++) {
		std::vector<GLTriangle*> triangles = staticDrawables[i]->getTransformedTriangles();
		for (int j = 0; j < triangles.size(); j++)
			triangleVBO->add(triangles[j]);
	}
	triangleVBO->updateData();
	_vbos.push_back(triangleVBO);

	// Group all the lines of the drawables and put them into a VBO
	VBO<GLLine>* lineVBO = new VBO<GLLine>(VBOBase::STATIC);
	for (int i = 0; i < staticDrawables.size(); i++) {
		std::vector<GLLine*> lines = staticDrawables[i]->getTransformedLines();
		for (int j = 0; j < lines.size(); j++)
			lineVBO->add(lines[j]);
	}
	lineVBO->updateData();
	_vbos.push_back(lineVBO);

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

