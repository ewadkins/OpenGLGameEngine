/*
 * OpenGLApplication.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#define GLEW_STATIC

#include "OpenGLApplication.h"

void error_callback(int error, const char* description)

{
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
		int mods) {
	if (action == GLFW_PRESS)
		std::cout << "Key pressed " << char(key) << std::endl;
	if (action == GLFW_RELEASE)
		std::cout << "Key released " << char(key) << std::endl;
	if (action == GLFW_REPEAT)
		std::cout << "Key repeated " << char(key) << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void OpenGLApplication::setupWindow() {
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
	//Make it so you can't resize the window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (!_fullScreen)
		_window = glfwCreateWindow(_screenSizeX, _screenSizeY,
				"OpenGL Tutorial", NULL, NULL);
	else
		_window = glfwCreateWindow(_screenSizeX, _screenSizeY,
				"OpenGL Application", glfwGetPrimaryMonitor(), NULL);

	//If window creation fails, then exit
	if (!_window) {
		std::string s(
				"Window creation failed. Can your hardware handle OpenGL version "
						+ std::to_string(VERSION_MAJOR) + "."
						+ std::to_string(VERSION_MINOR) + "?");
		stop(s.c_str());
	}

	//Creates an OpenGL context in the window
	glfwMakeContextCurrent(_window);

}

void OpenGLApplication::setupDisplay() {
	//Depth buffer setup
	glClearDepth(1.0f);
	//Enables depth testing
	glEnable(GL_DEPTH_TEST);
	//Type of depth testing
	glDepthFunc(GL_LEQUAL);
	glClearColor(0, 0, 0, 1);
}

void OpenGLApplication::initialize() {
	clock_t start, finish;

	start = clock();
	std::cout << "Initializing GLFW.." << std::endl;
	{
		//Initialize GLFW, if it fails, then exit
		if (!glfwInit()) {
			stop("GLFW failed to initialize");
		}

		//Creates error listener
		glfwSetErrorCallback(error_callback);
	}
	finish = clock();
	std::cout << "- (Took "
			<< (double(finish) - double(start)) / CLOCKS_PER_SEC * 1000
			<< " ms)" << std::endl;

	start = clock();
	std::cout << "Setting up window.." << std::endl;
	{
		//Creates and setups the window
		setupWindow();

		//Creates key callback
		glfwSetKeyCallback(_window, key_callback);
		//Creates framebuffer callback
		glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	}
	finish = clock();
	std::cout << "- (Took "
			<< (double(finish) - double(start)) / CLOCKS_PER_SEC * 1000
			<< " ms)" << std::endl;

	start = clock();
	std::cout << "Initializing GLEW.." << std::endl;
	{
		//Initialize GLEW
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			stop("GLEW failed to initialize");
		}
	}
	finish = clock();
	std::cout << "- (Took "
			<< (double(finish) - double(start)) / CLOCKS_PER_SEC * 1000
			<< " ms)" << std::endl;

	start = clock();
	std::cout << "Setting up display.." << std::endl;
	{
		setupDisplay();
	}
	finish = clock();
	std::cout << "- (Took "
			<< (double(finish) - double(start)) / CLOCKS_PER_SEC * 1000
			<< " ms)" << std::endl;

	start = clock();
	std::cout << "Setting up renderer.." << std::endl;
	{
		renderer = new Renderer();
		renderer->initialize();
	}
	finish = clock();
	std::cout << "- (Took "
			<< (double(finish) - double(start)) / CLOCKS_PER_SEC * 1000
			<< " ms)" << std::endl;

	// Get info of GPU and supported OpenGL version
	std::cout << std::endl << "###" << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
			<< std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "###" << std::endl << std::endl;
}

void OpenGLApplication::gameLoop() {

	//Game loop, while window close is not requested
	while (!glfwWindowShouldClose(_window)) {

		static int count = 0;
		count++;
		//std::cout << count << std::endl;

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
		static const GLfloat vertices[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f,
				0.0f, 0.0f, 1.0f, 0.0f, };

		// This will identify our vertex buffer
		GLuint vbo;

		// Generate 1 buffer, put the resulting identifier in vbo
		glGenBuffers(1, &vbo);

		// The following commands will talk about our 'vbo' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_STATIC_DRAW);

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
}

int OpenGLApplication::start() {
	int result = 0;

	std::cout << "*** Starting OpenGLApplication ***" << std::endl << std::endl;
	try {
		try {
			try {

				initialize();

				std::cout << "** Starting game loop **" << std::endl
						<< std::endl;
				gameLoop();

				stop();

			} catch (const char* str) {
				std::cout << std::endl << "*** Stopping OpenGLApplication ("
						<< str << ") ***" << std::endl;
				result = -1;
			}
		} catch (int e) {
			if (e == 0)
				std::cout << std::endl << "*** Stopping OpenGLApplication ***"
						<< std::endl;
			else
				throw;
		}
	} catch (...) {
		std::cout << std::endl
				<< "*** Stopping OpenGLApplication (Unknown reason) ***"
				<< std::endl;
		result = -1;
		throw;
	}

	glfwTerminate();

	return result;

}

void OpenGLApplication::warn(const char* warning) {
	std::cout << std::endl << "* WARNING: " << warning << " *" << std::endl;
}

void OpenGLApplication::stop(const char* reason) {
	throw reason;
}

void OpenGLApplication::stop() {
	throw 0;
}

int main() {
	OpenGLApplication* application = new OpenGLApplication(800, 600, false);
	int result = application->start();
	std::cout << "Exit code: " << result << std::endl;
	return result;
}
