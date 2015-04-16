/*
 * Camera.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ericwadkins
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Math/GLMatrix.h"
#include "Math/Matrix.h"
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>

class Application;

class Camera {
public:
	Camera(Application* application, float x, float y, float z,
			float rotationX, float rotationY, float rotationZ);
	virtual ~Camera() {
	}
	void initialize();
	void useView();
	void updateProjectionMatrices();
	void useProjectionMatrix();
	enum ProjectionType {ORTHOGRAPHIC, PERSPECTIVE};
	void setProjectionType(ProjectionType type);
	float getFOV();
	float getNear();
	float getFar();
	void setFOV(float fov);
	void setNear(float near);
	void setFar(float far);
	void translateX(float x);
	void translateY(float y);
	void translateZ(float z);
	void translateXYZ(float x, float y, float z);
	void rotateX(float theta);
	void rotateY(float theta);
	void rotateZ(float theta);
	void rotateXYZ(float thetaX, float thetaY, float thetaZ);
	float getX();
	float getY();
	float getZ();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setXYZ(float x, float y, float z);
	void setRotationX(float rotationX);
	void setRotationY(float rotationY);
	void setRotationZ(float rotationZ);
	void setRotationXYZ(float rotationX, float rotationY, float rotationZ);
private:
	Application* _application;
	float _fov, _near, _far, _x, _y, _z, _rotationX, _rotationY, _rotationZ;
	Matrix<float> _orthographic, _perspective;
	ProjectionType _projectionType;
};

#endif /* CAMERA_H_ */
