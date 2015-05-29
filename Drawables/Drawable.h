/*
 * Drawable.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "../Transformable.h"
#include "../Components/GLTriangle.h"
#include "../Components/GLLine.h"
#include "../Components/GLPoint.h"
#include "../Components/GLVertex.h"
#include "../Math/Matrix.h"
#include "../Math/GLMatrix.h"
#include <vector>

class Drawable: public Transformable {
public:
	Drawable();
	Drawable(Drawable* other);
	virtual ~Drawable() {
	}
	virtual Drawable* clone() {
		return new Drawable();
	}
	void cloneComponents(Drawable* other);
	std::vector<GLTriangle> getTransformedTriangles();
	std::vector<GLLine> getTransformedLines();
	std::vector<GLPoint> getTransformedPoints();
	void setColor(float r, float g, float b);
	void setOutlineColor(float r, float g, float b);
	bool getDrawFaces();
	void setDrawFaces(bool drawFaces);
	bool getDrawOutline();
	void setDrawOutline(bool drawOutline);
	std::vector<GLTriangle> _triangles;
	std::vector<GLLine> _lines;
	std::vector<GLPoint> _points;
protected:
	void applyTransformations();
	Drawable* _transformed;
	bool _drawOutline;
	bool _drawFaces;
};

#endif /* DRAWABLE_H_ */
