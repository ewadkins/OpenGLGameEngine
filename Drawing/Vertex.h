/*
 * Vertex.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>

class Vertex {
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float r, float g, float b);
	Vertex(float x, float y, float z, float r, float g, float b, float normX,
			float normY, float normZ);
	Vertex(float x, float y, float z, float r, float g, float b, float normX,
			float normY, float normZ, float texX, float texY);
	Vertex(std::vector<float> pos);
	Vertex(std::vector<float> pos, std::vector<float> color);
	Vertex(std::vector<float> pos, std::vector<float> color, std::vector<float> norm);
	Vertex(std::vector<float> pos, std::vector<float> color, std::vector<float> norm, std::vector<float> tex);
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
	Vertex* clone();
private:
	float _x, _y, _z, _r, _g, _b, _normX, _normY, _normZ, _texX, _texY;
};

#endif /* VERTEX_H_ */
