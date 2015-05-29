/*
 * GLMatrix.h
 *
 *  Created on: Apr 5, 2015
 *      Author: ericwadkins
 */

#ifndef GLMATRIX_H_
#define GLMATRIX_H_

#include "Matrix.h"
#include "PolynomialMatrix.h"

class GLMatrix {
public:
	static Matrix<float> translationMatrix(float deltaX, float deltaY,
			float deltaZ);
	static Matrix<float> scalarMatrix(float scaleX, float scaleY, float scaleZ);
	static Matrix<float> rotationMatrixX(float theta);
	static Matrix<float> rotationMatrixY(float theta);
	static Matrix<float> rotationMatrixZ(float theta);
	static Matrix<float> rotationMatrixXYZ(float thetaX, float thetaY,
			float thetaZ);
	static Matrix<float> inverseRotationMatrixXYZ(float thetaX, float thetaY,
			float thetaZ);
	static Matrix<float> rotationMatrixLine(float a, float b, float c, float u,
			float v, float w, float theta);
	static Matrix<float> modelTransformationMatrix(float deltaX, float deltaY,
			float deltaZ, float thetaX, float thetaY, float thetaZ,
			float scaleX, float scaleY, float scaleZ);
	static Matrix<float> inverseModelTransformationMatrix(float deltaX, float deltaY,
			float deltaZ, float thetaX, float thetaY, float thetaZ,
			float scaleX, float scaleY, float scaleZ);
	static Matrix<float> cameraTransformationMatrix(float deltaX, float deltaY,
			float deltaZ, float thetaX, float thetaY, float thetaZ);
	static Matrix<float> orthographicProjectionMatrix(float width, float height,
			float near, float far);
	static Matrix<float> perspectiveProjectionMatrix(float fov, float aspect,
			float near, float far);
};

#endif /* GLMATRIX_H_ */
