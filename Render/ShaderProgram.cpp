/*
 * ShaderManager.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: ericwadkins
 */

#define GLEW_STATIC

#include "ShaderProgram.h"
#include "../Application.h"

// Basic constructor
ShaderProgram::ShaderProgram(Application* application, const char* name,
		const char* vertexPath, const char* fragmentPath) {
	_application = application;
	_name = name;
	_vertexPath = vertexPath;
	_fragmentPath = fragmentPath;
	_program = create();
}

// For use in setting uniforms
void ShaderProgram::setUniform1i(const char* name, GLint i) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform1i(_program, loc, i);
}

// For use in setting uniforms
void ShaderProgram::setUniform3i(const char* name, GLint i1, GLint i2,
		GLint i3) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform3i(_program, loc, i1, i2, i3);
}

// For use in setting uniforms
void ShaderProgram::setUniform4i(const char* name, GLint i1, GLint i2, GLint i3,
		GLint i4) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform4f(_program, loc, i1, i2, i3, i4);
}

// For use in setting uniforms
void ShaderProgram::setUniform1f(const char* name, GLfloat f) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform1f(_program, loc, f);
}

// For use in setting uniforms
void ShaderProgram::setUniform3f(const char* name, GLfloat f1, GLfloat f2,
		GLfloat f3) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform3f(_program, loc, f1, f2, f3);
}

// For use in setting uniforms
void ShaderProgram::setUniform4f(const char* name, GLfloat f1, GLfloat f2,
		GLfloat f3, GLfloat f4) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform4f(_program, loc, f1, f2, f3, f4);
}

// For use in setting uniforms
void ShaderProgram::setUniform1d(const char* name, GLdouble d) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform1d(_program, loc, d);
}

// For use in setting uniforms
void ShaderProgram::setUniform3d(const char* name, GLdouble d1, GLdouble d2,
		GLdouble d3) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform3d(_program, loc, d1, d2, d3);
}

// For use in setting uniforms
void ShaderProgram::setUniform4d(const char* name, GLdouble d1, GLdouble d2,
		GLdouble d3, GLdouble d4) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniform4d(_program, loc, d1, d2, d3, d4);
}

// For use in setting uniforms
void ShaderProgram::setUniformMatrix3x3f(const char* name, GLfloat* values) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniformMatrix3fv(_program, loc, 1, false, values);
}

// For use in setting uniforms
void ShaderProgram::setUniformMatrix3x3d(const char* name, GLdouble* values) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniformMatrix3dv(_program, loc, 1, false, values);
}

// For use in setting uniforms
void ShaderProgram::setUniformMatrix4x4f(const char* name, GLfloat* values) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniformMatrix4fv(_program, loc, 1, false, values);
}

// For use in setting uniforms
void ShaderProgram::setUniformMatrix4x4d(const char* name, GLdouble* values) {
	GLint loc = glGetUniformLocation(_program, name);
	glProgramUniformMatrix4dv(_program, loc, 1, false, values);
}

std::string replace(std::string source, std::string search,
		std::string replace) {
	for (size_t pos = 0;; pos += replace.length()) {
		pos = source.find(search, pos);
		if (pos == std::string::npos)
			break;
		source.erase(pos, search.length());
		source.insert(pos, replace);
	}
	return source;
}

// Loads the shader of the specified file
GLuint ShaderProgram::loadShader(const char* shaderFile, GLenum type) {
	// Loads shader source code
	std::ifstream in(shaderFile);
	std::string src = "";
	std::string line = "";
	//_application->_logger->log("Source code:").endLine();
	while (std::getline(in, line)) {
		src += line + "\n";
		//_application->_logger->log(line).endLine();
	}

	int numLights = 1;
	if (_application->_map != nullptr)
		numLights = std::max(1, (int)_application->_map->_lights.size());
	src = replace(src, std::string("NUM_LIGHTS"), std::to_string(numLights));

	int numTextures = 1;
	if (_application->_textures != nullptr)
		numTextures = std::max(1, (int)_application->_textures->_textureMap.size());
	src = replace(src, std::string("NUM_TEXTURES"), std::to_string(numTextures));
	//_application->_logger->log(src).endLine();

	// Creates shader ID
	GLuint shader = glCreateShader(type);

	// Compiles shader
	const char* source = src.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	GLint maxLength = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
	GLchar* log = new char[maxLength];
	glGetShaderInfoLog(shader, maxLength, &maxLength, &log[0]);
	if (isCompiled == GL_FALSE) {
		glDeleteShader(shader);
		_application->warn("Could not compile the shader");

		//throw log;
		_application->warn(log);

		return 0;
	} else if (maxLength > 0)
		_application->warn(log);
	return shader;
}

// Creates the shader program
GLuint ShaderProgram::create() {

	GLuint vertexShader, fragmentShader;
	GLint linked = false;

	_application->_logger->log(_name).log(":").endLine().increaseIndent();

	// Loads vertex shader
	_application->_logger->log("Loading vertex shader..").endLine().increaseIndent();
	vertexShader = loadShader(_vertexPath, GL_VERTEX_SHADER);
	if (vertexShader)
		_application->_logger->log("Vertex shader loaded successfully!").endLine();
	_application->_logger->decreaseIndent();

	// Loads fragment shader
	_application->_logger->log("Loading fragment shader..").endLine().increaseIndent();
	fragmentShader = loadShader(_fragmentPath, GL_FRAGMENT_SHADER);
	if (fragmentShader)
		_application->_logger->log("Fragment shader loaded successfully!").endLine();
	_application->_logger->decreaseIndent();

	// Creates shader program
	_application->_logger->log("Creating shader program..").endLine().increaseIndent();
	_program = glCreateProgram();
	if (_program) {
		glAttachShader(_program, vertexShader);
		glAttachShader(_program, fragmentShader);

		// Links attribute variables
		glBindAttribLocation(_program, 0, "inPosition");
		glBindAttribLocation(_program, 1, "inColor");
		glBindAttribLocation(_program, 2, "inNormal");
		glBindAttribLocation(_program, 3, "inTexCoords");

		// Links shader program
		glLinkProgram(_program);
		glGetProgramiv(_program, GL_LINK_STATUS, &linked);
	}
	if (!linked || !_program || !vertexShader || !fragmentShader) {
		_application->warn("Could not create/link the shader program");
		_application->_logger->decreaseIndent().decreaseIndent();
		return 0;
	} else
		_application->_logger->log(
				"Shader program created and linked successfully!").endLine().decreaseIndent().decreaseIndent();

	return _program;
}

// Returns the name given to this shader program
const char* ShaderProgram::getName() {
	return _name;
}

// Returns the program ID used by OpenGL in identifying this shader program
int ShaderProgram::getProgramId() {
	return _program;
}

