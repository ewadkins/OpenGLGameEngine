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

	std::vector<Drawable*> drawables;

	// Creates drawables and adds them to the list so that later they are broken down
	// into their OpenGL parts and put into the respective VBOs
	{

		Drawable* d = new Triangle();
		drawables.push_back(d);

		Drawable* d2 = new Cube();
		d2->setXYZ(3, 3, 3);
		//d2->setRotationXYZ(45, 45, 45);
		drawables.push_back(d2);

	}

	// Group all the triangles of the drawables and put them into a VBO
	VBO<GLTriangle>* triangleVBO = new VBO<GLTriangle>(VBOBase::STATIC);
	for (int i = 0; i < drawables.size(); i++) {
		std::vector<GLTriangle*> triangles = drawables[i]->getTriangles();
		for (int j = 0; j < triangles.size(); j++)
			triangleVBO->add(triangles[j]);
	}
	triangleVBO->updateData();
	_vbos.push_back(triangleVBO);

	// Group all the lines of the drawables and put them into a VBO
	VBO<GLLine>* lineVBO = new VBO<GLLine>(VBOBase::STATIC);
	for (int i = 0; i < drawables.size(); i++) {
		std::vector<GLLine*> lines = drawables[i]->getLines();
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

