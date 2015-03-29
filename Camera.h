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
	void updateProjectionMatrix();
	void useView();
	int getFovX();
	int getFovY();
	float getNear();
	float getFar();
	void setFovX(int fovX);
	void setFovY(int fovY);
	void setNear(float near);
	void setFar(float far);
	void rotateX(float theta);
	void rotateY(float theta);
	void rotateZ(float theta);
	float getX();
	float getY();
	float getZ();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setRotationX(float rotationX);
	void setRotationY(float rotationY);
	void setRotationZ(float rotationZ);
private:
	static GLMatrix<float> translate(float deltaX, float deltaY, float deltaZ);
	static GLMatrix<float> scale(float scaleX, float scaleY, float scaleZ);
	static GLMatrix<float> rotate(float thetaX, float thetaY, float thetaZ);
	static GLMatrix<float> orthographic(int width, int height, float near, float far);
	static GLMatrix<float> perspective(int fovX, int fovY, float near, float far);
	OpenGLApplication* _application;
	int _fovX, _fovY;
	float _near, _far, _x, _y, _z, _rotationX, _rotationY, _rotationZ;
};

#endif /* CAMERA_H_ */
