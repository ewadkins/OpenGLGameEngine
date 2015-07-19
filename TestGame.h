/*
 * TestGame.h
 *
 *  Created on: May 19, 2015
 *      Author: ericwadkins
 */

#ifndef TESTGAME_H_
#define TESTGAME_H_

#include "Application.h"
#include <cmath>

class TestGame: public Application {
public:
	TestGame(const char* windowName, int screenSizeX, int screenSizeY, bool fullScreen = false);
	virtual ~TestGame() {
	}
	virtual void initializeWindow();
	virtual void initializeDisplay();
	virtual void initializeMap();
	virtual void initializeTextures();
	virtual void initializeCamera();
	virtual void onGameLoop();
	virtual void onKeyEvent(int key, int action);
	void handleInput();
private:
	Terrain* _terrain;
	LightSource* _mainLight;
	LightSource* _cameraLight;
	std::vector<LightSource*> _lights;
	float _playerHeight;
	bool _snapToGround;
};

#endif /* TESTGAME_H_ */
