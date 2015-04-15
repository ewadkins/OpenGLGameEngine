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
	virtual std::vector<Vertex*>* getVertices() {
		return new std::vector<Vertex*>();
	}
	virtual GLComponent* clone() {
		return new GLComponent();
	}
};

#endif /* GLCOMPONENT_H_ */
