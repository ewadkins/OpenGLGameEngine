/*
 * Main.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: ericwadkins
 */

#include "Main.h"

std::vector<OpenGLApplication*> Main::applications;

int main() {

	float arr[] = { 1, 0, 0 };
	std::vector<float> coeffs(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Polynomial<float> p1 = Polynomial<float>(coeffs, 5);
	p1.print();

	float arr2[] = { 2, 3 };
	std::vector<float> coeffs2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
	Polynomial<float> p2 = Polynomial<float>(coeffs2, 2);
	p2.print();

	(p1/p2).print();



	OpenGLApplication* application = new OpenGLApplication(800, 600, false);
	Main::applications.push_back(application);
	int result = application->start();
	std::cout << "Exit code: " << result << std::endl;
	return result;
}

