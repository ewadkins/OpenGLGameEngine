/*
 * Main.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: ericwadkins
 */

#include "Main.h"

int main() {

	Application* application = new TestGame("Test Game", 800, 600, false);
	int result = application->start();
	std::cout << "Exit code: " << result << std::endl;
	return result;
}

