/*
 * VBO.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef VBO_H_
#define VBO_H_

#include "Vertex.h"
#include "Triangle.h"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VBOBase {
public:
	enum Type {STATIC, DYNAMIC};
	virtual ~VBOBase() {
	}
	virtual void updateData() {};
	virtual void create() {std::cout << "Creating base" << std::endl;};
	virtual void draw() {std::cout << "Drawing base" << std::endl;};
};

template<typename T>
class VBO : public VBOBase {
public:
	VBO(Type type);
	virtual ~VBO() {
	}
	void add(T d);
	virtual void updateData();
	virtual void create();
	virtual void draw();
private:
	Type _type;
	std::vector<T> _drawables;
	std::vector<GLfloat> _data;
	GLuint _vao, _vbo;
};

#endif /* VBO_H_ */
