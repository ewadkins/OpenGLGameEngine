/*
 * MountainTerrain.h
 *
 *  Created on: May 17, 2015
 *      Author: ericwadkins
 */

#ifndef MAP_MOUNTAINTERRAIN_H_
#define MAP_MOUNTAINTERRAIN_H_

#include "Terrain.h"

class Application;

class MountainTerrain: public Terrain {
public:
	MountainTerrain(Application* application, int length, int width);
	MountainTerrain(Application* application, int length, int width, long seed);
	virtual ~MountainTerrain(){
	}
	virtual void generate();
};

#endif /* MAP_MOUNTAINTERRAIN_H_ */
