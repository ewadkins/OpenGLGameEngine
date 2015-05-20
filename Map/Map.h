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
	void initialize();
	void update();
	void updateVBOs();
	void addStatic(Drawable* drawable);
	void addDynamic(Drawable* drawable);
	void addStream(Drawable* drawable);
	void addTerrain(Terrain* terrain);
	void removeStatic(Drawable* drawable);
	void removeDynamic(Drawable* drawable);
	void removeStream(Drawable* drawable);
	void removeTerrain(Terrain* terrain);
	std::vector<Drawable*> getStaticDrawables();
	std::vector<Drawable*> getDynamicDrawables();
	std::vector<Drawable*> getStreamDrawables();
	std::vector<Drawable*> getTerrainDrawables();
private:
	Application* _application;
	std::vector<Drawable*> _staticDrawables;
	std::vector<Drawable*> _dynamicDrawables;
	std::vector<Drawable*> _streamDrawables;
	std::vector<Drawable*> _terrainDrawables;
	bool _staticsNeedUpdating;
	bool _dynamicsNeedUpdating;
	bool _terrainsNeedUpdating;
};

#endif /* MAP_MAP_H_ */
