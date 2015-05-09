/*
 * GLComponent.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: ericwadkins
 */

#include "GLComponent.h"

GLComponent::GLComponent() {

}

void GLComponent::setColor(float r, float g, float b) {
	std::vector<GLVertex> vertices = getVertices();
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].setColor(r, g, b);
	setVertices(vertices);
}
