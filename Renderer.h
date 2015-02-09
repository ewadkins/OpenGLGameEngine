/*
 * Renderer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
	Renderer() {
		shaderProgram = nullptr;
	}
	virtual ~Renderer() {
	}
	void initialize();
	void initTriangle();
	void renderTriangle();
	void useProgram(ShaderProgram*);
	ShaderProgram* shaderProgram;
private:
	void setupShaders();
};

#endif /* RENDERER_H_ */
