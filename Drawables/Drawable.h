/*
 * Drawable.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef DRAWABLES_DRAWABLE_H_
#define DRAWABLES_DRAWABLE_H_

#include <vector>

#include "../Drawing/GLTriangle.h"

class Drawable {
public:
	Drawable();
	virtual ~Drawable() {
	}
	virtual std::vector<GLTriangle> getTriangles() {
		return std::vector<GLTriangle>();
	}
};

#endif /* DRAWABLES_DRAWABLE_H_ */
