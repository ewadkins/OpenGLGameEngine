/*
 * Line.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef GLLINE_H_
#define GLLINE_H_

#include "Vertex.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLLine{
public:
	GLLine(Vertex* v1, Vertex* v2);
	virtual ~GLLine() {
	}
	virtual std::vector<Vertex*> getVertices();
	static int type;
private:
	Vertex* _v1;
	Vertex* _v2;
};

#endif /* GLLINE_H_ */
