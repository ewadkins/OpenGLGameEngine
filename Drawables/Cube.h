/*
 * Cube.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Drawable.h"

class Cube: public Drawable {
public:
	Cube();
	Cube(Cube* other);
	virtual ~Cube() {
	}
	virtual Drawable* clone();
};

#endif /* CUBE_H_ */
