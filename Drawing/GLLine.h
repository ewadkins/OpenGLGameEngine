/*
 * Line.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef GLLINE_H_
#define GLLINE_H_

#include "GLComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLLine : public GLComponent {
public:
	GLLine(Vertex* v1, Vertex* v2);
	virtual ~GLLine() {
	}
	virtual std::vector<Vertex*>* getVertices();
	virtual GLComponent* clone();
	static int _type;
	std::vector<Vertex*>* _vertices;
};

#endif /* GLLINE_H_ */
