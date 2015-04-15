/*
 * Drawable.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "../Drawing/GLTriangle.h"
#include "../Drawing/GLLine.h"
#include <vector>

class Drawable {
public:
	Drawable();
	virtual ~Drawable() {
	}
	virtual std::vector<GLTriangle*> getTriangles() {
		return std::vector<GLTriangle*>();
	}
	virtual std::vector<GLLine*> getLines() {
		return std::vector<GLLine*>();
	}
};

#endif /* DRAWABLE_H_ */
