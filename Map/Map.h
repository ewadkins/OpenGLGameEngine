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

class Application;

class Map {
public:
	Map(Application* application);
	virtual ~Map() {
	}
	void initialize();
	void update();
	void addStatic(Drawable* drawable);
	void addDynamic(Drawable* drawable);
	void addStream(Drawable* drawable);
	void removeStatic(Drawable* drawable);
	void removeDynamic(Drawable* drawable);
	void removeStream(Drawable* drawable);
	void addTerrain(Terrain* terrain);
	void removeTerrain(Terrain* terrain);
	std::vector<Drawable*> getStaticDrawables();
	std::vector<Drawable*> getDynamicDrawables();
	std::vector<Drawable*> getStreamDrawables();
private:
	Application* _application;
	std::vector<Drawable*> _staticDrawables;
	std::vector<Drawable*> _dynamicDrawables;
	std::vector<Drawable*> _streamDrawables;
	bool _staticsNeedUpdating;
	bool _dynamicsNeedUpdating;
};

#endif /* MAP_MAP_H_ */
