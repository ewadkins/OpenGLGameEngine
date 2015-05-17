/*
 * GLPoint.cpp
 *
 *  Created on: May 8, 2015
 *      Author: ericwadkins
 */

#include "GLPoint.h"

int GLPoint::_type = GL_POINTS;

GLPoint::GLPoint(GLVertex v1) {
	_vertices.push_back(v1);
}

GLPoint::GLPoint() {
}

