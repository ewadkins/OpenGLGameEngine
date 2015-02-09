/*
 * ShaderManager.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: ericwadkins
 */

#define GLEW_STATIC

#include "ShaderProgram.h"

GLuint ShaderProgram::loadShader(const char* shaderFile, GLenum type) {
	std::ifstream in(shaderFile);
	std::string src = "";
	std::string line = "";
	while (std::getline(in, line))
		src += "        " + line + "\n";
	std::cout << "    Source code:" << std::endl << std::endl << src << std::endl;
	GLuint shader;
	shader = glCreateShader(type);

	const char* source = src.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	if (!shader) {
		throw std::runtime_error("Could not compile the shader");
		return 0;
	}
	return shader;
}

GLuint ShaderProgram::create() {

	GLuint vertexShader, fragmentShader;
	GLint linked;

	std::cout << "    Loading vertex shader.." << std::endl;
	vertexShader = loadShader(_vertexPath, GL_VERTEX_SHADER);
	std::cout << "    Vertex shader loaded successfully!" << std::endl;

	std::cout << "    Loading fragment shader.." << std::endl;
	fragmentShader = loadShader(_fragmentPath, GL_FRAGMENT_SHADER);
	std::cout << "    Fragment shader loaded successfully!" << std::endl;

	if (!vertexShader || !fragmentShader)
		return 0;

	std::cout << "    Creating shader program.." << std::endl;
	program = glCreateProgram();
	if (!program) {
		throw std::runtime_error("Shader program creation failed");
		return 0;
	}
	std::cout << "    Shader program created successfully!" << std::endl;

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "vPosition");
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		throw std::runtime_error("Could not link the shader");
		return 0;
	}

	return program;
}

const char* ShaderProgram::getName() {
	return _name;
}

int ShaderProgram::getProgramId() {
	return program;
}


