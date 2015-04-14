/*
 * GLMatrix.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: ericwadkins
 */

#include "../Math/GLMatrix.h"

const float GLMatrix::PI = 3.1415926535897;

// Returns the translation matrix given the desired change in x, y, and z coordinates
Matrix<float> GLMatrix::translationMatrix(float deltaX, float deltaY, float deltaZ) {
	Matrix<float> result = Matrix<float>::identity(4);
	result.set(3, 0, deltaX);
	result.set(3, 1, deltaY);
	result.set(3, 2, deltaZ);
	return result;
}

// Returns the scalar matrix given the desired scale in the x, y, and z directions
Matrix<float> GLMatrix::scalarMatrix(float scaleX, float scaleY, float scaleZ) {
	Matrix<float> result = Matrix<float>::identity(4);
	result.set(0, 0, scaleX);
	result.set(1, 1, scaleY);
	result.set(2, 2, scaleZ);
	return result;
}

// Returns the rotation matrix given the desired change in angle about the x axis
Matrix<float> GLMatrix::rotationMatrixX(float theta) {
	Matrix<float> result = Matrix<float>::identity(4);
	float rads = theta * PI / 180;
	result.set(1, 1, std::cos(rads));
	result.set(1, 2, -std::sin(rads));
	result.set(2, 1, std::sin(rads));
	result.set(2, 2, std::cos(rads));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the y axis
Matrix<float> GLMatrix::rotationMatrixY(float theta) {
	Matrix<float> result = Matrix<float>::identity(4);
	float rads = theta * PI / 180;
	result.set(0, 0, std::cos(rads));
	result.set(0, 2, std::sin(rads));
	result.set(2, 0, -std::sin(rads));
	result.set(2, 2, std::cos(rads));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the z axis
Matrix<float> GLMatrix::rotationMatrixZ(float theta) {
	Matrix<float> result = Matrix<float>::identity(4);
	float rads = theta * PI / 180;
	result.set(0, 0, std::cos(rads));
	result.set(0, 1, -std::sin(rads));
	result.set(1, 0, std::sin(rads));
	result.set(1, 1, std::cos(rads));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the x, y, and z axes
Matrix<float> GLMatrix::rotationMatrixXYZ(float thetaX, float thetaY, float thetaZ) {
	Matrix<float> result = Matrix<float>::identity(4);
	float radsX = thetaX * PI / 180;
	float radsY = thetaY * PI / 180;
	float radsZ = thetaZ * PI / 180;
	result.set(0, 0, std::cos(radsY) * std::cos(radsZ));
	result.set(0, 1,
			cos(radsZ) * std::sin(radsX) * std::sin(radsY) - std::cos(radsX) * std::sin(radsZ));
	result.set(0, 2,
			cos(radsX) * std::cos(radsZ) * std::sin(radsY) + std::sin(radsX) * std::sin(radsZ));
	result.set(1, 0, std::cos(radsY) * std::sin(radsZ));
	result.set(1, 1,
			cos(radsX) * std::cos(radsZ) + std::sin(radsX) * std::sin(radsY) * std::sin(radsZ));
	result.set(1, 2,
			cos(radsX) * std::sin(radsY) * std::sin(radsZ) - std::cos(radsZ) * std::sin(radsX));
	result.set(2, 0, -sin(radsY));
	result.set(2, 1, std::cos(radsY) * std::sin(radsX));
	result.set(2, 2, std::cos(radsX) * std::cos(radsY));
	return result;
}

// Returns the rotation matrix given the desired change in angle about the line through (x, y, z) with the direction (u, v, w)
Matrix<float> GLMatrix::rotationMatrixLine(float x, float y, float z, float u, float v, float w, float theta) {
	Matrix<float> result = Matrix<float>::identity(4);
	float rads = theta * PI / 180;
	result.set(0, 0,
			(u * u + (v * v + w * w) * std::cos(rads)) / (u * u + v * v + w * w));
	result.set(0, 1,
			(u * v * (-cos(rads) + 1)
					- w * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(0, 2,
			(u * w * (-cos(rads) + 1)
					+ v * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(0, 3,
			((x * (v * v + w * w) - u * (y * v + z * w)) * (-cos(rads) + 1)
					+ (y * w - z * v) * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 0,
			(u * v * (-cos(rads) + 1)
					+ w * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 1,
			(v * v + (u * u + w * w) * std::cos(rads)) / (u * u + v * v + w * w));
	result.set(1, 2,
			(v * w * (-cos(rads) + 1)
					- u * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(1, 3,
			((y * (u * u + w * w) - v * (x * u + z * w)) * (-cos(rads) + 1)
					+ (z * u - x * w) * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 0,
			(u * w * (-cos(rads) + 1)
					- v * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 1,
			(v * w * (-cos(rads) + 1)
					+ u * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	result.set(2, 2,
			(w * w + (u * u + v * v) * std::cos(rads)) / (u * u + v * v + w * w));
	result.set(2, 3,
			((z * (u * u + v * v) - w * (x * u + y * v)) * (-cos(rads) + 1)
					+ (x * v - y * u) * std::sqrt(u * u + v * v + w * w) * std::sin(rads))
					/ (u * u + v * v + w * w));
	return result;
}

// Returns the orthographic projection matrix given the dimensions of the window and the near and far clipping planes
Matrix<float> GLMatrix::orthographicProjectionMatrix(float width, float height, float near, float far) {
	Matrix<float> result = Matrix<float>::zeros(4, 4);
	result.set(0, 0, 2 / (width));
	result.set(1, 1, 2 / (height));
	result.set(2, 2, -2 / (far - near));
	result.set(2, 3, -(far + near) / (far - near));
	result.set(3, 3, 1);
	return result;
}

// Returns the perspective projection matrix given the x and y field of view and the near and far clipping planes
Matrix<float> GLMatrix::perspectiveProjectionMatrix(float fov, float aspect, float near, float far) {
	Matrix<float> result = Matrix<float>::zeros(4, 4);
	float f = 1 / std::tan(fov / 2 * PI / 180);
	result.set(0, 0, f / aspect);
	result.set(1, 1, f);
	result.set(2, 2, -(far + near) / (far - near));
	result.set(2, 3, -1);
	result.set(3, 2, -2 * far * near / (far - near));
	return result;
}

