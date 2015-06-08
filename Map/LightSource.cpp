/*
 * LightSource.cpp
 *
 *  Created on: May 23, 2015
 *      Author: ericwadkins
 */

#include "LightSource.h"

const int LightSource::POINT = 0;
const int LightSource::DIRECTIONAL = 1;
const int LightSource::SPOTLIGHT = 2;

LightSource::LightSource(int type) {
	_type = type;
	_position = Vector<float>(0, 0, 0);
	_direction = Vector<float>(0, 0, 0);
	_ambient = Vector<float>(0, 0, 0);
	_diffuse = Vector<float>(0, 0, 0);
	_specular = Vector<float>(0, 0, 0);
	_range = 30;
	_beamAngle = 35;
	_enabled = true;
	_needsUpdating = true;
}

LightSource::LightSource(float x, float y, float z) {
	_type = POINT;
	_position = Vector<float>(x, y, z);
	_direction = Vector<float>(0, 0, 0);
	_ambient = Vector<float>(0, 0, 0);
	_diffuse = Vector<float>(0, 0, 0);
	_specular = Vector<float>(0, 0, 0);
	_range = 30;
	_beamAngle = 35;
	_enabled = true;
	_needsUpdating = true;
}

void LightSource::setType(int type) {
	_type = type;
}

void LightSource::setPosition(float x, float y, float z) {
	_position = Vector<float>(x, y, z);
	_needsUpdating = true;
}

void LightSource::setPosition(Vector<float> pos) {
	_position = pos;
	_needsUpdating = true;
}

void LightSource::setDirection(float u, float v, float w) {
	_direction = Vector<float>(u, v, w);
	_needsUpdating = true;
}

void LightSource::setDirection(Vector<float> dir) {
	_direction = dir;
	_needsUpdating = true;
}

void LightSource::setAmbient(float r, float g, float b) {
	_ambient = Vector<float>(r, g, b);
	_needsUpdating = true;
}

void LightSource::setAmbient(Vector<float> color) {
	_ambient = color;
	_needsUpdating = true;
}

void LightSource::setDiffuse(float r, float g, float b) {
	_diffuse = Vector<float>(r, g, b);
	_needsUpdating = true;
}

void LightSource::setDiffuse(Vector<float> color) {
	_diffuse = color;
	_needsUpdating = true;
}

void LightSource::setSpecular(float r, float g, float b) {
	_specular = Vector<float>(r, g, b);
	_needsUpdating = true;
}

void LightSource::setSpecular(Vector<float> color) {
	_specular = color;
	_needsUpdating = true;
}

void LightSource::setRange(float range) {
	_range = range;
	_needsUpdating = true;
}

void LightSource::setBeamAngle(float beamAngle) {
	_beamAngle = beamAngle;
	_needsUpdating = true;
}

void LightSource::setEnabled(bool enabled) {
	_enabled = enabled;
	_needsUpdating = true;
}

int LightSource::getType() {
	return _type;
}

Vector<float> LightSource::getPosition() {
	return _position;
}

Vector<float> LightSource::getDirection() {
	return _direction;
}

Vector<float> LightSource::getAmbient() {
	return _ambient;
}

Vector<float> LightSource::getDiffuse() {
	return _diffuse;
}

Vector<float> LightSource::getSpecular() {
	return _specular;
}

float LightSource::getRange() {
	return _range;
}

float LightSource::getBeamAngle() {
	return _beamAngle;
}

bool LightSource::isEnabled() {
	return _enabled;
}

