/*
 * GLComponent.h
 *
 *  Created on: Apr 15, 2015
 *      Author: ericwadkins
 */

#ifndef COMPONENTS_GLCOMPONENT_H_
#define COMPONENTS_GLCOMPONENT_H_

#include "GLVertex.h"
#include "../Math/Vector.h"
#include <vector>

class GLComponent {
public:
	GLComponent();
	virtual ~GLComponent() {
	}
	virtual std::vector<GLVertex> getVertices() {
		return std::vector<GLVertex>();
	}
	virtual void setVertices(std::vector<GLVertex> vertices) {
	}
	void setColor(float r, float g, float b);
};

#endif /* COMPONENTS_GLCOMPONENT_H_ */
