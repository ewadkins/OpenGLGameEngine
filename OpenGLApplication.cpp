/*
 * OpenGLApplication.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#define GLEW_STATIC

#include "OpenGLApplication.h"
#include "Main.h"

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
		int mods) {

	// Get the OpenGLApplication context running in the window
	OpenGLApplication* application = nullptr;
	for (int i = 0; i < Main::applications.size(); i++)
		if (Main::applications[i]->_window == window)
			application = Main::applications[i];

	application->_keyboard->dispatchEvent(key, scancode, action, mods);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Handle window resizes
	glViewport(0, 0, width, height);

	// Get the OpenGLApplication context running in the window
	OpenGLApplication* application = nullptr;
	for (int i = 0; i < Main::applications.size(); i++)
		if (Main::applications[i]->_window == window)
			application = Main::applications[i];

	application->_windowSizeX = width;
	application->_windowSizeY = height;
	application->_camera->updateProjectionMatrices();
}

OpenGLApplication::OpenGLApplication(int screenSizeX, int screenSizeY,
		bool fullScreen) {
	_application = this;
	_window = nullptr;
	_logger = new Logger();
	_windowSizeX = screenSizeX;
	_windowSizeY = screenSizeY;
	_fullScreen = fullScreen;
	_renderer = nullptr;
	_camera = nullptr;
	_keyboard = nullptr;
	_averageFPS = 0;
}

void OpenGLApplication::setupWindow() {
	// Basic window setup
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);

	// Make the window non-resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create the window
	if (!_fullScreen)
		_window = glfwCreateWindow(_windowSizeX, _windowSizeY,
				"OpenGL Application", NULL, NULL);
	else
		_window = glfwCreateWindow(_windowSizeX, _windowSizeY,
				"OpenGL Application", glfwGetPrimaryMonitor(), NULL);

	// If window creation fails, then exit
	if (!_window) {
		std::string s =
				"Window creation failed. Can your hardware handle OpenGL version "
						+ std::to_string(VERSION_MAJOR) + "."
						+ std::to_string(VERSION_MINOR) + "?";
		std::cout << s.c_str() << std::endl;
		// FIXME Error message
		stop(s.c_str());
	}

	// Creates an OpenGL context in the window
	glfwMakeContextCurrent(_window);

}

void OpenGLApplication::setupDisplay() {
	// Depth buffer setup
	glClearDepth(1.0f);

	// Enables depth testing
	glEnable(GL_DEPTH_TEST);

	// Type of depth testing
	glDepthFunc(GL_LEQUAL);

	// Sets background color
	glClearColor(1, 1, 1, 1);
}

void OpenGLApplication::initialize() {

	clock_t start, finish;

	_logger->log("Testing polynomials...").endLine().increaseIndent();
	start = clock();
	{

		float numArr[] = { -6 };
		std::vector<float> numCoeffs(numArr,
				numArr + sizeof(numArr) / sizeof(numArr[0]));
		float denArr[] = { 0, 1 };
		std::vector<float> denCoeffs(denArr,
				denArr + sizeof(denArr) / sizeof(denArr[0]));
		Polynomial<float> p = Polynomial<float>(numCoeffs, denCoeffs);

		float numArr2[] = { 5 };
		std::vector<float> numCoeffs2(numArr2,
				numArr2 + sizeof(numArr2) / sizeof(numArr2[0]));
		float denArr2[] = { 1 };
		std::vector<float> denCoeffs2(denArr2,
				denArr2 + sizeof(denArr2) / sizeof(denArr2[0]));
		Polynomial<float> p2 = Polynomial<float>(numCoeffs2, denCoeffs2);

		float numArr3[] = { -6, 5 };
		std::vector<float> numCoeffs3(numArr3,
				numArr3 + sizeof(numArr3) / sizeof(numArr3[0]));
		float denArr3[] = { 0, 1 };
		std::vector<float> denCoeffs3(denArr3,
				denArr3 + sizeof(denArr3) / sizeof(denArr3[0]));
		Polynomial<float> p3 = Polynomial<float>(numCoeffs3, denCoeffs3);

		_logger->log("p:").endLine().increaseIndent().log(p).endLine().decreaseIndent();
		_logger->log("p2:").endLine().increaseIndent().log(p2).endLine().decreaseIndent();
		_logger->log("p + p2:").endLine().increaseIndent().log(p + p2).endLine().decreaseIndent();
		_logger->log("p * p2:").endLine().increaseIndent().log(p * p2).endLine().decreaseIndent();
		_logger->log("p / p2:").endLine().increaseIndent().log(p / p2).endLine().decreaseIndent();
		_logger->log("p3:").endLine().increaseIndent().log(p3).endLine().decreaseIndent();

	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	_logger->log("Testing matrices...").endLine().increaseIndent();
	start = clock();
	{

		Matrix<float> m1 = Matrix<float>(3, 3);
		float arr[] = { 5, 3, 2, -2, 1, 4, 2, 5, -2 };
		std::vector<float> values(arr, arr + sizeof(arr) / sizeof(arr[0]));
		m1.setVector(values);

		m1.print();
		m1.upperTriangular().print();
		std::cout << m1.determinant() << std::endl;

		std::cout << std::endl << "-------------------" << std::endl
				<< std::endl;

		PolynomialMatrix<float> m2 = PolynomialMatrix<float>(3, 3);
		float arr2[] = { 5, 3, 2, -2, 1, 4, 2, 5, -2 };
		std::vector<float> values2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
		m2.setVector(values2);

		float arr3[] = { 5, 1 };
		std::vector<float> numCoeffs(arr3,
				arr3 + sizeof(arr3) / sizeof(arr3[0]));
		Polynomial<float> p = Polynomial<float>(numCoeffs, 1);
		m2.set(0, 0, p);

		m2.print();
		m2.upperTriangular().print();
		m2.determinant().print();
		std::cout << m2.determinant().value(0) << std::endl;

		std::cout << std::endl << "-------------------" << std::endl
				<< std::endl;

		m1.print();
		m1.eigenvalues();

	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	//stop("Testing complete");

	_logger->log("Initializing GLFW..").endLine().increaseIndent();
	start = clock();
	{
		// Initialize GLFW, if it fails, then exit
		if (!glfwInit()) {
			stop("GLFW failed to initialize");
		}

		// Creates error listener
		glfwSetErrorCallback(error_callback);
	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	_logger->log("Setting up window..").endLine().increaseIndent();
	start = clock();
	{
		// Creates and setups the window
		setupWindow();

		// Creates key callback
		glfwSetKeyCallback(_window, key_callback);

		// Creates framebuffer callback
		glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	_logger->log("Initializing GLEW..").endLine().increaseIndent();
	start = clock();
	{
		// Initialize GLEW
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			stop("GLEW failed to initialize");
		}
	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	_logger->log("Setting up display..").endLine().increaseIndent();
	start = clock();
	{
		// Setup the display
		setupDisplay();
	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	_logger->log("Setting up renderer..").endLine().increaseIndent();
	start = clock();
	{
		// Create and initialize the renderer
		_renderer = new Renderer(_application);
		_renderer->initialize();
	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	_logger->log("Setting up camera..").endLine().increaseIndent();
	start = clock();
	{
		// Create and initialize the camera
		_camera = new Camera(this, 1.5, 1.5, 4, -20, 20, 0);
		//_camera = new Camera(this, 0, 0, 0, 0, 0, 0);
		_camera->initialize();
	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	_logger->log("Setting up keyboard..").endLine().increaseIndent();
	start = clock();
	{
		// Create and initialize the keyboard manager
		_keyboard = new Keyboard(this);
	}
	finish = clock();
	_logger->log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine().decreaseIndent();

	// Get info of GPU and supported OpenGL version
	_logger->endLine().log("###").endLine();
	_logger->log("OpenGL version: ").log(glGetString(GL_VERSION)).endLine();
	_logger->log("GLSL version: ").log(glGetString(GL_SHADING_LANGUAGE_VERSION)).endLine();
	_logger->log("Vendor: ").log(glGetString(GL_VENDOR)).endLine();
	_logger->log("Renderer: ").log(glGetString(GL_RENDERER)).endLine();
	_logger->log("###").endLine().endLine();
}

void OpenGLApplication::gameLoop() {

	clock_t lastTime;

	// Game loop, while window close is not requested
	while (!glfwWindowShouldClose(_window)) {

		long currentTime = clock();
		long delta = currentTime - lastTime;
		float fps = CLOCKS_PER_SEC / ((float) delta);
		updateAverageFPS(fps);
		_logger->log("FPS: ").log((int) _averageFPS).endLine();
		lastTime = clock();

		static int count = 0;
		count++;

		_keyboard->update();

		//_camera->translateXYZ(0, 0, -0.01);
		//_camera->rotateXYZ(0, -1, 0);
		_camera->useView();

		_renderer->render();
		_renderer->display();

	}
}

int OpenGLApplication::start() {

	int result = -1;
	try {
		try {
			try {
				// Initialization
				_logger->log("*** Starting OpenGLApplication ***").endLine().endLine();
				initialize();

				// Start the game loop
				_logger->log("** Starting game loop **").endLine().endLine();

				gameLoop();

				// Upon exiting the game loop, stop the application
				stop();

			} catch (const char* str) {
				// Fatal error purposely thrown from within the application
				_logger->endLine().setIndent(0).log(
						"*** Stopping OpenGLApplication (").log(str).log(
						") ***").endLine();

			}
		} catch (int e) {
			// Error thrown to signify the end of the application
			if (e == 0) {
				_logger->endLine().setIndent(0).log(
						"*** Stopping OpenGLApplication ***").endLine();
				result = 0;
			} else
				throw;
		}
	} catch (...) {
		// Fatal error caused the application to crash
		_logger->endLine().setIndent(0).log(
				"*** Stopping OpenGLApplication (Unknown reason) ***").endLine();
		throw;
	}

	glfwTerminate();

	return result;

}

void OpenGLApplication::warn(const char* warning) {
	// Logs a warning message
	_logger->endLine().log("* WARNING: ").log(warning).log(" *").endLine();
}

void OpenGLApplication::stop(const char* reason) {
	throw reason;
}

void OpenGLApplication::stop() {
	throw 0;
}

void OpenGLApplication::updateAverageFPS(float fps) {

	static long count = 0;
	int minData = std::max(1, std::min(10, (int) fps));
	if (fpsList.size() < minData)
		fpsList.push_back(fps);
	else {
		count++;
		fpsList.erase(fpsList.begin());
		fpsList.push_back(fps);

		double average = 0;
		for (int i = 0; i < fpsList.size(); i++)
			average += fpsList[i];
		average /= fpsList.size();
		_averageFPS = average;
	}
	if (count == 0)
		_averageFPS = fps;
}
