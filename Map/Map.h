/*
 * Map.h
 *
 *  Created on: May 8, 2015
 *      Author: ericwadkins
 */

#ifndef MAP_MAP_H_
#define MAP_MAP_H_

#include "../Drawables/Drawable.h"
#include "Terrain.h"
#include "HillTerrain.h"
#include "MountainTerrain.h"

class Application;

class Map {
public:
	Map(Application* application);
	virtual ~Map() {
	}
	void updateVBOs();
	void addStaticDrawable(Drawable* drawable);
	void addDynamicDrawable(Drawable* drawable);
	void addStreamDrawable(Drawable* drawable);
	void addTerrain(Terrain* terrain);
	void removeStaticDrawable(Drawable* drawable);
	void removeDynamicDrawable(Drawable* drawable);
	void removeStreamDrawable(Drawable* drawable);
	void removeTerrain(Terrain* terrain);
	std::vector<Drawable*> _staticDrawables;
	std::vector<Drawable*> _dynamicDrawables;
	std::vector<Drawable*> _streamDrawables;
	std::vector<Drawable*> _terrainDrawables;
private:
	Application* _application;
	bool _staticsNeedUpdating;
	bool _dynamicsNeedUpdating;
	bool _terrainsNeedUpdating;
};

#endif /* MAP_MAP_H_ */
