/*
 * GLComponent.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: ericwadkins
 */

#include "../Components/GLComponent.h"

GLComponent::GLComponent() {

}

void GLComponent::setColor(float r, float g, float b) {
	std::vector<Vertex*> vertices = getVertices();
	for (int i = 0; i < vertices.size(); i++)
		vertices[i]->setColor(r, g, b);
}

