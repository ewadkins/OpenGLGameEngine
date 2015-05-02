/*
 * VBO.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef COMPONENTS_VBO_H_
#define COMPONENTS_VBO_H_

#include "../Components/GLLine.h"
#include "../Components/GLTriangle.h"
#include "../Components/Vertex.h"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VBOBase {
public:
	enum Type {
		STATIC, DYNAMIC, STREAM
	};
	virtual ~VBOBase() {
	}
	virtual void clear() {
	}
	virtual void updateData() {
	}
	virtual void pushToBuffer() {
	}
	virtual void create() {
	}
	virtual void draw() {
	}
};

template<typename T>
class VBO: public VBOBase {
public:
	VBO(Type type);
	virtual ~VBO() {
	}
	void add(T* d);
	virtual void clear();
	virtual void updateData();
	virtual void pushToBuffer();
	virtual void create();
	virtual void draw();
private:
	Type _type;
	std::vector<T*> _drawables;
	std::vector<GLfloat> _data;
	GLuint _vao, _vbo;
};

#endif /* COMPONENTS_VBO_H_ */
