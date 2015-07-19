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
	_terrain = nullptr;
	_mainLight = nullptr;
	_cameraLight = nullptr;
	_playerHeight = 1;
	_snapToGround = false;
}

void TestGame::initializeWindow() {

}

void TestGame::initializeDisplay() {
	_renderer->setBackgroundColor(0.8, 1, 1);
}

void TestGame::initializeMap() {
	_application->_logger->log("Adding objects..").endLine();

	Drawable* t1 = new Triangle();
	t1->setXYZ(-5, 3, 0);
	_map->addStaticDrawable(t1);

	Drawable* t2 = new Triangle();
	t2->setXYZ(-4, 3, 0);
	t2->rotateXYZ(45, 45, 45);
	_map->addStaticDrawable(t2);

	Drawable* t3 = new Triangle();
	t3->setXYZ(-3, 3, 0);
	t3->rotateXYZ(-80, 0, 0);
	t3->scaleXYZ(1, 2, 1);
	_map->addStaticDrawable(t3);

	Drawable* t4 = new Triangle();
	t4->setXYZ(-2, 6, 0);
	t4->setColor(1, 0.5, 0);
	_map->addStreamDrawable(t4);

	Drawable* c1 = new Cube();
	c1->setXYZ(0, 3, 0);
	c1->setRotationXYZ(45, 45, 45);
	c1->scaleXYZ(2, 2, 2);
	_map->addStaticDrawable(c1);

	Drawable* c2 = new Cube();
	c2->setXYZ(3, 3, 0);
	c2->setRotationXYZ(30, 30, 30);
	c2->scaleXYZ(1, 1, 2);
	c2->setColor(0, 0, 1);
	_map->addStaticDrawable(c2);

	Drawable* c3 = new Cube();
	c3->setXYZ(5, 3, 0);
	c3->setColor(1, 0, 1);
	_map->addStaticDrawable(c3);

	for (int i = 0; i < 1; i++) {
		Drawable* c4 = new Cube();
		c4->setXYZ(i, 8, 0);
		c4->setColor(1, 0, 0);
		_map->addStreamDrawable(c4);
	}

	Drawable* c5 = new Cube();
	c5->setXYZ(2, 6, 0);
	c5->setRotationXYZ(45, 0, 45);
	c5->setColor(0, 1, 0);
	_map->addStreamDrawable(c5);

	//_terrain = new HillTerrain(this, 100, 100, 123456);
	_terrain = new FractalMountainTerrain(this, 128, 128, 123456);
	_terrain->generate();
	_terrain->setScale(1);
	_terrain->setDrawOutline(false);
	_terrain->setDrawFaces(true);
	_terrain->updateDrawables();
	_map->addTerrain(_terrain);

	_mainLight = new LightSource(LightSource::DIRECTIONAL);
	_mainLight->setDirection(1, -0.5, 1);
	_mainLight->setAmbient(0.3, 0.3, 0.3);
	_mainLight->setDiffuse(0.6, 0.6, 0.6);
	_mainLight->setSpecular(0.2, 0.2, 0.2);
	_map->addLightSource(_mainLight);

	_cameraLight = new LightSource(LightSource::SPOTLIGHT);
	_cameraLight->setAmbient(0.4, 0.4, 0.4);
	_cameraLight->setDiffuse(0.6, 0.6, 0.6);
	_cameraLight->setSpecular(0.2, 0.2, 0.2);
	_cameraLight->setBeamAngle(40);
	_map->addLightSource(_cameraLight);
}

void TestGame::initializeTextures() {
	int grass = _textures->registerTexture("textures/grass.png");
	_logger->log("Grass texture index: ").log(grass).endLine();
}

void TestGame::initializeCamera() {
	_camera->setXYZ(0, 1.5, 8);
}

void TestGame::onGameLoop() {
	//_logger->log("FPS: ").log(_fps).endLine();

	handleInput();

	// Snap to terrain
	if (_snapToGround) {
		Vector<float> pos = _terrain->project(
				Vector<float>(_camera->getX(), _camera->getY() - _playerHeight,
						_camera->getZ()), true);
		if (pos.size() > 0)
			_camera->setXYZ(pos[0], pos[1] + _playerHeight, pos[2]);
	}

	_camera->useView();

	_cameraLight->setPosition(_camera->getPosition());
	_cameraLight->setDirection(_camera->getEyeVector());

	for (int i = 0; i < _map->_streamDrawables.size(); i++) {
		_map->_streamDrawables[i]->rotateXYZ(0, 1, 0);
		//_streamDrawables[i]->translateXYZ(0, 0.01, 0);
	}

	_map->update();
	_textures->update();

	_renderer->render();

	float sx = 2.0 / getWindowWidth();
	float sy = 2.0 / getWindowHeight();
	std::string str = "The quick brown fox jumps over the lazy dog!";
	//_renderer->renderText(str, font1, 0, 0, 0.1, 0.1);
	_renderer->renderText(str, _font1, -1 + 8 * sx, 1 - 50 * sy, sx, sy);

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
		if (_cameraLight->isEnabled())
			_cameraLight->setEnabled(false);
		else
			_cameraLight->setEnabled(true);
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		if (_mainLight->isEnabled()) {
			_mainLight->setEnabled(false);
			_renderer->setBackgroundColor(0, 0, 0);
		} else {
			_mainLight->setEnabled(true);
			_renderer->setBackgroundColor(0.8, 1, 1);
		}
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		LightSource* light = new LightSource(LightSource::SPOTLIGHT);
		light->setPosition(_camera->getPosition());
		light->setDirection(_camera->getEyeVector());
		light->setAmbient(0.4, 0.4, 0.4);
		light->setDiffuse(0.6, 0.6, 0.6);
		light->setSpecular(0.2, 0.2, 0.2);
		_lights.push_back(light);
		_map->addLightSource(light);
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		for (int i = 0; i < _lights.size(); i++)
			_map->removeLightSource(_lights[i]);
		_lights.clear();
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		if (_snapToGround)
			_snapToGround = false;
		else
			_snapToGround = true;
	}

	// FIXME Remove
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
		_terrain->scale(1.5);
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
		_terrain->scale((float) 1 / 1.5);
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		_terrain->rotateXYZ(10, 10, 10);
		_terrain->translateXYZ(10, 0, 30);
		_terrain->scaleXYZ(1.5, 2, 1.5);
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

