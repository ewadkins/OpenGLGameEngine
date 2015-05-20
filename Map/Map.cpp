/*
 * Map.cpp
 *
 *  Created on: May 8, 2015
 *      Author: ericwadkins
 */

#include "Map.h"
#include "../Application.h"

Map::Map(Application* application) {
	_application = application;
	_staticsNeedUpdating = false;
	_dynamicsNeedUpdating = false;
	_terrainsNeedUpdating = false;
}

void Map::updateVBOs() {
	if (_staticsNeedUpdating) {
		_application->_renderer->updateStaticVBOs();
		_staticsNeedUpdating = false;
	}
	if (_dynamicsNeedUpdating) {
		_application->_renderer->updateDynamicVBOs();
		_dynamicsNeedUpdating = false;
	}
	if (_terrainsNeedUpdating) {
		_application->_renderer->updateTerrainVBOs();
		_terrainsNeedUpdating = false;
	}
}

void Map::addStaticDrawable(Drawable* drawable) {
	_staticDrawables.push_back(drawable);
	_staticsNeedUpdating = true;
}

void Map::addDynamicDrawable(Drawable* drawable) {
	_dynamicDrawables.push_back(drawable);
	_dynamicsNeedUpdating = true;
}

void Map::addStreamDrawable(Drawable* drawable) {
	_streamDrawables.push_back(drawable);
}

void Map::addTerrain(Terrain* terrain) {
	std::vector<Drawable*> drawables = terrain->getDrawables();
	for (int i = 0; i < drawables.size(); i++)
		_terrainDrawables.push_back(drawables[i]);
	_terrainsNeedUpdating = true;
}

void Map::removeStaticDrawable(Drawable* drawable) {
	for (int i = 0; i < _staticDrawables.size(); i++)
		if (_staticDrawables[i] == drawable)
			_staticDrawables.erase(_staticDrawables.begin() + i);
	_staticsNeedUpdating = true;
}

void Map::removeDynamicDrawable(Drawable* drawable) {
	_dynamicDrawables.push_back(drawable);
	_dynamicsNeedUpdating = true;
}

void Map::removeStreamDrawable(Drawable* drawable) {
	_streamDrawables.push_back(drawable);
}

void Map::removeTerrain(Terrain* terrain) {
	std::vector<Drawable*> drawables = terrain->getDrawables();
	for (int i = 0; i < drawables.size(); i++)
		for (int j = 0; j < _terrainDrawables.size(); j++)
			if (_terrainDrawables[j] == drawables[i])
				_terrainDrawables.erase(_terrainDrawables.begin() + j);
	_terrainsNeedUpdating = true;
}

