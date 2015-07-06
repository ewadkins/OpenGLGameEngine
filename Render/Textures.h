/*
 * Textures.h
 *
 *  Created on: Jul 4, 2015
 *      Author: ericwadkins
 */

#ifndef TEXTURES_H_
#define TEXTURES_H_

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <png.h>

class Application;

class Textures {
public:
	Textures(Application* application);
	virtual ~Textures() {
	}
	void initialize();
	void update();
	int registerTexture();
	int registerTexture(const char* filename);
	int loadPNGImage(std::string filename);
	void setUniforms();
	static int TEXTURE_SLOTS[];
	std::vector<GLuint> _textureMap;
	int _dynamic;
private:
	Application* _application;
	bool _textureCountChanged;
};

#endif /* TEXTURES_H_ */
