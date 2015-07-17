/*
 * FractalMountainTerrain.h
 *
 *  Created on: Jul 17, 2015
 *      Author: ericwadkins
 */

#ifndef MAP_FRACTALMOUNTAINTERRAIN_H_
#define MAP_FRACTALMOUNTAINTERRAIN_H_

#include "Terrain.h"

class Application;

class FractalMountainTerrain: public Terrain {
public:
	FractalMountainTerrain(Application* application, int length, int width);
	FractalMountainTerrain(Application* application, int length, int width, long seed);
	virtual ~FractalMountainTerrain(){
	}
	virtual void generate();
private:
	static int fractalIterations;
	static float randomFactor;
};

#endif /* MAP_FRACTALMOUNTAINTERRAIN_H_ */
