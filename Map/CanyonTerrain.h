/*
 * CanyonTerrain.h
 *
 *  Created on: May 20, 2015
 *      Author: ericwadkins
 */

#ifndef MAP_CANYONTERRAIN_H_
#define MAP_CANYONTERRAIN_H_

#include "Terrain.h"

class Application;

class CanyonTerrain: public Terrain {
public:
	CanyonTerrain(Application* application, int length, int width);
	CanyonTerrain(Application* application, int length, int width, long seed);
	virtual ~CanyonTerrain(){
	}
	virtual void generate();
};

#endif /* MAP_CANYONTERRAIN_H_ */
