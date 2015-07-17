/*
 * OpenGLApplication.h
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Logger.h"
#include "Render/Renderer.h"
#include "Map/Map.h"
#include "Render/Camera.h"
#include "Render/Textures.h"
#include "Math/Matrix.h"
#include "Input/Keyboard.h"
#include <string>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <freetype.h>

class Application {
public:
	Application(const char* windowName, int screenSizeX, int screenSizeY, bool fullScreen);
	virtual ~Application() {
	}
	int start();
	void warn(const char*);
	void stop(const char*);
	void stop();
	int getWindowWidth();
	int getWindowHeight();
	bool isFullScreen();
	Application* _application;
	GLFWwindow* _window;
	Logger* _logger;
	Renderer* _renderer;
	Map* _map;
	Textures* _textures;
	Camera* _camera;
	Keyboard* _keyboard;
	static std::vector<Application*> _applications;
	friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	friend class Keyboard;
protected:
	int _frameCount;
	int _fps;
	FT_Face _font1;
private:
	void initialize();
	void _initializeWindow();
	virtual void initializeWindow() {
		warn("Missing function: initializeWindow()");
	}
	virtual void initializeDisplay() {
		warn("Missing function: initializeDisplay()");
	}
	virtual void initializeMap() {
		warn("Missing function: initializeMap()");
	}
	virtual void initializeTextures() {
		warn("Missing function: initializeTextures()");
	}
	virtual void initializeCamera() {
		warn("Missing function: initializeCamera()");
	}
	void gameLoop();
	virtual void onGameLoop() {
		warn("Missing function: onGameLoop()");
	}
	virtual void onKeyEvent(int key, int action) {
		warn("Missing function: onKeyEvent(int key, int action)");
	}
	//void updateAverageFPS(float fps);
	const static int VERSION_MAJOR = 4;
	const static int VERSION_MINOR = 1;
	const char* _windowName;
	int _windowWidth;
	int _windowHeight;
	bool _fullScreen;
	std::vector<float> fpsList;
};

#endif /* APPLICATION_H_ */
