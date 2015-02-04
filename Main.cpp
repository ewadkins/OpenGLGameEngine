/*
 * Main.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


int main(){

	/*// Initialise GLFW
	if( !glfwInit() )
	{
	    fprintf( stderr, "Failed to initialize GLFW\n" );
	    return -1;
	}*/

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//For windowed application
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	//For fullscreen application
	//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	    glfwSetWindowShouldClose(window, GL_TRUE);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}



	glfwTerminate();

	return 0;

}

