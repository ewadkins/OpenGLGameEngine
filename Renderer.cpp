/*
 * Renderer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#include "Renderer.h"

void Renderer::setupShaders() {
	shaderProgram = new ShaderProgram("Shader 1", "shaders/vertex.glsl", "shaders/fragment.glsl");
}

void Renderer::useProgram(ShaderProgram* program) {
	glUseProgram(program->getProgramId());
	std::cout << "    Using shader program: " << program->getName() << std::endl << std::endl;
}

void Renderer::initialize() {
	setupShaders();
	if(shaderProgram->getProgramId() != 0)
		useProgram(shaderProgram);
	else
		throw "No shader assigned";
}

void Renderer::initTriangle() {

}

void Renderer::renderTriangle() {

}

