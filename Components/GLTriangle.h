/*
 * Triangle.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef COMPONENTS_GLTRIANGLE_H_
#define COMPONENTS_GLTRIANGLE_H_

#include "GLComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class GLTriangle : public GLComponent{
public:
	GLTriangle(GLVertex v1, GLVertex v2, GLVertex v3);
	GLTriangle();
	virtual ~GLTriangle() {
	}
	Vector<float> getFaceNormal();
	void useFaceNormal();
	static int _type;
};

#endif /* COMPONENTS_GLTRIANGLE_H_ */
