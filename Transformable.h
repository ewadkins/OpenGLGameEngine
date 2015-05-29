/*
 * Transformable.h
 *
 *  Created on: May 29, 2015
 *      Author: ericwadkins
 */

#ifndef TRANSFORMABLE_H_
#define TRANSFORMABLE_H_

class Transformable {
public:
	Transformable();
	virtual ~Transformable() {
	}
	virtual void translateX(float x);
	virtual void translateY(float y);
	virtual void translateZ(float z);
	virtual void translateXYZ(float x, float y, float z);
	virtual void scale(float scale);
	virtual void scaleX(float scaleX);
	virtual void scaleY(float scaleY);
	virtual void scaleZ(float scaleZ);
	virtual void scaleXYZ(float scaleX, float scaleY, float scaleZ);
	virtual void rotateX(float theta);
	virtual void rotateY(float theta);
	virtual void rotateZ(float theta);
	virtual void rotateXYZ(float thetaX, float thetaY, float thetaZ);
	virtual float getX();
	virtual float getY();
	virtual float getZ();
	virtual float getScaleX();
	virtual float getScaleY();
	virtual float getScaleZ();
	virtual float getRotationX();
	virtual float getRotationY();
	virtual float getRotationZ();
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setZ(float z);
	virtual void setXYZ(float x, float y, float z);
	virtual void setScale(float scale);
	virtual void setScaleX(float scaleX);
	virtual void setScaleY(float scaleY);
	virtual void setScaleZ(float scaleZ);
	virtual void setScaleXYZ(float scaleX, float scaleY, float scaleZ);
	virtual void setRotationX(float rotationX);
	virtual void setRotationY(float rotationY);
	virtual void setRotationZ(float rotationZ);
	virtual void setRotationXYZ(float rotationX, float rotationY, float rotationZ);
protected:
	bool _needsUpdating;
	float _x, _y, _z, _scaleX, _scaleY, _scaleZ, _rotationX, _rotationY, _rotationZ;
};

#endif /* TRANSFORMABLE_H_ */
