/*
 * Triangle.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef GLTRIANGLE_H_
#define GLTRIANGLE_H_

#include "GLComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLTriangle : public GLComponent {
public:
	GLTriangle(Vertex* v1, Vertex* v2, Vertex* v3);
	virtual ~GLTriangle() {
	}
	virtual std::vector<Vertex*>* getVertices();
	virtual GLComponent* clone();
	static int _type;
	std::vector<Vertex*>* _vertices;
};

#endif /* GLTRIANGLE_H_ */
