/*
 * Main.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: ericwadkins
 */

#include "Main.h"

std::vector<OpenGLApplication*> Main::applications;

int main() {
	OpenGLApplication* application = new OpenGLApplication(800, 600, false);
	Main::applications.push_back(application);
	int result = application->start();
	std::cout << "Exit code: " << result << std::endl;
	return result;
}

