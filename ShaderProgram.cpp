/*
 * ShaderManager.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: ericwadkins
 */

#define GLEW_STATIC

#include "ShaderProgram.h"
#include "OpenGLApplication.h"

ShaderProgram::ShaderProgram(OpenGLApplication* application, const char* name, const char* vertexPath, const char* fragmentPath) {
	_application = application;
	_name = name;
	_vertexPath = vertexPath;
	_fragmentPath = fragmentPath;
	program = create();
}

GLuint ShaderProgram::loadShader(const char* shaderFile, GLenum type) {
	std::ifstream in(shaderFile);
	std::string src = "";
	std::string line = "";
	_application->_logger->log("Source code:").endLine();
	while (std::getline(in, line)) {
		src += line + "\n";
		_application->_logger->log(line).endLine();
	}
	GLuint shader;
	shader = glCreateShader(type);

	const char* source = src.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	if (!shader) {
		_application->warn("Could not compile the shader");
		return 0;
	}
	return shader;
}

GLuint ShaderProgram::create() {

	GLuint vertexShader, fragmentShader;
	GLint linked = false;

	_application->_logger->log("Loading vertex shader..").endLine().increaseIndent();
	vertexShader = loadShader(_vertexPath, GL_VERTEX_SHADER);
	if(vertexShader)
		_application->_logger->decreaseIndent().log("Vertex shader loaded successfully!").endLine();

	_application->_logger->log("Loading fragment shader..").endLine().increaseIndent();
	fragmentShader = loadShader(_fragmentPath, GL_FRAGMENT_SHADER);
	if(fragmentShader)
		_application->_logger->decreaseIndent().log("Fragment shader loaded successfully!").endLine();

	_application->_logger->log("Creating shader program..").endLine();
	program = glCreateProgram();
	if (program) {
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glBindAttribLocation(program, 0, "inPosition");
		glBindAttribLocation(program, 1, "inColor");
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
	}
	if (!linked || !program || !vertexShader || !fragmentShader) {
		_application->warn("Could not create/link the shader");
		return 0;
	}
	else
		_application->_logger->log("Shader program created and linked successfully!").endLine();

	return program;
}

const char* ShaderProgram::getName() {
	return _name;
}

int ShaderProgram::getProgramId() {
	return program;
}


