/*
 * Vertex.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef COMPONENTS_VERTEX_H_
#define COMPONENTS_VERTEX_H_

#include "../Math/Matrix.h"
#include <vector>
#include <string>

class GLVertex {
public:
	GLVertex();
	GLVertex(float x, float y, float z);
	GLVertex(float x, float y, float z, float r, float g, float b);
	GLVertex(float x, float y, float z, float r, float g, float b, float normX,
			float normY, float normZ);
	GLVertex(float x, float y, float z, float r, float g, float b, float normX,
			float normY, float normZ, float texX, float texY);
	GLVertex(std::vector<float> pos);
	GLVertex(std::vector<float> pos, std::vector<float> color);
	GLVertex(std::vector<float> pos, std::vector<float> color, std::vector<float> norm);
	GLVertex(std::vector<float> pos, std::vector<float> color, std::vector<float> norm, std::vector<float> tex);
	virtual ~GLVertex() {
	}
	void transform(Matrix<float> modelTransformationMatrix, Matrix<float> rotationMatrix);
	void setPosition(float x, float y, float z);
	void setColor(float r, float g, float b);
	void setNormal(float normX, float normY, float normZ);
	void setTexCoords(float texX, float texY);
	std::vector<float> getPosition();
	std::vector<float> getColor();
	std::vector<float> getNormal();
	std::vector<float> getTexCoords();
	GLVertex* clone();
	std::string toString();
private:
	float _x, _y, _z, _r, _g, _b, _normX, _normY, _normZ, _texX, _texY;
};

#endif /* COMPONENTS_VERTEX_H_ */
