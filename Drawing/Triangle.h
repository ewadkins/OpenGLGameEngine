/*
 * Triangle.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vertex.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Triangle{
public:
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	virtual ~Triangle() {
	}
	virtual std::vector<Vertex> getVertices();
	static int type;
private:
	Vertex _v1, _v2, _v3;
};

#endif /* TRIANGLE_H_ */
