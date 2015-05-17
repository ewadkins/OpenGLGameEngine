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
	virtual ~GLComponent() {
	}
	void setColor(float r, float g, float b);
	std::vector<GLVertex> _vertices;
};

#endif /* COMPONENTS_GLCOMPONENT_H_ */
