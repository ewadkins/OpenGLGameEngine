/*
 * TestGame.cpp
 *
 *  Created on: May 19, 2015
 *      Author: ericwadkins
 */

#include "TestGame.h"

TestGame::TestGame(const char* windowName, int screenSizeX, int screenSizeY,
		bool fullScreen) :
		Application(windowName, screenSizeX, screenSizeY, fullScreen) {
	_cameraLight = nullptr;

}

void TestGame::initializeWindow() {

}

void TestGame::initializeDisplay() {
	//_renderer->setBackgroundColor(0.8, 1, 1);
}

void TestGame::initializeMap() {
	_application->_logger->log("Adding objects..").endLine();

	Drawable* t1 = new Triangle();
	t1->setXYZ(-5, 0, 0);
	_map->addStaticDrawable(t1);

	Drawable* t2 = new Triangle();
	t2->setXYZ(-4, 0, 0);
	t2->rotateXYZ(45, 45, 45);
	_map->addStaticDrawable(t2);

	Drawable* t3 = new Triangle();
	t3->setXYZ(-3, 0, 0);
	t3->rotateXYZ(-80, 0, 0);
	t3->scaleXYZ(1, 2, 1);
	_map->addStaticDrawable(t3);

	Drawable* t4 = new Triangle();
	t4->setXYZ(-2, 3, 0);
	t4->setColor(1, 0.5, 0);
	_map->addStreamDrawable(t4);

	Drawable* c1 = new Cube();
	c1->setRotationXYZ(45, 45, 45);
	c1->scaleXYZ(2, 2, 2);
	_map->addStaticDrawable(c1);

	Drawable* c2 = new Cube();
	c2->setXYZ(3, 0, 0);
	c2->setRotationXYZ(30, 30, 30);
	c2->scaleXYZ(1, 1, 2);
	c2->setColor(0, 0, 1);
	_map->addStaticDrawable(c2);

	Drawable* c3 = new Cube();
	c3->setXYZ(5, 0, 0);
	c3->setColor(1, 0, 1);
	_map->addStaticDrawable(c3);

	for (int i = 0; i < 1; i++) {
		Drawable* c4 = new Cube();
		c4->setXYZ(i, 5, 0);
		c4->setColor(1, 0, 0);
		_map->addStreamDrawable(c4);
	}

	Drawable* c5 = new Cube();
	c5->setXYZ(2, 3, 0);
	c5->setRotationXYZ(45, 0, 45);
	c5->setColor(0, 1, 0);
	_map->addStreamDrawable(c5);

	Terrain* terrain = new HillTerrain(this, 100, 100, 123456);
	terrain->generate();
	terrain->setDrawOutline(false);
	terrain->updateDrawables();
	_map->addTerrain(terrain);

	_mainLight = new LightSource(LightSource::DIRECTIONAL);
	_mainLight->setDirection(1, -0.5, 1);
	_mainLight->setAmbient(0.3, 0.3, 0.3);
	_mainLight->setDiffuse(0.6, 0.6, 0.6);
	_mainLight->setSpecular(0.2, 0.2, 0.2);
	_map->addLightSource(_mainLight);

	_cameraLight = new LightSource(LightSource::SPOTLIGHT);
	_cameraLight->setAmbient(0.3, 0.3, 0.3);
	_cameraLight->setDiffuse(0.6, 0.6, 0.6);
	_cameraLight->setSpecular(0.2, 0.2, 0.2);
	_cameraLight->setRange(50);
	_map->addLightSource(_cameraLight);
}

void TestGame::initializeCamera() {
	_camera->setXYZ(0, 1.5, 8);
}

void TestGame::onGameLoop() {
	_logger->log("FPS: ").log(_fps).endLine();

	handleInput();
	_cameraLight->setPosition(_camera->getPosition());
	_cameraLight->setDirection(_camera->getEyeVector());
	_camera->useView();

	for (int i = 0; i < _map->_streamDrawables.size(); i++) {
		_map->_streamDrawables[i]->rotateXYZ(0, 1, 0);
		//_streamDrawables[i]->translateXYZ(0, 0.01, 0);
	}
	_map->updateVBOs();

	_renderer->render();
	_renderer->display();
}

void TestGame::onKeyEvent(int key, int action) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, GL_TRUE);

	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		_camera->setProjectionType(_camera->ORTHOGRAPHIC);
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		_camera->setProjectionType(_camera->PERSPECTIVE);

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		if(_cameraLight->isEnabled())
			_cameraLight->setEnabled(false);
		else
			_cameraLight->setEnabled(true);
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		LightSource* light = new LightSource(LightSource::SPOTLIGHT);
		light->setPosition(_camera->getPosition());
		light->setDirection(_camera->getEyeVector());
		light->setAmbient(0.3, 0.3, 0.3);
		light->setDiffuse(0.6, 0.6, 0.6);
		light->setSpecular(0.2, 0.2, 0.2);
		light->setRange(50);
		_lights.push_back(light);
		_map->addLightSource(light);
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		for (int i = 0; i < _lights.size(); i++)
			_map->removeLightSource(_lights[i]);
		_lights.clear();
	}
}

void TestGame::handleInput() {

	float translationSpeed = .1;
	float rotationSpeed = 1.5;

	if (_keyboard->isKeyDown(GLFW_KEY_A))
		_camera->translateXYZ(
				translationSpeed
						* sin((_camera->getRotationY() - 90) * M_PI / 180), 0,
				translationSpeed
						* cos((_camera->getRotationY() - 90) * M_PI / 180));
	if (_keyboard->isKeyDown(GLFW_KEY_D))
		_camera->translateXYZ(
				translationSpeed
						* sin((_camera->getRotationY() + 90) * M_PI / 180), 0,
				translationSpeed
						* cos((_camera->getRotationY() + 90) * M_PI / 180));
	if (_keyboard->isKeyDown(GLFW_KEY_W))
		_camera->translateXYZ(
				-translationSpeed * sin(_camera->getRotationY() * M_PI / 180),
				0,
				-translationSpeed * cos(_camera->getRotationY() * M_PI / 180));
	if (_keyboard->isKeyDown(GLFW_KEY_S))
		_camera->translateXYZ(
				translationSpeed * sin(_camera->getRotationY() * M_PI / 180), 0,
				translationSpeed * cos(_camera->getRotationY() * M_PI / 180));
	if (_keyboard->isKeyDown(GLFW_KEY_SPACE))
		_camera->translateY(translationSpeed);
	if (_keyboard->isKeyDown(GLFW_KEY_LEFT_SHIFT))
		_camera->translateY(-translationSpeed);

	if (_keyboard->isKeyDown(GLFW_KEY_LEFT))
		_camera->rotateY(rotationSpeed);
	if (_keyboard->isKeyDown(GLFW_KEY_RIGHT))
		_camera->rotateY(-rotationSpeed);
	if (_keyboard->isKeyDown(GLFW_KEY_UP))
		_camera->rotateX(rotationSpeed);
	if (_keyboard->isKeyDown(GLFW_KEY_DOWN))
		_camera->rotateX(-rotationSpeed);
}

