/*
 * Main.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#define GLEW_STATIC

#include "Main.h"

void error_callback(int error, const char* description)

{
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
		int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* setupWindow(GLFWwindow *window) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//For windowed application
	window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
	//For fullscreen application
	//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr);

	//If window creation fails, then exit
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Creates an OpenGL context in the window
	glfwMakeContextCurrent(window);

	return window;
}

void setupDisplay() {
    glClearDepth(1.0f);                      // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);               // The Type Of Depth Testing To Do
	glClearColor(0, 0, 0, 1);
}

void OpenGLApplication::initialize() {
	//Initialize GLFW, if it fails, then exit
	if ( !glfwInit() )
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	//Creates error listener
	glfwSetErrorCallback(error_callback);

	_window = setupWindow(_window);

	//Creates key callback
	glfwSetKeyCallback(_window, key_callback);
	//Creates framebuffer callback
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	setupDisplay();


}

int OpenGLApplication::start() {

	initialize();

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	//Game loop, while window close is not requested
	while (!glfwWindowShouldClose(_window)) {

		float ratio;
		int width, height;

		glfwGetFramebufferSize(_window, &width, &height);
		ratio = width / (float) height;

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		//// Render

		//Triangle test

		//FIXME Not drawing the triangle

		// An array of 3 vectors which represents 3 vertices
		static const GLfloat vertices[] = {
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
		};

		// This will identify our vertex buffer
		GLuint vbo;

		// Generate 1 buffer, put the resulting identifier in vbo
		glGenBuffers(1, &vbo);

		// The following commands will talk about our 'vbo' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*) 0            // array buffer offset
				);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		glDisableVertexAttribArray(0);

		////

		//Swap buffers
		glfwSwapBuffers(_window);

		//Processes the events that have been received, then returns
		glfwPollEvents();
		//Puts the thread to sleep until another event is received, used when no need to update continuously
		//glfwWaitEvents();
	}

	glfwTerminate();

	return 0;

}

int main()
{
	OpenGLApplication _application;
	return _application.start();
}
