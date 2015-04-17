/*
 * GLComponent.h
 *
 *  Created on: Apr 15, 2015
 *      Author: ericwadkins
 */

#ifndef GLCOMPONENT_H_
#define GLCOMPONENT_H_

#include "Vertex.h"
#include <vector>

class GLComponent {
public:
	GLComponent();
	virtual ~GLComponent() {
	}
	virtual std::vector<Vertex*> getVertices() {
		return std::vector<Vertex*>();
	}
	virtual void setVertices(std::vector<Vertex*> vertices) {
	}
	virtual GLComponent* clone() {
		return new GLComponent();
	}
	void setColor(float r, float g, float b);
};

#endif /* GLCOMPONENT_H_ */
