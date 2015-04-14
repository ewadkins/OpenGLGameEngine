/*
 * Vertex.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef DRAWING_VERTEX_H_
#define DRAWING_VERTEX_H_

#include <vector>

class Vertex {
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float r, float g, float b);
	virtual ~Vertex() {
	}
	void setPosition(float x, float y, float z);
	void setColor(float r, float g, float b);
	void setNormal(float normX, float normY, float normZ);
	void setTexCoords(float texX, float texY);
	std::vector<float> getPosition();
	std::vector<float> getColor();
	std::vector<float> getNormal();
	std::vector<float> getTexCoords();
private:
	float _x, _y, _z, _r, _g, _b, _normX, _normY, _normZ, _texX, _texY;
};

#endif /* DRAWING_VERTEX_H_ */
