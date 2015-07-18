/*
 * Application.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: ericwadkins
 */

#define GLEW_STATIC

#include "Application.h"

std::vector<Application*> Application::_applications;

void error_callback(int error, const char* description) {
	throw description;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
		int mods) {

	// Get the OpenGLApplication context running in the window
	Application* application = nullptr;
	for (int i = 0; i < Application::_applications.size(); i++)
		if (Application::_applications[i]->_window == window)
			application = Application::_applications[i];

	application->_keyboard->dispatchEvent(key, scancode, action, mods);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Handle window resizes
	glViewport(0, 0, width, height);

	// Get the OpenGLApplication context running in the window
	Application* application = nullptr;
	for (int i = 0; i < Application::_applications.size(); i++)
		if (Application::_applications[i]->_window == window)
			application = Application::_applications[i];

	application->_windowWidth = width;
	application->_windowHeight = height;
	application->_camera->updateProjectionMatrices();
}

Application::Application(const char* windowName, int screenSizeX,
		int screenSizeY, bool fullScreen) {
	_application = this;
	_window = nullptr;
	_logger = new Logger();
	_windowName = windowName;
	_windowWidth = screenSizeX;
	_windowHeight = screenSizeY;
	_fullScreen = fullScreen;
	_frameCount = 0;
	_renderer = nullptr;
	_map = nullptr;
	_camera = nullptr;
	_keyboard = nullptr;
	_fps = 0;
	_font1 = FT_Face();

	_applications.push_back(this);
}

void Application::_initializeWindow() {
	// Basic window setup
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);

	// Make the window resizable or non-resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create the window
	if (!_fullScreen)
		_window = glfwCreateWindow(_windowWidth, _windowHeight, _windowName,
		NULL, NULL);
	else
		_window = glfwCreateWindow(_windowWidth, _windowHeight, _windowName,
				glfwGetPrimaryMonitor(), nullptr);

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

void Application::initialize() {

	clock_t start, finish, start2, finish2;

	/*
	 _logger->log("Testing polynomials...").endLine().increaseIndent();
	 start = clock();
	 {
	 //float numArr[] = { -5, 3, -3, 1 };
	 //float numArr[] = { -64, 48, -12, 1 };
	 //float numArr[] = { 1200, -140, -270, 0, 10 };
	 float numArr[] = { -22680, 6966, 25209, -7884, -2521, 934, -9, -16, 1 };
	 //float numArr[] = { 5, 3, 2, -2, 1, 4, 2, 5, -2 };
	 std::vector<float> values(numArr,
	 numArr + sizeof(numArr) / sizeof(numArr[0]));
	 Polynomial<float> p = Polynomial<float>(values, 1);
	 p.print();

	 std::vector<Complex<float> > roots = p.roots();
	 std::cout << "Roots: " << std::endl;
	 for (int i = 0; i < roots.size(); i++)
	 roots[i].print();

	 std::cout << std::endl;

	 float numArr2[] = { -122, 25, 4, -1 };
	 std::vector<float> values2(numArr2,
	 numArr2 + sizeof(numArr2) / sizeof(numArr2[0]));
	 Polynomial<float> p2 = Polynomial<float>(values2, 1);
	 p2.print();

	 (p/p2).print();

	 std::vector<Complex<float> > roots2 = p2.roots();
	 std::cout << "Roots: " << std::endl;
	 for (int i = 0; i < roots2.size(); i++)
	 roots2[i].print();

	 }
	 finish = clock();
	 _logger->log("(Took ").log(
	 (double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
	 " ms)").endLine().decreaseIndent();

	 _logger->log("Testing matrices...").endLine().increaseIndent();
	 start = clock();
	 {
	 {
	 PolynomialMatrix<float> pm = PolynomialMatrix<float>(3, 3);

	 //float numArr[] = { 5, 3, 2, -2, 1, 4, 2, 5, -2 };
	 float numArr[] = { 5, 3, 9, -2, 1, 3, 2, 5, 15 };
	 std::vector<float> values2(numArr,
	 numArr + sizeof(numArr) / sizeof(numArr[0]));
	 pm.setVector(values2);

	 float denArr[] = { 5, 1 };
	 std::vector<float> numCoeffs(denArr,
	 denArr + sizeof(denArr) / sizeof(denArr[0]));

	 Polynomial<float> p = Polynomial<float>(numCoeffs, 1);
	 pm.set(0, 0, p);

	 pm.print();
	 pm.upperTriangular().print();
	 pm.rref().print();
	 std::vector<std::vector<Polynomial<float> > > specialSolutions = pm.specialSolutions();
	 for (int i = 0; i < specialSolutions.size(); i++) {
	 std::cout << "Special solution " << i + 1 << ": ";
	 for (int j = 0; j < specialSolutions[i].size(); j++)
	 std::cout << specialSolutions[i][j].toString() << ", ";
	 std::cout << std::endl;
	 }

	 }

	 std::cout << std::endl << "-------------------" << std::endl
	 << std::endl;

	 {
	 ComplexMatrix<float> cm = ComplexMatrix<float>(3, 3);

	 float numArr[] = { 5, 3, 2, -2, 1, 4, 2, 5, -2 };
	 std::vector<float> values2(numArr,
	 numArr + sizeof(numArr) / sizeof(numArr[0]));
	 cm.setVector(values2);

	 float denArr[] = { 5, 1 };
	 std::vector<float> numCoeffs(denArr,
	 denArr + sizeof(denArr) / sizeof(denArr[0]));

	 Complex<float> c = Complex<float>(numCoeffs, 1);
	 cm.set(0, 0, c);

	 cm.print();
	 cm.upperTriangular().print();
	 cm.determinant().print();
	 }

	 std::cout << std::endl << "-------------------" << std::endl
	 << std::endl;

	 Matrix<float> m1 = Matrix<float>(2, 2);
	 float arr[] = { 2, 1, 1, 1 };
	 //float arr[] = { 4, -4, 8, -4, 4, -8, 8, -8, 16 };
	 //float arr[] = { 5, 3, 2, -2, 1, 4, 2, 5, -2 };
	 //float arr[] = { 5, 25, 2, -2, -10, 4, 2, 10, -2 };
	 //float arr[] = { 5, 0, 2, -2, 0, 4, 2, 0, -2 };
	 std::vector<float> values(arr, arr + sizeof(arr) / sizeof(arr[0]));
	 m1.setVector(values);

	 m1.print();
	 std::vector<Complex<float> > eigenvalues;
	 eigenvalues = m1.eigenvalues();
	 for (int i = 0; i < eigenvalues.size(); i++) {
	 std::cout << "Eigenvalue " << i + 1 << ": ";
	 eigenvalues[i].print();
	 }

	 std::vector<std::vector<Complex<float> > > evectors = m1.eigenvectors();
	 for (int i = 0; i < evectors.size(); i++) {
	 std::cout << "Eigenvector " << i + 1 << ": ";
	 for (int j = 0; j < evectors[i].size(); j++)
	 std::cout << evectors[i][j].toString() << ", ";
	 std::cout << std::endl;
	 }

	 std::cout << std::endl << "-------------------" << std::endl
	 << std::endl;

	 m1 = Matrix<float>(3, 3);
	 float arr2[] = { 5, 25, 2, -2, -10, 4, 2, 10, -2 };
	 //float arr2[] = { 5, 0, 2, -2, 0, 4, 2, 0, -2 };
	 std::vector<float> values2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
	 m1.setVector(values2);

	 m1.print();
	 eigenvalues = m1.eigenvalues();
	 for (int i = 0; i < eigenvalues.size(); i++) {
	 std::cout << "Eigenvalue " << i + 1 << ": ";
	 eigenvalues[i].print();
	 }

	 evectors = m1.eigenvectors();
	 for (int i = 0; i < evectors.size(); i++) {
	 std::cout << "Eigenvector " << i + 1 << ": ";
	 for (int j = 0; j < evectors[i].size(); j++)
	 std::cout << evectors[i][j].toString() << ", ";
	 std::cout << std::endl;
	 }

	 std::cout << std::endl << "-------------------" << std::endl
	 << std::endl;

	 float arr3[] = { 5, 25, 10, -2, -10, -4, 2, 10, 4 };
	 std::vector<float> values3(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
	 m1.setVector(values3);

	 m1.print();
	 eigenvalues = m1.eigenvalues();
	 for (int i = 0; i < eigenvalues.size(); i++) {
	 std::cout << "Eigenvalue " << i + 1 << ": ";
	 eigenvalues[i].print();
	 }

	 evectors = m1.eigenvectors();
	 for (int i = 0; i < evectors.size(); i++) {
	 std::cout << "Eigenvector " << i + 1 << ": ";
	 for (int j = 0; j < evectors[i].size(); j++)
	 std::cout << evectors[i][j].toString() << ", ";
	 std::cout << std::endl;
	 }

	 std::cout << std::endl << "-------------------" << std::endl
	 << std::endl;

	 m1 = Matrix<float>::identity(3);

	 m1.print();
	 eigenvalues = m1.eigenvalues();
	 for (int i = 0; i < eigenvalues.size(); i++)
	 eigenvalues[i].print();

	 evectors = m1.eigenvectors();
	 for (int i = 0; i < evectors.size(); i++) {
	 std::cout << "Eigenvector " << i + 1 << ": ";
	 for (int j = 0; j < evectors[i].size(); j++)
	 std::cout << evectors[i][j].toString() << ", ";
	 std::cout << std::endl;
	 }

	 }
	 finish = clock();
	 _logger->log("(Took ").log(
	 (double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
	 " ms)").endLine().decreaseIndent();


	 //stop("Testing complete");*/

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
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing window..").endLine().increaseIndent();
	start = clock();
	{
		// Creates and setups the window
		_initializeWindow();

		// Creates framebuffer callback
		glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

		initializeWindow();
	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

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
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing FreeType..").endLine().increaseIndent();
	start = clock();
	{
		// Initialize GLEW
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		    stop("FreeType failed to initialize");

		if (FT_New_Face(ft, "fonts/montserrat/Montserrat-Regular.ttf", 0, &_font1))
		    _logger->log("Failed to load font!").endLine();
		FT_Set_Pixel_Sizes(_font1, 0, 24);

		/*
		FT_GlyphSlot glyph;
		if (FT_Load_Char(font1, 'X', FT_LOAD_RENDER)) {
			_logger->log("Could not load character 'X'").endLine();
		}
		else {
			glyph = font1->glyph;
			_logger->log("Loaded character 'X'").endLine().increaseIndent();
			_logger->log("Width: ").log((int)(glyph->bitmap.width)).endLine();
			_logger->log("Height: ").log((int)(glyph->bitmap.rows)).endLine();
			_logger->decreaseIndent();
		}
		*/


	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing display..").endLine().increaseIndent();
	start = clock();
	{
		glClearDepth(1.0);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// To prevent certain artifacts when a character is not rendered exactly on pixel boundaries,
		// we should clamp the texture at the edges, and enable linear interpolation:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		initializeDisplay();
	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing map..").endLine().increaseIndent();
	start = clock();
	{
		_map = new Map(this);
		initializeMap();
	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing renderer..").endLine().increaseIndent();
	start = clock();
	{
		// Create and initialize the renderer
		_renderer = new Renderer(_application);
		_logger->log("Creating shaders..").endLine().increaseIndent();
		start2 = clock();
		_renderer->createShaders();
		finish2 = clock();
		_logger->decreaseIndent().log("(Took ").log(
				(double(finish2) - double(start2)) / CLOCKS_PER_SEC * 1000).log(
				" ms)").endLine();

		_logger->log("Creating VBOs..").endLine().increaseIndent();
		start2 = clock();
		_renderer->createVBOs();
		finish2 = clock();
		_logger->decreaseIndent().log("(Took ").log(
				(double(finish2) - double(start2)) / CLOCKS_PER_SEC * 1000).log(
				" ms)").endLine();
	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing textures..").endLine().increaseIndent();
	start = clock();
	{
		// Create and initialize the camera
		_textures = new Textures(this);
		_textures->initialize();
		initializeTextures();
	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing camera..").endLine().increaseIndent();
	start = clock();
	{
		// Create and initialize the camera
		//_camera = new Camera(this, 1.5, 1.5, 4, -20, 20, 0);
		_camera = new Camera(this, 0, 0, 0, 0, 0, 0);
		_camera->initialize();
		initializeCamera();
	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	_logger->log("Initializing keyboard..").endLine().increaseIndent();
	start = clock();
	{
		// Creates key callback
		glfwSetKeyCallback(_window, key_callback);

		// Create and initialize the keyboard manager
		_keyboard = new Keyboard(this);
	}
	finish = clock();
	_logger->decreaseIndent().log("(Took ").log(
			(double(finish) - double(start)) / CLOCKS_PER_SEC * 1000).log(
			" ms)").endLine();

	// Get info of GPU and supported OpenGL version
	_logger->endLine().log("###").endLine();
	_logger->log("OpenGL version: ").log(glGetString(GL_VERSION)).endLine();
	_logger->log("GLSL version: ").log(glGetString(GL_SHADING_LANGUAGE_VERSION)).endLine();
	_logger->log("Vendor: ").log(glGetString(GL_VENDOR)).endLine();
	_logger->log("Renderer: ").log(glGetString(GL_RENDERER)).endLine();
	_logger->log("###").endLine().endLine();
}

void Application::gameLoop() {

	clock_t lastTime;

	// Game loop, while window close is not requested
	while (!glfwWindowShouldClose(_window)) {

		_frameCount++;
		long currentTime = clock();
		long delta = currentTime - lastTime;
		_fps = CLOCKS_PER_SEC / ((float) delta);

		fpsList.push_back(_fps);
		float avg = 0;
		for (int i = 0; i < fpsList.size(); i++)
			avg += fpsList[i];
		avg /= fpsList.size();
		//std::cout << "* Average FPS: " << avg << std::endl;

		lastTime = clock();

		onGameLoop();
	}
}

int Application::start() {

	int result = -1;
	try {
		try {
			try {
				// Initialization
				_logger->log("*** Starting Application ***").endLine().endLine();
				initialize();

				// Start the game loop
				_logger->log("** Starting game loop **").endLine().endLine();

				gameLoop();

				// Upon exiting the game loop, stop the application
				stop();

			} catch (const char* str) {
				// Fatal error purposely thrown from within the application
				std::string string = std::string(str);
				if (string.find("\n") == std::string::npos)
					_logger->endLine().setIndent(0).log(
							"*** Stopping Application (").log(str).log(") ***").endLine();
				else
					_logger->endLine().setIndent(0).log(
							"*** Stopping Application ***").endLine().log(str).endLine();
			}
		} catch (int e) {
			// Error thrown to signify the end of the application
			if (e == 0) {
				_logger->endLine().setIndent(0).log(
						"*** Stopping Application ***").endLine();
				result = 0;
			} else
				throw;
		}
	} catch (...) {
		// Fatal error caused the application to crash
		_logger->endLine().setIndent(0).log(
				"*** Stopping Application (Unknown reason) ***").endLine();
		throw;
	}

	glfwTerminate();

	return result;

}

void Application::warn(const char* warning) {
	_logger->log("WARNING: ").log(warning).endLine();
}

void Application::stop(const char* reason) {
	throw reason;
}

void Application::stop() {
	throw 0;
}

int Application::getWindowWidth() {
	return _windowWidth;
}

int Application::getWindowHeight() {
	return _windowHeight;
}

bool Application::isFullScreen() {
	return _fullScreen;
}

