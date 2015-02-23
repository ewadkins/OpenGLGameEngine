/*
 * Renderer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#include "Renderer.h"
#include "OpenGLApplication.h"

Renderer::Renderer(OpenGLApplication* application) {
	shaderProgram = nullptr;
	_application = application;
	vao = 0;
	vbo = 0;
}

void Renderer::setupShaders() {
	shaderProgram = new ShaderProgram(_application, "Shader 1", "shaders/vertex.glsl",
			"shaders/fragment.glsl");
}

void Renderer::useProgram(ShaderProgram* program) {
	glUseProgram(program->getProgramId());
	_application->_logger->log("Using shader program: ").log(program->getName()).endLine().endLine();
}

void Renderer::initialize() {
	setupShaders();
	if (shaderProgram->getProgramId() != 0)
		useProgram(shaderProgram);
	else
		throw "No shader assigned";

	initTriangle();
}

void Renderer::initTriangle() {

	GLfloat vertexData[] = { 0.0, 0.8, 0.0, -0.8, -0.8, 0.0, 0.8, -0.8, 0.0, };

	// make and bind the VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// make and bind the VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
			GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Renderer::renderTriangle() {

	// clear everything
	//glClearColor(0, 0, 0, 1); // black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind the VAO (the triangle)
	glBindVertexArray(vao);

	// draw the VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// unbind the VAO
	glBindVertexArray(0);

}

void Renderer::display() {
	//swaps the display buffers (displays what was drawn)
	glfwSwapBuffers (_application->_window);
	glfwPollEvents();
}

