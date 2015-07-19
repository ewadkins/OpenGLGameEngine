/*
 * Terrain.h
 *
 *  Created on: May 9, 2015
 *      Author: ericwadkins
 */

#ifndef MAP_TERRAIN_H_
#define MAP_TERRAIN_H_

#include "../Transformable.h"
#include "../Drawables/Drawable.h"
#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

class Application;

class Terrain: public Transformable {
public:
	Terrain(Application* application, int length, int width, int resolution);
	Terrain(Application* application, int length, int width, int resolution, long seed);
	virtual ~Terrain() {
	}
	virtual void generate() {
	}
	void updateDrawables();
	Vector<float> project(Vector<float> pos, bool bounded);
	enum LightingType {
		ROUGH, SMOOTH
	};
	void setLightingType(LightingType lightingType);
	void setDrawFaces(bool drawFaces);
	void setDrawOutline(bool drawOutline);
	std::vector<Drawable*> getDrawables();
	friend class Map;
protected:
	float randomFloat();
	void smooth(float smoothness, int num);
	void setColor(float r, float g, float b);
	void logMatrixRepresentation();
	bool checkFractal();
	Application* _application;
	std::vector<Drawable*> _drawables;
	float** _heightMap;
	int _length, _width;
	int _i, _j;
	long _seed;
	float _internalScaleX, _internalScaleY, _internalScaleZ;
	int _resolution;
	LightingType _lightingType;
	bool _drawFaces, _drawOutline;
	Vector<float> _color;
};

#endif /* MAP_TERRAIN_H_ */
