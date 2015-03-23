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
	_program = create();
}

void ShaderProgram::setUniform(const char* name, GLint i) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform1i(_program, loc, i);
}

void ShaderProgram::setUniform(const char* name, GLfloat f) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform1f(_program, loc, f);
}

void ShaderProgram::setUniform(const char* name, GLfloat f1, GLfloat f2, GLfloat f3) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform3f(_program, loc, f1, f2, f3);
}

void ShaderProgram::setUniform(const char* name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform4f(_program, loc, f1, f2, f3, f4);
}

GLuint ShaderProgram::loadShader(const char* shaderFile, GLenum type) {
	// Loads shader source code
	std::ifstream in(shaderFile);
	std::string src = "";
	std::string line = "";
	_application->_logger->log("Source code:").endLine();
	while (std::getline(in, line)) {
		src += line + "\n";
		_application->_logger->log(line).endLine();
	}
	GLuint shader;

	// Creates shader ID
	shader = glCreateShader(type);

	// Compiles shader
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

	// Loads vertex shader
	_application->_logger->log("Loading vertex shader..").endLine().increaseIndent();
	vertexShader = loadShader(_vertexPath, GL_VERTEX_SHADER);
	if(vertexShader)
		_application->_logger->decreaseIndent().log("Vertex shader loaded successfully!").endLine();

	// Loads fragment shader
	_application->_logger->log("Loading fragment shader..").endLine().increaseIndent();
	fragmentShader = loadShader(_fragmentPath, GL_FRAGMENT_SHADER);
	if(fragmentShader)
		_application->_logger->decreaseIndent().log("Fragment shader loaded successfully!").endLine();

	// Creates shader program
	_application->_logger->log("Creating shader program..").endLine();
	_program = glCreateProgram();
	if (_program) {
		glAttachShader(_program, vertexShader);
		glAttachShader(_program, fragmentShader);

		// Links attribute variables
		glBindAttribLocation(_program, 0, "inPosition");
		glBindAttribLocation(_program, 1, "inColor");

		// Links shader program
		glLinkProgram(_program);
		glGetProgramiv(_program, GL_LINK_STATUS, &linked);
	}
	if (!linked || !_program || !vertexShader || !fragmentShader) {
		_application->warn("Could not create/link the shader");
		return 0;
	}
	else
		_application->_logger->log("Shader program created and linked successfully!").endLine();

	return _program;
}

const char* ShaderProgram::getName() {
	// Returns name of the shader
	return _name;
}

int ShaderProgram::getProgramId() {
	// Returns the program ID used by OpenGL
	return _program;
}


