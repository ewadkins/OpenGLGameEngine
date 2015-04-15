/*
 * Triangle.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef GLTRIANGLE_H_
#define GLTRIANGLE_H_

#include "Vertex.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLTriangle{
public:
	GLTriangle(Vertex* v1, Vertex* v2, Vertex* v3);
	virtual ~GLTriangle() {
	}
	virtual std::vector<Vertex*> getVertices();
	static int type;
private:
	Vertex* _v1;
	Vertex* _v2;
	Vertex* _v3;
};

#endif /* GLTRIANGLE_H_ */
