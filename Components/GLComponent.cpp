/*
 * GLComponent.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: ericwadkins
 */

#include "GLComponent.h"

void GLComponent::setColor(float r, float g, float b) {
	for (int i = 0; i < _vertices.size(); i++)
		_vertices[i].setColor(r, g, b);
}
