/*
 * Terrain.h
 *
 *  Created on: May 9, 2015
 *      Author: ericwadkins
 */

#ifndef MAP_TERRAIN_H_
#define MAP_TERRAIN_H_

#include "../Drawables/Drawable.h"
#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

class Application;

class Terrain {
public:
	Terrain(Application* application, int length, int width);
	Terrain(Application* application, int length, int width, long seed);
	virtual ~Terrain() {
	}
	virtual void generate() {
	}
	void updateDrawables();
	enum LightingType {
		ROUGH, SMOOTH
	};
	void setLightingType(LightingType lightingType);
	void setDrawFaces(bool drawFaces);
	void setDrawOutline(bool drawOutline);
	std::vector<Drawable*> getDrawables();
protected:
	float randomFloat();
	void smooth(float smoothness, int num);
	void setColor(float r, float g, float b);
	void logMatrixRepresentation();
	Application* _application;
	std::vector<Drawable*> _drawables;
	float** _heightMap;
	int _length, _width;
	long _seed;
	float _heightScale;
	LightingType _lightingType;
	bool _drawFaces, _drawOutline;
	Vector<float> _color;
};

#endif /* MAP_TERRAIN_H_ */
