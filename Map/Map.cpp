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

void Map::initialize() {

	Drawable* t1 = new Triangle();
	t1->setXYZ(-5, 0, 0);
	addStatic(t1);

	Drawable* t2 = new Triangle();
	t2->setXYZ(-4, 0, 0);
	t2->rotateXYZ(45, 45, 45);
	addStatic(t2);

	Drawable* t3 = new Triangle();
	t3->setXYZ(-3, 0, 0);
	t3->rotateXYZ(45, 45, 45);
	t3->scaleXYZ(1, 2, 1);
	addStatic(t3);

	Drawable* t4 = new Triangle();
	t4->setXYZ(-2, 3, 0);
	t4->setColor(1, 0.5, 0);
	addStream(t4);

	Drawable* lightCube = new Cube();
	lightCube->setXYZ(0, 15, 0);
	lightCube->scaleXYZ(0.5, 0.5, 0.5);
	lightCube->setColor(1, 1, 0);
	addStatic(lightCube);

	Drawable* c1 = new Cube();
	c1->setRotationXYZ(45, 45, 45);
	c1->scaleXYZ(2, 2, 2);
	addStatic(c1);

	Drawable* c2 = new Cube();
	c2->setXYZ(3, 0, 0);
	c2->setRotationXYZ(30, 30, 30);
	c2->scaleXYZ(1, 1, 2);
	c2->setColor(0, 0, 1);
	addStatic(c2);

	Drawable* c3 = new Cube();
	c3->setXYZ(5, 0, 0);
	c3->setColor(1, 0, 1);
	addStatic(c3);

	for (int i = 0; i < 1; i++) {
		Drawable* c4 = new Cube();
		c4->setXYZ(i, 5, 0);
		c4->setColor(1, 0, 0);
		addStream(c4);
	}

	Drawable* c5 = new Cube();
	c5->setXYZ(2, 3, 0);
	c5->setRotationXYZ(45, 0, 45);
	c5->setColor(0, 1, 0);
	addStream(c5);

	Terrain* terrain = new HillTerrain(_application, 50, 50, 12345);
	terrain->generate();
	terrain->updateDrawables();
	addTerrain(terrain);

}

void Map::update() {
	for (int i = 0; i < _streamDrawables.size(); i++) {
		_streamDrawables[i]->rotateXYZ(0, 1, 0);
		//_streamDrawables[i]->translateXYZ(0, 0.01, 0);
	}

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

void Map::addStatic(Drawable* drawable) {
	_staticDrawables.push_back(drawable);
	_staticsNeedUpdating = true;
}

void Map::addDynamic(Drawable* drawable) {
	_dynamicDrawables.push_back(drawable);
	_dynamicsNeedUpdating = true;
}

void Map::addStream(Drawable* drawable) {
	_streamDrawables.push_back(drawable);
}

void Map::addTerrain(Terrain* terrain) {
	std::vector<Drawable*> drawables = terrain->getDrawables();
	for (int i = 0; i < drawables.size(); i++)
		_terrainDrawables.push_back(drawables[i]);
	_terrainsNeedUpdating = true;
}

void Map::removeStatic(Drawable* drawable) {
	for (int i = 0; i < _staticDrawables.size(); i++)
		if (_staticDrawables[i] == drawable)
			_staticDrawables.erase(_staticDrawables.begin() + i);
	_staticsNeedUpdating = true;
}

void Map::removeDynamic(Drawable* drawable) {
	_dynamicDrawables.push_back(drawable);
	_dynamicsNeedUpdating = true;
}

void Map::removeStream(Drawable* drawable) {
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

std::vector<Drawable*> Map::getStaticDrawables() {
	/*std::vector<Drawable*> result;
	result.insert(result.end(), _staticDrawables.begin(), _staticDrawables.end());
	result.insert(result.end(), _terrainDrawables.begin(), _terrainDrawables.end());
	return result;*/
	return _staticDrawables;
}

std::vector<Drawable*> Map::getDynamicDrawables() {
	return _dynamicDrawables;
}

std::vector<Drawable*> Map::getStreamDrawables() {
	return _streamDrawables;
}

std::vector<Drawable*> Map::getTerrainDrawables() {
	return _terrainDrawables;
}

