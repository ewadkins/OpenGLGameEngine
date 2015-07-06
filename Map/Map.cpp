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
	_lightCountChanged = false;
}

void Map::update() {

	if (_staticsNeedUpdating) {
		_application->_renderer->updateStaticVBOs();
		_staticsNeedUpdating = false;
	}

	if (_dynamicsNeedUpdating) {
		_application->_renderer->updateDynamicVBOs();
		_dynamicsNeedUpdating = false;
	}

	bool terrainUpdated = false;
	for (int i = 0; i < _terrains.size(); i++)
		if (_terrains[i]->_needsUpdating) {
			_terrains[i]->updateDrawables();
			_terrains[i]->_needsUpdating = false;
			terrainUpdated = true;
		}
	if (terrainUpdated) {
		updateTerrainDrawables();
	}
	if (_terrainsNeedUpdating) {
		_application->_renderer->updateTerrainVBOs();
		_terrainsNeedUpdating = false;
	}

	if (_application->_renderer != nullptr)
		if (_lightCountChanged) {
			_application->_renderer->createShaders();
			_lightCountChanged = false;
		}
	bool lightsNeedUpdating = false;
	for (int i = 0; i < _lights.size(); i++)
		if (_lights[i]->_needsUpdating) {
			lightsNeedUpdating = true;
			_lights[i]->_needsUpdating = false;
		}
	if (lightsNeedUpdating)
		_application->_renderer->updateLights();
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
	_terrains.push_back(terrain);
	updateTerrainDrawables();
}

void Map::removeStaticDrawable(Drawable* drawable) {
	for (int i = 0; i < _staticDrawables.size(); i++)
		if (_staticDrawables[i] == drawable)
			_staticDrawables.erase(_staticDrawables.begin() + i);
	_staticsNeedUpdating = true;
}

void Map::removeDynamicDrawable(Drawable* drawable) {
	for (int i = 0; i < _dynamicDrawables.size(); i++)
		if (_dynamicDrawables[i] == drawable)
			_dynamicDrawables.erase(_dynamicDrawables.begin() + i);
	_dynamicsNeedUpdating = true;
}

void Map::removeStreamDrawable(Drawable* drawable) {
	for (int i = 0; i < _streamDrawables.size(); i++)
		if (_streamDrawables[i] == drawable)
			_streamDrawables.erase(_streamDrawables.begin() + i);
}

void Map::removeTerrain(Terrain* terrain) {
	for (int i = 0; i < _terrains.size(); i++)
		if (_terrains[i] == terrain)
			_terrains.erase(_terrains.begin() + i);
	updateTerrainDrawables();
}

void Map::addLightSource(LightSource* light) {
	_lights.push_back(light);
	_lightCountChanged = true;
}

void Map::removeLightSource(LightSource* light) {
	for (int i = 0; i < _lights.size(); i++)
		if (_lights[i] == light)
			_lights.erase(_lights.begin() + i);
	_lightCountChanged = true;
}

void Map::updateTerrainDrawables() {
	_terrainDrawables.clear();
	for (int i = 0; i < _terrains.size(); i++) {
		std::vector<Drawable*> drawables = _terrains[i]->getDrawables();
		_terrainDrawables.insert(_terrainDrawables.end(), drawables.begin(), drawables.end());
	}
	_terrainsNeedUpdating = true;
}

