/*
 * Line.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef COMPONENTS_GLLINE_H_
#define COMPONENTS_GLLINE_H_

#include "GLComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLLine : public GLComponent{
public:
	GLLine(GLVertex v1, GLVertex v2);
	GLLine();
	virtual ~GLLine() {
	}
	static int _type;
};

#endif /* COMPONENTS_GLLINE_H_ */
