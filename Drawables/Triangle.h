/*
 * Triangle.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Drawable.h"

class Triangle: public Drawable {
public:
	Triangle();
	Triangle(GLVertex v1, GLVertex v2, GLVertex v3);
	Triangle(Triangle* other);
	virtual ~Triangle() {
	}
	virtual Drawable* clone();
};

#endif /* TRIANGLE_H_ */
