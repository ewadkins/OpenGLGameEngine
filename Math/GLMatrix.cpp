/*
 * GLMatrix.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: ericwadkins
 */

#include "GLMatrix.h"

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
	float rads = theta * M_PI / 180;
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
	float rads = theta * M_PI / 180;
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
	float rads = theta * M_PI / 180;
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
	float radsX = thetaX * M_PI / 180;
	float radsY = thetaY * M_PI / 180;
	float radsZ = thetaZ * M_PI / 180;
	float sinX = sin(radsX);
	float sinY = sin(radsY);
	float sinZ = sin(radsZ);
	float cosX = cos(radsX);
	float cosY = cos(radsY);
	float cosZ = cos(radsZ);
	result.set(0, 0, cosY * cosZ);
	result.set(0, 1, cosZ * sinX * sinY - cosX * sinZ);
	result.set(0, 2, cosX * cosZ * sinY + sinX * sinZ);
	result.set(1, 0, cosY * sinZ);
	result.set(1, 1, cosX * cosZ + sinX * sinY * sinZ);
	result.set(1, 2, cosX * sinY * sinZ - cosZ * sinX);
	result.set(2, 0, -sinY);
	result.set(2, 1, cosY * sinX);
	result.set(2, 2, cosX * cosY);
	result.set(3, 3, 1);
	return result;
}

// Returns the inverse rotation matrix given the desired change in angle about the x, y, and z axes
Matrix<float> GLMatrix::inverseRotationMatrixXYZ(float thetaX, float thetaY,
		float thetaZ) {
	Matrix<float> result = Matrix<float>(4);
	float radsX = thetaX * M_PI / 180;
	float radsY = thetaY * M_PI / 180;
	float radsZ = thetaZ * M_PI / 180;
	float sinX = sin(radsX);
	float sinY = sin(radsY);
	float sinZ = sin(radsZ);
	float cosX = cos(radsX);
	float cosY = cos(radsY);
	float cosZ = cos(radsZ);
	float sinX2 = sinX * sinX;
	float sinY2 = sinY * sinY;
	float sinZ2 = sinZ * sinZ;
	float cosX2 = cosX * cosX;
	float cosY2 = cosY * cosY;
	float cosZ2 = cosZ * cosZ;
	result.set(0, 0,
			(cosY * cosZ)
					/ (cosY2 * cosZ2 + cosY2 * sinZ2 + cosZ2 * sinY2
							+ sinY2 * sinZ2));
	result.set(0, 1,
			(cosY * sinZ)
					/ (cosY2 * cosZ2 + cosY2 * sinZ2 + cosZ2 * sinY2
							+ sinY2 * sinZ2));
	result.set(0, 2, -sinY / (cosY2 + sinY2));
	result.set(1, 0,
			-(cosX * cosY2 * sinZ - cosZ * sinX * sinY + cosX * sinY2 * sinZ)
					/ (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
							+ cosX2 * cosZ2 * sinY2 + cosX2 * sinY2 * sinZ2
							+ cosY2 * cosZ2 * sinX2 + cosY2 * sinX2 * sinZ2
							+ cosZ2 * sinX2 * sinY2 + sinX2 * sinY2 * sinZ2));
	result.set(1, 1,
			(cosX * cosZ * cosY2 + cosX * cosZ * sinY2 + sinX * sinZ * sinY)
					/ (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
							+ cosX2 * cosZ2 * sinY2 + cosX2 * sinY2 * sinZ2
							+ cosY2 * cosZ2 * sinX2 + cosY2 * sinX2 * sinZ2
							+ cosZ2 * sinX2 * sinY2 + sinX2 * sinY2 * sinZ2));
	result.set(1, 2,
			(cosY * sinX)
					/ (cosX2 * cosY2 + cosX2 * sinY2 + cosY2 * sinX2
							+ sinX2 * sinY2));
	result.set(2, 0,
			(sinX * sinZ * cosY2 + sinX * sinZ * sinY2 + cosX * cosZ * sinY)
					/ (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
							+ cosX2 * cosZ2 * sinY2 + cosX2 * sinY2 * sinZ2
							+ cosY2 * cosZ2 * sinX2 + cosY2 * sinX2 * sinZ2
							+ cosZ2 * sinX2 * sinY2 + sinX2 * sinY2 * sinZ2));
	result.set(2, 1,
			-(cosY2 * cosZ * sinX - cosX * sinY * sinZ + cosZ * sinX * sinY2)
					/ (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
							+ cosX2 * cosZ2 * sinY2 + cosX2 * sinY2 * sinZ2
							+ cosY2 * cosZ2 * sinX2 + cosY2 * sinX2 * sinZ2
							+ cosZ2 * sinX2 * sinY2 + sinX2 * sinY2 * sinZ2));
	result.set(2, 2,
			(cosX * cosY)
					/ (cosX2 * cosY2 + cosX2 * sinY2 + cosY2 * sinX2
							+ sinX2 * sinY2));
	result.set(3, 3, 1);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the line through (x, y, z) with the direction (u, v, w)
Matrix<float> GLMatrix::rotationMatrixLine(float x, float y, float z, float u,
		float v, float w, float theta) {
	Matrix<float> result = Matrix<float>(4);
	float rads = theta * M_PI / 180;
	float sinX = sin(rads);
	float cosX = cos(rads);
	result.set(0, 0,
			(u * u + (v * v + w * w) * cosX) / (u * u + v * v + w * w));
	result.set(0, 1,
			(u * v * (-cosX + 1) - w * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(0, 2,
			(u * w * (-cosX + 1) + v * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(0, 3,
			((x * (v * v + w * w) - u * (y * v + z * w)) * (-cosX + 1)
					+ (y * w - z * v) * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(1, 0,
			(u * v * (-cosX + 1) + w * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(1, 1,
			(v * v + (u * u + w * w) * cosX) / (u * u + v * v + w * w));
	result.set(1, 2,
			(v * w * (-cosX + 1) - u * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(1, 3,
			((y * (u * u + w * w) - v * (x * u + z * w)) * (-cosX + 1)
					+ (z * u - x * w) * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(2, 0,
			(u * w * (-cosX + 1) - v * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(2, 1,
			(v * w * (-cosX + 1) + u * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(2, 2,
			(w * w + (u * u + v * v) * cosX) / (u * u + v * v + w * w));
	result.set(2, 3,
			((z * (u * u + v * v) - w * (x * u + y * v)) * (-cosX + 1)
					+ (x * v - y * u) * sqrt(u * u + v * v + w * w) * sinX)
					/ (u * u + v * v + w * w));
	result.set(3, 3, 1);
	return result;
}

Matrix<float> GLMatrix::modelTransformationMatrix(float deltaX, float deltaY,
		float deltaZ, float thetaX, float thetaY, float thetaZ, float scaleX,
		float scaleY, float scaleZ) {
	Matrix<float> result = Matrix<float>(4);
	float radsX = thetaX * M_PI / 180;
	float radsY = thetaY * M_PI / 180;
	float radsZ = thetaZ * M_PI / 180;
	float sinX = sin(radsX);
	float sinY = sin(radsY);
	float sinZ = sin(radsZ);
	float cosX = cos(radsX);
	float cosY = cos(radsY);
	float cosZ = cos(radsZ);
	result.set(0, 0, scaleX * cosY * cosZ);
	result.set(0, 1, -scaleY * (cosX * sinZ - cosZ * sinX * sinY));
	result.set(0, 2, scaleZ * (sinX * sinZ + cosX * cosZ * sinY));
	result.set(0, 3, deltaX);
	result.set(1, 0, scaleX * cosY * sinZ);
	result.set(1, 1, scaleY * (cosX * cosZ + sinX * sinY * sinZ));
	result.set(1, 2, -scaleZ * (cosZ * sinX - cosX * sinY * sinZ));
	result.set(1, 3, deltaY);
	result.set(2, 0, -scaleX * sinY);
	result.set(2, 1, scaleY * cosY * sinX);
	result.set(2, 2, scaleZ * cosX * cosY);
	result.set(2, 3, deltaZ);
	result.set(3, 3, 1);
	return result;
}

Matrix<float> GLMatrix::inverseModelTransformationMatrix(float deltaX,
		float deltaY, float deltaZ, float thetaX, float thetaY, float thetaZ,
		float scaleX, float scaleY, float scaleZ) {
	Matrix<float> result = Matrix<float>(4);
	float radsX = thetaX * M_PI / 180;
	float radsY = thetaY * M_PI / 180;
	float radsZ = thetaZ * M_PI / 180;
	float sinX = sin(radsX);
	float sinY = sin(radsY);
	float sinZ = sin(radsZ);
	float cosX = cos(radsX);
	float cosY = cos(radsY);
	float cosZ = cos(radsZ);
	float sinX2 = sinX * sinX;
	float sinY2 = sinY * sinY;
	float sinZ2 = sinZ * sinZ;
	float cosX2 = cosX * cosX;
	float cosY2 = cosY * cosY;
	float cosZ2 = cosZ * cosZ;
	result.set(0, 0,
			(cosY * cosZ)
					/ (scaleX
							* (cosY2 * cosZ2 + cosY2 * sinZ2 + cosZ2 * sinY2
									+ sinY2 * sinZ2)));
	result.set(0, 1,
			(cosY * sinZ)
					/ (scaleX
							* (cosY2 * cosZ2 + cosY2 * sinZ2 + cosZ2 * sinY2
									+ sinY2 * sinZ2)));
	result.set(0, 2, -sinY / (scaleX * (cosY2 + sinY2)));
	result.set(0, 3,
			(deltaZ * sinY) / (scaleX * (cosY2 + sinY2))
					- (deltaX * cosY * cosZ)
							/ (scaleX
									* (cosY2 * cosZ2 + cosY2 * sinZ2
											+ cosZ2 * sinY2 + sinY2 * sinZ2))
					- (deltaY * cosY * sinZ)
							/ (scaleX
									* (cosY2 * cosZ2 + cosY2 * sinZ2
											+ cosZ2 * sinY2 + sinY2 * sinZ2)));
	result.set(1, 0,
			-(cosX * cosY2 * sinZ - cosZ * sinX * sinY + cosX * sinY2 * sinZ)
					/ (scaleY
							* (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
									+ cosX2 * cosZ2 * sinY2
									+ cosX2 * sinY2 * sinZ2
									+ cosY2 * cosZ2 * sinX2
									+ cosY2 * sinX2 * sinZ2
									+ cosZ2 * sinX2 * sinY2
									+ sinX2 * sinY2 * sinZ2)));
	result.set(1, 1,
			(cosX * cosZ * cosY2 + cosX * cosZ * sinY2 + sinX * sinZ * sinY)
					/ (scaleY
							* (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
									+ cosX2 * cosZ2 * sinY2
									+ cosX2 * sinY2 * sinZ2
									+ cosY2 * cosZ2 * sinX2
									+ cosY2 * sinX2 * sinZ2
									+ cosZ2 * sinX2 * sinY2
									+ sinX2 * sinY2 * sinZ2)));
	result.set(1, 2,
			(cosY * sinX)
					/ (scaleY
							* (cosX2 * cosY2 + cosX2 * sinY2 + cosY2 * sinX2
									+ sinX2 * sinY2)));
	result.set(1, 3,
			(deltaX
					* (cosX * cosY2 * sinZ - cosZ * sinX * sinY
							+ cosX * sinY2 * sinZ))
					/ (scaleY
							* (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
									+ cosX2 * cosZ2 * sinY2
									+ cosX2 * sinY2 * sinZ2
									+ cosY2 * cosZ2 * sinX2
									+ cosY2 * sinX2 * sinZ2
									+ cosZ2 * sinX2 * sinY2
									+ sinX2 * sinY2 * sinZ2))
					- (deltaY
							* (cosX * cosZ * cosY2 + cosX * cosZ * sinY2
									+ sinX * sinZ * sinY))
							/ (scaleY
									* (cosX2 * cosY2 * cosZ2
											+ cosX2 * cosY2 * sinZ2
											+ cosX2 * cosZ2 * sinY2
											+ cosX2 * sinY2 * sinZ2
											+ cosY2 * cosZ2 * sinX2
											+ cosY2 * sinX2 * sinZ2
											+ cosZ2 * sinX2 * sinY2
											+ sinX2 * sinY2 * sinZ2))
					- (deltaZ * cosY * sinX)
							/ (scaleY
									* (cosX2 * cosY2 + cosX2 * sinY2
											+ cosY2 * sinX2 + sinX2 * sinY2)));
	result.set(2, 0,
			(sinX * sinZ * cosY2 + sinX * sinZ * sinY2 + cosX * cosZ * sinY)
					/ (scaleZ
							* (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
									+ cosX2 * cosZ2 * sinY2
									+ cosX2 * sinY2 * sinZ2
									+ cosY2 * cosZ2 * sinX2
									+ cosY2 * sinX2 * sinZ2
									+ cosZ2 * sinX2 * sinY2
									+ sinX2 * sinY2 * sinZ2)));
	result.set(2, 1,
			-(cosY2 * cosZ * sinX - cosX * sinY * sinZ + cosZ * sinX * sinY2)
					/ (scaleZ
							* (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
									+ cosX2 * cosZ2 * sinY2
									+ cosX2 * sinY2 * sinZ2
									+ cosY2 * cosZ2 * sinX2
									+ cosY2 * sinX2 * sinZ2
									+ cosZ2 * sinX2 * sinY2
									+ sinX2 * sinY2 * sinZ2)));
	result.set(2, 2,
			(cosX * cosY)
					/ (scaleZ
							* (cosX2 * cosY2 + cosX2 * sinY2 + cosY2 * sinX2
									+ sinX2 * sinY2)));
	result.set(2, 3,
			(deltaY
					* (cosY2 * cosZ * sinX - cosX * sinY * sinZ
							+ cosZ * sinX * sinY2))
					/ (scaleZ
							* (cosX2 * cosY2 * cosZ2 + cosX2 * cosY2 * sinZ2
									+ cosX2 * cosZ2 * sinY2
									+ cosX2 * sinY2 * sinZ2
									+ cosY2 * cosZ2 * sinX2
									+ cosY2 * sinX2 * sinZ2
									+ cosZ2 * sinX2 * sinY2
									+ sinX2 * sinY2 * sinZ2))
					- (deltaX
							* (sinX * sinZ * cosY2 + sinX * sinZ * sinY2
									+ cosX * cosZ * sinY))
							/ (scaleZ
									* (cosX2 * cosY2 * cosZ2
											+ cosX2 * cosY2 * sinZ2
											+ cosX2 * cosZ2 * sinY2
											+ cosX2 * sinY2 * sinZ2
											+ cosY2 * cosZ2 * sinX2
											+ cosY2 * sinX2 * sinZ2
											+ cosZ2 * sinX2 * sinY2
											+ sinX2 * sinY2 * sinZ2))
					- (deltaZ * cosX * cosY)
							/ (scaleZ
									* (cosX2 * cosY2 + cosX2 * sinY2
											+ cosY2 * sinX2 + sinX2 * sinY2)));
	result.set(3, 3, 1);
	return result;
}

Matrix<float> GLMatrix::cameraTransformationMatrix(float deltaX, float deltaY,
		float deltaZ, float thetaX, float thetaY, float thetaZ) {
	Matrix<float> result = Matrix<float>(4);
	float radsX = thetaX * M_PI / 180;
	float radsY = thetaY * M_PI / 180;
	float radsZ = thetaZ * M_PI / 180;
	float sinX = sin(radsX);
	float sinY = sin(radsY);
	float sinZ = sin(radsZ);
	float cosX = cos(radsX);
	float cosY = cos(radsY);
	float cosZ = cos(radsZ);
	result.set(0, 0, cosY * cosZ);
	result.set(0, 1, -(cosX * sinZ - cosZ * sinX * sinY));
	result.set(0, 2, (sinX * sinZ + cosX * cosZ * sinY));
	result.set(1, 0, cosY * sinZ);
	result.set(1, 1, (cosX * cosZ + sinX * sinY * sinZ));
	result.set(1, 2, -(cosZ * sinX - cosX * sinY * sinZ));
	result.set(2, 0, -sinY);
	result.set(2, 1, cosY * sinX);
	result.set(2, 2, cosX * cosY);
	result.set(3, 0,
			deltaZ * sinY - deltaX * cosY * cosZ - deltaY * cosY * sinZ);
	result.set(3, 1,
			deltaX * (cosX * sinZ - cosZ * sinX * sinY)
					- deltaY * (cosX * cosZ + sinX * sinY * sinZ)
					- deltaZ * cosY * sinX);
	result.set(3, 2,
			deltaY * (cosZ * sinX - cosX * sinY * sinZ)
					- deltaX * (sinX * sinZ + cosX * cosZ * sinY)
					- deltaZ * cosX * cosY);
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
	float f = 1 / tan(fov / 2 * M_PI / 180);
	result.set(0, 0, f / aspect);
	result.set(1, 1, f);
	result.set(2, 2, -(far + near) / (far - near));
	result.set(2, 3, -1);
	result.set(3, 2, -2 * far * near / (far - near));
	return result;
}

