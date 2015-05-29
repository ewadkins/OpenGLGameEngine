/*
 * Renderer.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: ericwadkins
 */

#include "Renderer.h"
#include "../Application.h"

Renderer::Renderer(Application* application) : // FIXME Random warning message
		_projectionMatrix(Matrix<float>::identity(4)) {
	_application = application;
	_basicShader = nullptr;
	_lightingShader = nullptr;
	_currentProgram = nullptr;
	_lightingEnabled = true;
	_shininess = 0;

	/*_staticTriangleVBO = nullptr;
	_staticLineVBO = nullptr;
	_staticPointVBO = nullptr;
	_dynamicTriangleVBO = nullptr;
	_dynamicLineVBO = nullptr;
	_dynamicPointVBO = nullptr;
	_streamTriangleVBO = nullptr;
	_streamLineVBO = nullptr;
	_streamPointVBO = nullptr;
	_terrainTriangleVBO = nullptr;
	_terrainLineVBO = nullptr;
	_terrainPointVBO = nullptr;*/
}

// Sets the shader program to be used in rendering
void Renderer::useProgram(ShaderProgram* program) {
	glUseProgram(program->getProgramId());
	_currentProgram = program;
	_application->_logger->log("Using shader program: ").log(program->getName()).endLine();
	updateUniforms();
}

void Renderer::setLightingEnabled(bool lightingEnabled) {
	_currentProgram->setUniform1i("lightingEnabled", lightingEnabled);
	_lightingEnabled = lightingEnabled;
}

void Renderer::setShininess(float shininess) {
	_currentProgram->setUniform1f("shininess", shininess);
	_shininess = shininess;
}

// Sets the projection matrix to be used in rendering
void Renderer::setProjectionMatrix(Matrix<float> projectionMatrix) {
	_currentProgram->setUniformMatrix4x4f("projectionMatrix",
			projectionMatrix.getArray());
	_projectionMatrix = projectionMatrix;
}

// Updates certain uniforms upon the use of a different shader program
void Renderer::updateUniforms() {
	_currentProgram->setUniform1i("lightingEnabled", _lightingEnabled);
	_currentProgram->setUniform1i("shininess", _shininess);
	_currentProgram->setUniformMatrix4x4f("projectionMatrix",
			_projectionMatrix.getArray());
}

void Renderer::setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 1);
}

// Initialization method ran on startup
void Renderer::createShaders() {
	// Create shader programs
	_basicShader = new ShaderProgram(_application, "Basic shader",
			"shaders/basicVertex.glsl", "shaders/basicFragment.glsl");
	_lightingShader = new ShaderProgram(_application, "Lighting shader",
			"shaders/lightingVertex.glsl", "shaders/lightingFragment.glsl");

	// Attempt to assign a shader program
	if (_lightingShader->getProgramId() != 0)
		useProgram(_lightingShader);
	else if (_basicShader->getProgramId() != 0)
		useProgram(_basicShader);
	else
		throw "No shader assigned";
}

void Renderer::createVBOs() {

	// Create static VBOs
	_staticTriangleVBO = new VBO<GLTriangle>(VBOBase::STATIC);
	_staticLineVBO = new VBO<GLLine>(VBOBase::STATIC);
	_staticPointVBO = new VBO<GLPoint>(VBOBase::STATIC);
	_staticTriangleVBO->create();
	_staticLineVBO->create();
	_staticPointVBO->create();

	// Create dynamic VBOs
	_dynamicTriangleVBO = new VBO<GLTriangle>(VBOBase::DYNAMIC);
	_dynamicLineVBO = new VBO<GLLine>(VBOBase::DYNAMIC);
	_dynamicPointVBO = new VBO<GLPoint>(VBOBase::DYNAMIC);
	_dynamicTriangleVBO->create();
	_dynamicLineVBO->create();
	_dynamicPointVBO->create();

	// Create stream VBOs
	_streamTriangleVBO = new VBO<GLTriangle>(VBOBase::STREAM);
	_streamLineVBO = new VBO<GLLine>(VBOBase::STREAM);
	_streamPointVBO = new VBO<GLPoint>(VBOBase::STREAM);
	_streamTriangleVBO->create();
	_streamLineVBO->create();
	_streamPointVBO->create();

	// Create terrain VBOs
	_terrainTriangleVBO = new VBO<GLTriangle>(VBOBase::STATIC);
	_terrainLineVBO = new VBO<GLLine>(VBOBase::STATIC);
	_terrainPointVBO = new VBO<GLPoint>(VBOBase::STATIC);
	_terrainTriangleVBO->create();
	_terrainLineVBO->create();
	_terrainPointVBO->create();
}

void Renderer::updateStaticVBOs() {

	_staticTriangleVBO->clear();
	_staticLineVBO->clear();
	_staticPointVBO->clear();

	std::vector<GLTriangle> triangles;
	std::vector<GLLine> lines;
	std::vector<GLPoint> points;

	std::vector<Drawable*> staticDrawables = _application->_map->_staticDrawables;

	// Uses pre-transformed versions of each drawable, which prevents recalculation if unnecessary
	for (int i = 0; i < staticDrawables.size(); i++) {

		triangles = staticDrawables[i]->getTransformedTriangles();
		lines = staticDrawables[i]->getTransformedLines();
		points = staticDrawables[i]->getTransformedPoints();

		if (staticDrawables[i]->getDrawFaces())
			for (int j = 0; j < triangles.size(); j++)
				_staticTriangleVBO->add(triangles[j]);

		if (staticDrawables[i]->getDrawOutline()) {
			for (int j = 0; j < lines.size(); j++)
				_staticLineVBO->add(lines[j]);
			for (int j = 0; j < points.size(); j++)
				_staticPointVBO->add(points[j]);
		}
	}

	_staticTriangleVBO->updateData();
	_staticTriangleVBO->pushToBuffer();
	_staticLineVBO->updateData();
	_staticLineVBO->pushToBuffer();
	_staticPointVBO->updateData();
	_staticPointVBO->pushToBuffer();
}

void Renderer::updateDynamicVBOs() {

	_dynamicTriangleVBO->clear();
	_dynamicLineVBO->clear();
	_dynamicPointVBO->clear();

	std::vector<GLTriangle> triangles;
	std::vector<GLLine> lines;
	std::vector<GLPoint> points;

	std::vector<Drawable*> dynamicDrawables = _application->_map->_dynamicDrawables;

	// Uses pre-transformed versions of each drawable, which prevents recalculation if unnecessary
	for (int i = 0; i < dynamicDrawables.size(); i++) {

		triangles = dynamicDrawables[i]->getTransformedTriangles();
		lines = dynamicDrawables[i]->getTransformedLines();
		points = dynamicDrawables[i]->getTransformedPoints();

		if (dynamicDrawables[i]->getDrawFaces())
			for (int j = 0; j < triangles.size(); j++)
				_dynamicTriangleVBO->add(triangles[j]);

		if (dynamicDrawables[i]->getDrawOutline()) {
			for (int j = 0; j < lines.size(); j++)
				_dynamicLineVBO->add(lines[j]);
			for (int j = 0; j < points.size(); j++)
				_dynamicPointVBO->add(points[j]);
		}
	}

	_dynamicTriangleVBO->updateData();
	_dynamicTriangleVBO->pushToBuffer();
	_dynamicLineVBO->updateData();
	_dynamicLineVBO->pushToBuffer();
	_dynamicPointVBO->updateData();
	_dynamicPointVBO->pushToBuffer();
}

void Renderer::updateStreamVBOs() {

	_streamTriangleVBO->clear();
	_streamLineVBO->clear();
	_streamPointVBO->clear();

	std::vector<GLTriangle> triangles;
	std::vector<GLLine> lines;
	std::vector<GLPoint> points;

	std::vector<Drawable*> streamDrawables = _application->_map->_streamDrawables;

	// Transforms each drawable on the spot to increase performance for rendering stream drawables
	for (int i = 0; i < streamDrawables.size(); i++) {
		Drawable* d = streamDrawables[i];
		Matrix<float> modelTransformationMatrix =
				GLMatrix::modelTransformationMatrix(d->getX(), d->getY(),
						d->getZ(), d->getRotationX(), d->getRotationY(),
						d->getRotationZ(), d->getScaleX(), d->getScaleY(),
						d->getScaleZ());

		Matrix<float> rotationMatrix = GLMatrix::rotationMatrixXYZ(
				d->getRotationX(), d->getRotationY(), d->getRotationZ());

		triangles = streamDrawables[i]->_triangles;
		lines = streamDrawables[i]->_lines;
		points = streamDrawables[i]->_points;

		if (streamDrawables[i]->getDrawFaces()) {
			for (int j = 0; j < triangles.size(); j++) {
				for (int k = 0; k < triangles[j]._vertices.size(); k++)
					triangles[j]._vertices[k].transform(modelTransformationMatrix,
							rotationMatrix);
				_streamTriangleVBO->add(triangles[j]);
			}
		}

		if (streamDrawables[i]->getDrawOutline()) {
			for (int j = 0; j < lines.size(); j++) {
				for (int k = 0; k < lines[j]._vertices.size(); k++)
					lines[j]._vertices[k].transform(modelTransformationMatrix,
							rotationMatrix);
				_streamLineVBO->add(lines[j]);
			}
			for (int j = 0; j < points.size(); j++) {
				for (int k = 0; k < points[j]._vertices.size(); k++)
					points[j]._vertices[k].transform(modelTransformationMatrix,
							rotationMatrix);
				_streamPointVBO->add(points[j]);
			}
		}
	}

	_streamTriangleVBO->updateData();
	_streamTriangleVBO->pushToBuffer();
	_streamLineVBO->updateData();
	_streamLineVBO->pushToBuffer();
	_streamPointVBO->updateData();
	_streamPointVBO->pushToBuffer();
}

void Renderer::updateTerrainVBOs() {

	_terrainTriangleVBO->clear();
	_terrainLineVBO->clear();
	_terrainPointVBO->clear();

	std::vector<GLTriangle> triangles;
	std::vector<GLLine> lines;
	std::vector<GLPoint> points;

	std::vector<Drawable*> terrainDrawables = _application->_map->_terrainDrawables;

	// Uses pre-transformed versions of each drawable, which prevents recalculation if unnecessary
	for (int i = 0; i < terrainDrawables.size(); i++) {

		triangles = terrainDrawables[i]->getTransformedTriangles();
		lines = terrainDrawables[i]->getTransformedLines();
		points = terrainDrawables[i]->getTransformedPoints();

		if (terrainDrawables[i]->getDrawFaces())
			for (int j = 0; j < triangles.size(); j++)
				_terrainTriangleVBO->add(triangles[j]);

		if (terrainDrawables[i]->getDrawOutline()) {
			for (int j = 0; j < lines.size(); j++)
				_terrainLineVBO->add(lines[j]);
			for (int j = 0; j < points.size(); j++)
				_terrainPointVBO->add(points[j]);
		}
	}

	_terrainTriangleVBO->updateData();
	_terrainTriangleVBO->pushToBuffer();
	_terrainLineVBO->updateData();
	_terrainLineVBO->pushToBuffer();
	_terrainPointVBO->updateData();
	_terrainPointVBO->pushToBuffer();
}

void Renderer::updateLights() {
	std::vector<LightSource*> lights = _application->_map->_lights;
	for (int i = 0; i < lights.size(); i++) {
		std::string var = std::string("lights[") + std::to_string(i) + std::string("]");
		_currentProgram->setUniform1i((var + ".type").c_str(), lights[i]->getType());
		Vector<float> vec = lights[i]->getPosition();
		_currentProgram->setUniform3f((var + ".position").c_str(), vec[0], vec[1], vec[2]);
		vec = lights[i]->getDirection();
		_currentProgram->setUniform3f((var + ".direction").c_str(), vec[0], vec[1], vec[2]);
		vec = lights[i]->getAmbient();
		_currentProgram->setUniform3f((var + ".ambient").c_str(), vec[0], vec[1], vec[2]);
		vec = lights[i]->getDiffuse();
		_currentProgram->setUniform3f((var + ".diffuse").c_str(), vec[0], vec[1], vec[2]);
		vec = lights[i]->getSpecular();
		_currentProgram->setUniform3f((var + ".specular").c_str(), vec[0], vec[1], vec[2]);
		_currentProgram->setUniform1f((var + ".range").c_str(), lights[i]->getRange());
		_currentProgram->setUniform1f((var + ".spread").c_str(), lights[i]->getSpread());
		_currentProgram->setUniform1i((var + ".enabled").c_str(), lights[i]->isEnabled());
	}
}

void Renderer::render() {

	// Clear everything
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateStreamVBOs();

	bool lightingEnabled = _lightingEnabled;

	setShininess(20);
	_staticTriangleVBO->draw();
	_dynamicTriangleVBO->draw();
	_streamTriangleVBO->draw();
	setShininess(2);
	_terrainTriangleVBO->draw();

	if (lightingEnabled)
		setLightingEnabled(false);
	_staticLineVBO->draw();
	_staticPointVBO->draw();
	_dynamicLineVBO->draw();
	_dynamicPointVBO->draw();
	_streamLineVBO->draw();
	_streamPointVBO->draw();
	_terrainLineVBO->draw();
	_terrainPointVBO->draw();

	if (lightingEnabled)
		setLightingEnabled(true);
}

// Displays the rendered scene
void Renderer::display() {
	// Swaps the display buffers (displays what was drawn)
	glfwSwapBuffers(_application->_window);
	glfwPollEvents();
	//glfwWaitEvents();
}

