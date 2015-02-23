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

class OpenGLApplication;

class ShaderProgram {
public:
	ShaderProgram(OpenGLApplication* application, const char* name, const char* vertexPath, const char* fragmentPath);
	virtual ~ShaderProgram() {
	}
	const char* getName();
	int getProgramId();
private:
	GLuint loadShader(const char*, GLenum);
	GLuint create();
	OpenGLApplication* _application;
	const char* _name;
	const char* _vertexPath;
	const char* _fragmentPath;
	int program;
};

#endif /* SHADERPROGRAM_H_ */
