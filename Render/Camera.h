/*
 * Camera.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ericwadkins
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Transformable.h"
#include "../Math/GLMatrix.h"
#include "../Math/Matrix.h"
#include "../Math/Vector.h"
//#include <cmath>
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>

class Application;

class Camera: public Transformable {
public:
	Camera(Application* application, float x, float y, float z, float rotationX,
			float rotationY, float rotationZ);
	virtual ~Camera() {
	}
	void initialize();
	void useView();
	Vector<float> getPosition();
	Vector<float> getEyeVector();
	void updateProjectionMatrices();
	void useProjectionMatrix();
	enum ProjectionType {
		ORTHOGRAPHIC, PERSPECTIVE
	};
	void setProjectionType(ProjectionType type);
	float getFOV();
	float getNear();
	float getFar();
	void setFOV(float fov);
	void setNear(float near);
	void setFar(float far);
	virtual void setRotationX(float rotationX);
	virtual void setRotationY(float rotationY);
	virtual void setRotationZ(float rotationZ);
	virtual void setRotationXYZ(float rotationX, float rotationY, float rotationZ);
private:
	Application* _application;
	float _fov, _near, _far;
	Matrix<float> _orthographic, _perspective;
	ProjectionType _projectionType;
};

#endif /* CAMERA_H_ */
