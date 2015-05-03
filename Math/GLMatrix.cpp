/*
 * GLMatrix.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: ericwadkins
 */

#include "GLMatrix.h"

const float GLMatrix::PI = 3.1415926535897;

// Returns the translation matrix given the desired change in x, y, and z coordinates
Matrix<float> GLMatrix::translationMatrix(float deltaX, float deltaY,
		float deltaZ) {
	Matrix<float> result = Matrix<float>::identity(4);
	result.set(0, 3, deltaX);
	result.set(1, 3, deltaY);
	result.set(2, 3, deltaZ);
	return result;
}

// Returns the scalar matrix given the desired scale in the x, y, and z directions
Matrix<float> GLMatrix::scalarMatrix(float scaleX, float scaleY, float scaleZ) {
	Matrix<float> result = Matrix<float>(4);
	result.set(0, 0, scaleX);
	result.set(1, 1, scaleY);
	result.set(2, 2, scaleZ);
	result.set(3, 3, 1);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the x axis
Matrix<float> GLMatrix::rotationMatrixX(float theta) {
	Matrix<float> result = Matrix<float>(4);
	float rads = theta * PI / 180;
	result.set(0, 0, 1);
	result.set(1, 1, cos(rads));
	result.set(1, 2, -sin(rads));
	result.set(2, 1, sin(rads));
	result.set(2, 2, cos(rads));
	result.set(3, 3, 1);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the y axis
Matrix<float> GLMatrix::rotationMatrixY(float theta) {
	Matrix<float> result = Matrix<float>(4);
	float rads = theta * PI / 180;
	result.set(0, 0, cos(rads));
	result.set(0, 2, sin(rads));
	result.set(1, 1, 1);
	result.set(2, 0, -sin(rads));
	result.set(2, 2, cos(rads));
	result.set(3, 3, 1);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the z axis
Matrix<float> GLMatrix::rotationMatrixZ(float theta) {
	Matrix<float> result = Matrix<float>(4);
	float rads = theta * PI / 180;
	result.set(0, 0, cos(rads));
	result.set(0, 1, -sin(rads));
	result.set(1, 0, sin(rads));
	result.set(1, 1, cos(rads));
	result.set(2, 2, 1);
	result.set(3, 3, 1);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the x, y, and z axes
Matrix<float> GLMatrix::rotationMatrixXYZ(float thetaX, float thetaY,
		float thetaZ) {
	Matrix<float> result = Matrix<float>(4);
	float radsX = thetaX * PI / 180;
	float radsY = thetaY * PI / 180;
	float radsZ = thetaZ * PI / 180;
	result.set(0, 0, cos(radsY) * cos(radsZ));
	result.set(0, 1,
			cos(radsZ) * sin(radsX) * sin(radsY) - cos(radsX) * sin(radsZ));
	result.set(0, 2,
			cos(radsX) * cos(radsZ) * sin(radsY) + sin(radsX) * sin(radsZ));
	result.set(1, 0, cos(radsY) * sin(radsZ));
	result.set(1, 1,
			cos(radsX) * cos(radsZ) + sin(radsX) * sin(radsY) * sin(radsZ));
	result.set(1, 2,
			cos(radsX) * sin(radsY) * sin(radsZ) - cos(radsZ) * sin(radsX));
	result.set(2, 0, -sin(radsY));
	result.set(2, 1, cos(radsY) * sin(radsX));
	result.set(2, 2, cos(radsX) * cos(radsY));
	result.set(3, 3, 1);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the line through (x, y, z) with the direction (u, v, w)
Matrix<float> GLMatrix::rotationMatrixLine(float x, float y, float z, float u,
		float v, float w, float theta) {
	Matrix<float> result = Matrix<float>(4);
	float rads = theta * PI / 180;
	result.set(0, 0,
			(u * u + (v * v + w * w) * cos(rads)) / (u * u + v * v + w * w));
	result.set(0, 1,
			(u * v * (-cos(rads) + 1)
					- w * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(0, 2,
			(u * w * (-cos(rads) + 1)
					+ v * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(0, 3,
			((x * (v * v + w * w) - u * (y * v + z * w)) * (-cos(rads) + 1)
					+ (y * w - z * v) * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 0,
			(u * v * (-cos(rads) + 1)
					+ w * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 1,
			(v * v + (u * u + w * w) * cos(rads)) / (u * u + v * v + w * w));
	result.set(1, 2,
			(v * w * (-cos(rads) + 1)
					- u * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 3,
			((y * (u * u + w * w) - v * (x * u + z * w)) * (-cos(rads) + 1)
					+ (z * u - x * w) * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 0,
			(u * w * (-cos(rads) + 1)
					- v * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 1,
			(v * w * (-cos(rads) + 1)
					+ u * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 2,
			(w * w + (u * u + v * v) * cos(rads)) / (u * u + v * v + w * w));
	result.set(2, 3,
			((z * (u * u + v * v) - w * (x * u + y * v)) * (-cos(rads) + 1)
					+ (x * v - y * u) * sqrt(u * u + v * v + w * w) * sin(rads))
					/ (u * u + v * v + w * w));
	result.set(3, 3, 1);
	return result;
}

Matrix<float> GLMatrix::modelTransformationMatrix(float deltaX, float deltaY,
		float deltaZ, float thetaX, float thetaY, float thetaZ, float scaleX,
		float scaleY, float scaleZ) {
	Matrix<float> result = Matrix<float>(4);
	float radsX = thetaX * PI / 180;
	float radsY = thetaY * PI / 180;
	float radsZ = thetaZ * PI / 180;
	result.set(0, 0, scaleX * cos(radsY) * cos(radsZ));
	result.set(0, 1,
			-scaleY
					* (cos(radsX) * sin(radsZ)
							- cos(radsZ) * sin(radsX) * sin(radsY)));
	result.set(0, 2,
			scaleZ
					* (sin(radsX) * sin(radsZ)
							+ cos(radsX) * cos(radsZ) * sin(radsY)));
	result.set(0, 3, deltaX);
	result.set(1, 0, scaleX * cos(radsY) * sin(radsZ));
	result.set(1, 1,
			scaleY
					* (cos(radsX) * cos(radsZ)
							+ sin(radsX) * sin(radsY) * sin(radsZ)));
	result.set(1, 2,
			-scaleZ
					* (cos(radsZ) * sin(radsX)
							- cos(radsX) * sin(radsY) * sin(radsZ)));
	result.set(1, 3, deltaY);
	result.set(2, 0, -scaleX * sin(radsY));
	result.set(2, 1, scaleY * cos(radsY) * sin(radsX));
	result.set(2, 2, scaleZ * cos(radsX) * cos(radsY));
	result.set(2, 3, deltaZ);
	result.set(3, 3, 1);
	return result;
}

Matrix<float> GLMatrix::cameraTransformationMatrix(float deltaX, float deltaY,
		float deltaZ, float thetaX, float thetaY, float thetaZ) {
	Matrix<float> result = Matrix<float>(4);
	float radsX = thetaX * PI / 180;
	float radsY = thetaY * PI / 180;
	float radsZ = thetaZ * PI / 180;
	result.set(0, 0, cos(radsY) * cos(radsZ));
	result.set(0, 1,
			-(cos(radsX) * sin(radsZ) - cos(radsZ) * sin(radsX) * sin(radsY)));
	result.set(0, 2,
			(sin(radsX) * sin(radsZ) + cos(radsX) * cos(radsZ) * sin(radsY)));
	result.set(1, 0, cos(radsY) * sin(radsZ));
	result.set(1, 1,
			(cos(radsX) * cos(radsZ) + sin(radsX) * sin(radsY) * sin(radsZ)));
	result.set(1, 2,
			-(cos(radsZ) * sin(radsX) - cos(radsX) * sin(radsY) * sin(radsZ)));
	result.set(2, 0, -sin(radsY));
	result.set(2, 1, cos(radsY) * sin(radsX));
	result.set(2, 2, cos(radsX) * cos(radsY));
	result.set(3, 0,
			deltaZ * sin(radsY) - deltaX * cos(radsY) * cos(radsZ)
					- deltaY * cos(radsY) * sin(radsZ));
	result.set(3, 1,
			deltaX
					* (cos(radsX) * sin(radsZ)
							- cos(radsZ) * sin(radsX) * sin(radsY))
					- deltaY
							* (cos(radsX) * cos(radsZ)
									+ sin(radsX) * sin(radsY) * sin(radsZ))
					- deltaZ * cos(radsY) * sin(radsX));
	result.set(3, 2,
			deltaY
					* (cos(radsZ) * sin(radsX)
							- cos(radsX) * sin(radsY) * sin(radsZ))
					- deltaX
							* (sin(radsX) * sin(radsZ)
									+ cos(radsX) * cos(radsZ) * sin(radsY))
					- deltaZ * cos(radsX) * cos(radsY));
	result.set(3, 3, 1);
	return result;
}

// Returns the orthographic projection matrix given the dimensions of the window and the near and far clipping planes
Matrix<float> GLMatrix::orthographicProjectionMatrix(float width, float height,
		float near, float far) {
	Matrix<float> result = Matrix<float>(4);
	result.set(0, 0, 2 / (width));
	result.set(1, 1, 2 / (height));
	result.set(2, 2, -2 / (far - near));
	result.set(2, 3, -(far + near) / (far - near));
	result.set(3, 3, 1);
	return result;
}

// Returns the perspective projection matrix given the x and y field of view and the near and far clipping planes
Matrix<float> GLMatrix::perspectiveProjectionMatrix(float fov, float aspect,
		float near, float far) {
	Matrix<float> result = Matrix<float>(4);
	float f = 1 / tan(fov / 2 * PI / 180);
	result.set(0, 0, f / aspect);
	result.set(1, 1, f);
	result.set(2, 2, -(far + near) / (far - near));
	result.set(2, 3, -1);
	result.set(3, 2, -2 * far * near / (far - near));
	return result;
}

