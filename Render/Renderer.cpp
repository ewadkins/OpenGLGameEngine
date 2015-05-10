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

	/*_staticTriangleVBO = nullptr;
	_staticLineVBO = nullptr;
	_staticPointVBO = nullptr;
	_dynamicTriangleVBO = nullptr;
	_dynamicLineVBO = nullptr;
	_dynamicPointVBO = nullptr;
	_streamTriangleVBO = nullptr;
	_streamLineVBO = nullptr;
	_streamPointVBO = nullptr;*/
}

// Sets up the shaders for use in rendering
void Renderer::setupShaders() {
	_basicShader = new ShaderProgram(_application, "Basic shader",
			"shaders/basicVertex.glsl", "shaders/basicFragment.glsl");
	_lightingShader = new ShaderProgram(_application, "Lighting shader",
			"shaders/lightingVertex.glsl", "shaders/lightingFragment.glsl");
}

// Sets the shader program to be used in rendering
void Renderer::useProgram(ShaderProgram* program) {
	glUseProgram(program->getProgramId());
	_currentProgram = program;
	_application->_logger->log("Using shader program: ").log(program->getName()).endLine();
	updateUniforms();
}

void Renderer::useLighting(bool useLighting) {
	_currentProgram->setUniform1i("lightingEnabled", useLighting);
}

// Sets the projection matrix to be used in rendering
void Renderer::setProjectionMatrix(Matrix<float> projectionMatrix) {
	_projectionMatrix = projectionMatrix;
	_currentProgram->setUniformMatrix4x4f("projectionMatrix",
			_projectionMatrix.getArray());
}

// Updates certain uniforms upon the use of a different shader program
void Renderer::updateUniforms() {
	_currentProgram->setUniformMatrix4x4f("projectionMatrix",
			_projectionMatrix.getArray());
}

// Initialization method ran on startup
void Renderer::createShaders() {
	// Create shader programs
	setupShaders();

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
}

void Renderer::updateStaticVBOs() {

	_staticTriangleVBO->clear();
	_staticLineVBO->clear();
	_staticPointVBO->clear();

	std::vector<GLVertex> vertices;
	std::vector<GLTriangle> triangles;
	std::vector<GLLine> lines;
	std::vector<GLPoint> points;

	std::vector<Drawable*> staticDrawables = _application->_map->getStaticDrawables();

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

	std::vector<GLVertex> vertices;
	std::vector<GLTriangle> triangles;
	std::vector<GLLine> lines;
	std::vector<GLPoint> points;

	std::vector<Drawable*> dynamicDrawables = _application->_map->getDynamicDrawables();

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

	std::vector<GLVertex> vertices;
	std::vector<GLTriangle> triangles;
	std::vector<GLLine> lines;
	std::vector<GLPoint> points;

	std::vector<Drawable*> streamDrawables = _application->_map->getStreamDrawables();

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
				vertices = triangles[j].getVertices();
				for (int k = 0; k < vertices.size(); k++)
					vertices[k].transform(modelTransformationMatrix,
							rotationMatrix);
				triangles[j].setVertices(vertices);
				_streamTriangleVBO->add(triangles[j]);
			}
		}

		if (streamDrawables[i]->getDrawOutline()) {
			for (int j = 0; j < lines.size(); j++) {
				vertices = lines[j].getVertices();
				for (int k = 0; k < vertices.size(); k++)
					vertices[k].transform(modelTransformationMatrix,
							rotationMatrix);
				lines[j].setVertices(vertices);
				_streamLineVBO->add(lines[j]);
			}
			for (int j = 0; j < points.size(); j++) {
				vertices = points[j].getVertices();
				for (int k = 0; k < vertices.size(); k++)
					vertices[k].transform(modelTransformationMatrix,
							rotationMatrix);
				points[j].setVertices(vertices);
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

void Renderer::render() {

	// Clear everything
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateStreamVBOs();

	_staticTriangleVBO->draw();
	_dynamicTriangleVBO->draw();
	_streamTriangleVBO->draw();
	useLighting(false);
	_staticLineVBO->draw();
	_dynamicLineVBO->draw();
	_streamLineVBO->draw();
	_staticPointVBO->draw();
	_dynamicPointVBO->draw();
	_streamPointVBO->draw();
	useLighting(true);
}

// Displays the rendered scene
void Renderer::display() {
	// Swaps the display buffers (displays what was drawn)
	glfwSwapBuffers(_application->_window);
	glfwPollEvents();
	//glfwWaitEvents();
}

