/*
 * Vertex.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "../Drawing/Vertex.h"

Vertex::Vertex() {
	_x = 0;
	_y = 0;
	_z = 0;
	_r = 0;
	_g = 0;
	_b = 0;
	_normX = 0;
	_normY = 0;
	_normZ = 0;
	_texX = 0;
	_texY = 0;
}

Vertex::Vertex(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
	_r = 0;
	_g = 0;
	_b = 0;
	_normX = 0;
	_normY = 0;
	_normZ = 0;
	_texX = 0;
	_texY = 0;
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b) {
	_x = x;
	_y = y;
	_z = z;
	_r = r;
	_g = g;
	_b = b;
	_normX = 0;
	_normY = 0;
	_normZ = 0;
	_texX = 0;
	_texY = 0;
}

void Vertex::setPosition(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

void Vertex::setColor(float r, float g, float b) {
	_r = r;
	_g = g;
	_b = b;
}

void Vertex::setNormal(float normX, float normY, float normZ) {
	_normX = normX;
	_normY = normY;
	_normZ = normZ;
}

void Vertex::setTexCoords(float texX, float texY) {
	_texX = texX;
	_texY = texY;
}

std::vector<float> Vertex::getPosition() {
	float arr[] = { _x, _y, _z };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

std::vector<float> Vertex::getColor() {
	float arr[] = { _r, _g, _b };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

std::vector<float> Vertex::getNormal() {
	float arr[] = { _normX, _normY, _normZ };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

std::vector<float> Vertex::getTexCoords() {
	float arr[] = { _texX, _texY };
	std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	return vec;
}

