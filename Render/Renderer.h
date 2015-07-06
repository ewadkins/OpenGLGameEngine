/*
 * Renderer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "ShaderProgram.h"
#include "VBO.h"
#include "../Math/Matrix.h"
#include "../Components/GLTriangle.h"
#include "../Components/GLLine.h"
#include "../Components/GLPoint.h"
#include "../Components/GLVertex.h"
#include "../Drawables/Drawable.h"
#include "../Drawables/Triangle.h"
#include "../Drawables/Cube.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <freetype.h>

class Application;

class Renderer {
public:
	Renderer(Application* application);
	virtual ~Renderer() {
	}
	void useProgram(ShaderProgram*);
	void setProjectionMatrix(Matrix<float> projectionMatrix);
	void setBackgroundColor(float r, float g, float b);
	void createShaders();
	void createVBOs();
	void updateStaticVBOs();
	void updateDynamicVBOs();
	void updateStreamVBOs();
	void updateTerrainVBOs();
	void updateLights();
	void renderText(std::string &str, FT_Face face, float x, float y, float sx, float sy);
	void render();
	void display();
	ShaderProgram* _basicShader;
	ShaderProgram* _lightingShader;
	ShaderProgram* _currentProgram;
private:
	void updateUniforms();
	void setLightingEnabled(bool lightingEnabled);
	void setModelViewProjectionEnabled(bool modelViewProjectionEnabled);
	void setShininess(float shininess);
	Application* _application;

	VBO<GLTriangle>* _staticTriangleVBO;
	VBO<GLLine>* _staticLineVBO;
	VBO<GLPoint>* _staticPointVBO;
	VBO<GLTriangle>* _dynamicTriangleVBO;
	VBO<GLLine>* _dynamicLineVBO;
	VBO<GLPoint>* _dynamicPointVBO;
	VBO<GLTriangle>* _streamTriangleVBO;
	VBO<GLLine>* _streamLineVBO;
	VBO<GLPoint>* _streamPointVBO;
	VBO<GLTriangle>* _terrainTriangleVBO;
	VBO<GLLine>* _terrainLineVBO;
	VBO<GLPoint>* _terrainPointVBO;

	std::vector<GLfloat> _textData;
	GLuint _textVao, _textVbo;

	bool _lightingEnabled;
	bool _modelViewProjectionEnabled;
	float _shininess;
	Matrix<float> _projectionMatrix;
};

#endif /* RENDERER_H_ */
