/*
 * Vertex.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "GLVertex.h"

GLVertex::GLVertex() {
	setPosition(0, 0, 0);
	setColor(0, 0, 0);
	setNormal(0, 0, 0);
	setTexCoords(0, 0, 0);
	_hasColor = false;
	_hasNormal = false;
	_hasTexCoords = false;
}

GLVertex::GLVertex(float x, float y, float z) {
	setPosition(x, y, z);
	setColor(0, 0, 0);
	setNormal(0, 0, 0);
	setTexCoords(0, 0, 0);
	_hasColor = false;
	_hasNormal = false;
	_hasTexCoords = false;
}

GLVertex::GLVertex(float x, float y, float z, float r, float g, float b) {
	setPosition(x, y, z);
	setColor(r, g, b);
	setNormal(0, 0, 0);
	setTexCoords(0, 0, 0);
	_hasColor = true;
	_hasNormal = false;
	_hasTexCoords = false;
}

GLVertex::GLVertex(float x, float y, float z, float r, float g, float b,
		float normX, float normY, float normZ) {
	setPosition(x, y, z);
	setColor(r, g, b);
	setNormal(normX, normY, normZ);
	setTexCoords(0, 0, 0);
	_hasColor = true;
	_hasNormal = true;
	_hasTexCoords = false;
}

GLVertex::GLVertex(float x, float y, float z, float r, float g, float b,
		float normX, float normY, float normZ, float texX, float texY, float texIndex) {
	setPosition(x, y, z);
	setColor(r, g, b);
	setNormal(normX, normY, normZ);
	setTexCoords(texX, texY, texIndex);
	_hasColor = true;
	_hasNormal = true;
	_hasTexCoords = true;
}

GLVertex::GLVertex(std::vector<float> pos) {
	setPosition(pos);
	setColor(0, 0, 0);
	setNormal(0, 0, 0);
	setTexCoords(0, 0, 0);
	_hasColor = false;
	_hasNormal = false;
	_hasTexCoords = false;
}

GLVertex::GLVertex(std::vector<float> pos, std::vector<float> color) {
	setPosition(pos);
	setColor(color);
	setNormal(0, 0, 0);
	setTexCoords(0, 0, 0);
	_hasColor = true;
	_hasNormal = false;
	_hasTexCoords = false;
}

GLVertex::GLVertex(std::vector<float> pos, std::vector<float> color,
		std::vector<float> norm) {
	setPosition(pos);
	setColor(color);
	setNormal(norm);
	setTexCoords(0, 0, 0);
	_hasColor = true;
	_hasNormal = true;
	_hasTexCoords = false;
}

GLVertex::GLVertex(std::vector<float> pos, std::vector<float> color,
		std::vector<float> norm, std::vector<float> tex) {
	setPosition(pos);
	setColor(color);
	setNormal(norm);
	setTexCoords(tex);
	_hasColor = true;
	_hasNormal = true;
	_hasTexCoords = true;
}

void GLVertex::transform(Matrix<float> modelTransformationMatrix,
		Matrix<float> rotationMatrix) {
	Matrix<float> m = Matrix<float>(4, 1);

	std::vector<float> pos = getPosition();
	pos.push_back(1);
	m.setVector(pos);
	m = m << modelTransformationMatrix;
	setPosition(m.get(0, 0), m.get(1, 0), m.get(2, 0));

	if (_hasNormal) {
		std::vector<float> norm = getNormal();
		norm.push_back(1);
		m.setVector(norm);
		m = m << rotationMatrix;
		setNormal(m.get(0, 0), m.get(1, 0), m.get(2, 0));
	}
}

void GLVertex::setPosition(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

void GLVertex::setColor(float r, float g, float b) {
	_r = r;
	_g = g;
	_b = b;
	_hasColor = true;
}

void GLVertex::setNormal(float normX, float normY, float normZ) {
	_normX = normX;
	_normY = normY;
	_normZ = normZ;
	_hasNormal = true;
}

void GLVertex::setTexCoords(float texX, float texY, float texIndex) {
	_texX = texX;
	_texY = texY;
	_texIndex = texIndex;
	_hasTexCoords = true;
}

void GLVertex::setPosition(std::vector<float> pos) {
	_x = pos[0];
	_y = pos[1];
	_z = pos[2];
}

void GLVertex::setColor(std::vector<float> color) {
	_r = color[0];
	_g = color[1];
	_b = color[2];
	_hasColor = true;
}

void GLVertex::setNormal(std::vector<float> norm) {
	_normX = norm[0];
	_normY = norm[1];
	_normZ = norm[2];
	_hasNormal = true;
}

void GLVertex::setTexCoords(std::vector<float> tex) {
	_texX = tex[0];
	_texY = tex[1];
	_texIndex = tex[2];
	_hasTexCoords = true;
}

std::vector<float> GLVertex::getPosition() {
	float arr[] = { _x, _y, _z };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

std::vector<float> GLVertex::getColor() {
	float arr[] = { _r, _g, _b };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

std::vector<float> GLVertex::getNormal() {
	float arr[] = { _normX, _normY, _normZ };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

std::vector<float> GLVertex::getTexCoords() {
	float arr[] = { _texX, _texY, _texIndex };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

std::vector<float> GLVertex::getData() {
	float arr[] = { _x, _y, _z, _r, _g, _b, _normX, _normY, _normZ, _texX, _texY, _texIndex };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

bool GLVertex::hasColor() {
	return _hasColor;
}

bool GLVertex::hasNormal() {
	return _hasNormal;
}

bool GLVertex::hasTexCoords() {
	return _hasTexCoords;
}

GLVertex* GLVertex::clone() {
	return new GLVertex(getPosition(), getColor(), getNormal(), getTexCoords());
}

std::string GLVertex::toString() {
	std::string str = "Vertex{";
	str += "Position(" + std::to_string(_x) + ", " + std::to_string(_y) + ", "
			+ std::to_string(_z) + "), ";
	str += "Color(" + std::to_string(_r) + ", " + std::to_string(_g) + ", "
			+ std::to_string(_b) + "), ";
	str += "Normal(" + std::to_string(_normX) + ", " + std::to_string(_normY)
			+ ", " + std::to_string(_normZ) + "), ";
	str += "TexCoords(" + std::to_string(_texX) + ", " + std::to_string(_texY)
	+ ", " + std::to_string(_texIndex) + ")";
	str += "}";
	return str;
}

