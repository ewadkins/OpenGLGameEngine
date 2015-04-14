/*
 * GLTriangle.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef DRAWING_GLTRIANGLE_H_
#define DRAWING_GLTRIANGLE_H_

#include "../Drawing/Vertex.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLTriangle {
public:
	GLTriangle(Vertex* v1, Vertex* v2, Vertex* v3);
	virtual ~GLTriangle() {
	}
	virtual std::vector<Vertex*> getVertices();
	static int type;
private:
	Vertex *_v1, *_v2, *_v3;
};

#endif /* DRAWING_GLTRIANGLE_H_ */
