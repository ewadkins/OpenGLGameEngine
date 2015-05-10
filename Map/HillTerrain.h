/*
 * HillTerrain.h
 *
 *  Created on: May 9, 2015
 *      Author: ericwadkins
 */

#ifndef MAP_HILLTERRAIN_H_
#define MAP_HILLTERRAIN_H_

#include "Terrain.h"

class Application;

class HillTerrain: public Terrain {
public:
	HillTerrain(Application* application, int length, int width);
	HillTerrain(Application* application, int length, int width, long seed);
	virtual ~HillTerrain(){
	}
	virtual void generate();
};

#endif /* MAP_HILLTERRAIN_H_ */
