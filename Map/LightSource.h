/*
 * LightSource.h
 *
 *  Created on: May 23, 2015
 *      Author: ericwadkins
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "../Math/Vector.h"

class LightSource {
public:
	LightSource(int type);
	LightSource(float x, float y, float z);
	virtual ~LightSource() {
	}
	void setType(int type);
	void setPosition(float x, float y, float z);
	void setPosition(Vector<float> pos);
	void setDirection(float u, float v, float w);
	void setDirection(Vector<float> dir);
	void setAmbient(float r, float g, float b);
	void setAmbient(Vector<float> color);
	void setDiffuse(float r, float g, float b);
	void setDiffuse(Vector<float> color);
	void setSpecular(float r, float g, float b);
	void setSpecular(Vector<float> color);
	void setRange(float range);
	void setBeamAngle(float beamAngle);
	void setEnabled(bool enabled);
	int getType();
	Vector<float> getPosition();
	Vector<float> getDirection();
	Vector<float> getAmbient();
	Vector<float> getDiffuse();
	Vector<float> getSpecular();
	float getRange();
	float getBeamAngle();
	bool isEnabled();
	bool _needsUpdating;
    static const int POINT, DIRECTIONAL, SPOTLIGHT;
private:
    int _type;
    Vector<float> _position;
    Vector<float> _direction;
    Vector<float> _ambient;
    Vector<float> _diffuse;
    Vector<float> _specular;
    float _range;
    float _beamAngle;
    bool _enabled;

};

#endif /* LIGHTSOURCE_H_ */
