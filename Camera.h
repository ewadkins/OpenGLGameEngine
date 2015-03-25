/*
 * Camera.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ericwadkins
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "GLMatrix.h"
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>

class OpenGLApplication;

class Camera {
public:
	Camera(OpenGLApplication* application, float x, float y, float z,
			float rotationX, float rotationY, float rotationZ);
	virtual ~Camera() {
	}
	void initialize();
	void useView();
	float getX();
	float getY();
	float getZ();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	void setX();
	void setY();
	void setZ();
	void setRotationX();
	void setRotationY();
	void setRotationZ();
private:
	template<typename T>
	static GLMatrix<T> translate(T deltaX, T deltaY, T deltaZ);
	template<typename T>
	static GLMatrix<T> scale(T scaleX, T scaleY, T scaleZ);
	template<typename T>
	static GLMatrix<T> rotate(T thetaX, T thetaY, T thetaZ);
	OpenGLApplication* _application;
	float _x, _y, _z, _rotationX, _rotationY, _rotationZ;
};

#endif /* CAMERA_H_ */
