/*
 * ShaderManager.h
 *
 *  Created on: Feb 7, 2015
 *      Author: ericwadkins
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderProgram {
public:
	ShaderProgram(const char* name, const char* vertexPath, const char* fragmentPath) {
		_name = name;
		_vertexPath = vertexPath;
		_fragmentPath = fragmentPath;
		program = create();
	}
	virtual ~ShaderProgram() {
	}
	const char* getName();
	int getProgramId();
private:
	GLuint loadShader(const char*, GLenum);
	GLuint create();
	const char* _name;
	const char* _vertexPath;
	const char* _fragmentPath;
	int program;
};

#endif /* SHADERPROGRAM_H_ */
