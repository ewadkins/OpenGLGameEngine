/*
 * Main.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: ericwadkins
 */

#include "Main.h"

std::vector<OpenGLApplication*> Main::applications;

int main() {

	float arr[] = { 2, 3 };
	std::vector<float> coeffs(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Polynomial<float> p = Polynomial<float>(coeffs, 1);
	p.print();

	(p^2).print();
	(p^3).print();

	/*
	float arr2[] = { 1, -3 };
	std::vector<float> coeffs2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
	Polynomial<float> p2 = Polynomial<float>(coeffs2);
	p2.print();
	*/

	OpenGLApplication* application = new OpenGLApplication(800, 600, false);
	Main::applications.push_back(application);
	int result = application->start();
	std::cout << "Exit code: " << result << std::endl;
	return result;
}

