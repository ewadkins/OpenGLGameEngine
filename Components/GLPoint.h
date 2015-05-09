/*
 * GLPoint.h
 *
 *  Created on: May 8, 2015
 *      Author: ericwadkins
 */

#ifndef GLPOINT_H_
#define GLPOINT_H_

#include "GLComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLPoint : public GLComponent{
public:
	GLPoint(GLVertex v1);
	GLPoint();
	virtual ~GLPoint() {
	}
	virtual std::vector<GLVertex> getVertices();
	virtual void setVertices(std::vector<GLVertex> vertices);
	static int _type;
private:
	std::vector<GLVertex> _vertices;
};

#endif /* GLPOINT_H_ */
