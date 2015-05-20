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
	TestGame(const char* windowName, int screenSizeX, int screenSizeY, bool fullScreen);
	virtual ~TestGame() {
	}
	virtual void initializeWindow();
	virtual void initializeDisplay();
	virtual void initializeMap();
	virtual void initializeCamera();
	virtual void onGameLoop();
	virtual void onKeyEvent(int key, int action);
	void handleInput();
};

#endif /* TESTGAME_H_ */
