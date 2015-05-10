/*
 * Drawable.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "../Components/GLTriangle.h"
#include "../Components/GLLine.h"
#include "../Components/GLPoint.h"
#include "../Components/GLVertex.h"
#include "../Math/Matrix.h"
#include "../Math/GLMatrix.h"
#include <vector>

class Drawable {
public:
	Drawable();
	virtual ~Drawable() {
	}
	virtual Drawable* clone() {
		return new Drawable();
	}
	std::vector<GLTriangle> getTriangles();
	std::vector<GLLine> getLines();
	std::vector<GLPoint> getPoints();
	std::vector<GLTriangle> getTransformedTriangles();
	std::vector<GLLine> getTransformedLines();
	std::vector<GLPoint> getTransformedPoints();
	void setColor(float r, float g, float b);
	void setOutlineColor(float r, float g, float b);
	bool getDrawFaces();
	void setDrawFaces(bool drawFaces);
	bool getDrawOutline();
	void setDrawOutline(bool drawOutline);
	void translateX(float x);
	void translateY(float y);
	void translateZ(float z);
	void translateXYZ(float x, float y, float z);
	void scaleX(float scaleX);
	void scaleY(float scaleY);
	void scaleZ(float scaleZ);
	void scaleXYZ(float scaleX, float scaleY, float scaleZ);
	void rotateX(float theta);
	void rotateY(float theta);
	void rotateZ(float theta);
	void rotateXYZ(float thetaX, float thetaY, float thetaZ);
	float getX();
	float getY();
	float getZ();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setXYZ(float x, float y, float z);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setScaleZ(float scaleZ);
	void setScaleXYZ(float scaleX, float scaleY, float scaleZ);
	void setRotationX(float rotationX);
	void setRotationY(float rotationY);
	void setRotationZ(float rotationZ);
	void setRotationXYZ(float rotationX, float rotationY, float rotationZ);
	std::vector<GLTriangle> _triangles;
	std::vector<GLLine> _lines;
	std::vector<GLPoint> _points;
protected:
	void applyTransformations();
	Drawable* _transformed;
	bool _needsUpdating;
	bool _drawOutline;
	bool _drawFaces;
private:
	float _x, _y, _z, _scaleX, _scaleY, _scaleZ, _rotationX, _rotationY, _rotationZ;
};

#endif /* DRAWABLE_H_ */
