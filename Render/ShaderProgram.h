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
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application;

class ShaderProgram {
public:
	ShaderProgram(Application* application, const char* name,
			const char* vertexPath, const char* fragmentPath);
	virtual ~ShaderProgram() {
	}
	void setUniform1i(const char* name, GLint i);
	void setUniform3i(const char* name, GLint i1, GLint i2, GLint i3);
	void setUniform4i(const char* name, GLint i1, GLint i2, GLint i3, GLint i4);
	void setUniform1f(const char* name, GLfloat f);
	void setUniform3f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3);
	void setUniform4f(const char* name, GLfloat f1, GLfloat f2, GLfloat f3,
			GLfloat f4);
	void setUniform1d(const char* name, GLdouble d);
	void setUniform3d(const char* name, GLdouble d1, GLdouble d2, GLdouble d3);
	void setUniform4d(const char* name, GLdouble d1, GLdouble d2, GLdouble d3,
			GLdouble d4);
	void setUniformMatrix3x3f(const char* name, GLfloat* values);
	void setUniformMatrix3x3d(const char* name, GLdouble* values);
	void setUniformMatrix4x4f(const char* name, GLfloat* values);
	void setUniformMatrix4x4d(const char* name, GLdouble* values);
	const char* getName();
	int getProgramId();
private:
	GLuint loadShader(const char*, GLenum);
	GLuint create();
	Application* _application;
	const char* _name;
	const char* _vertexPath;
	const char* _fragmentPath;
	int _program;
};

#endif /* SHADERPROGRAM_H_ */
