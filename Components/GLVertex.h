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
			float normY, float normZ, float texX, float texY, float texIndex);
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
	void setTexCoords(float texX, float texY, float texIndex);
	void setPosition(std::vector<float> pos);
	void setColor(std::vector<float> color);
	void setNormal(std::vector<float> norm);
	void setTexCoords(std::vector<float> tex);
	std::vector<float> getPosition();
	std::vector<float> getColor();
	std::vector<float> getNormal();
	std::vector<float> getTexCoords();
	std::vector<float> getData();
	bool hasColor();
	bool hasNormal();
	bool hasTexCoords();
	GLVertex* clone();
	std::string toString();
	float _x, _y, _z, _r, _g, _b, _normX, _normY, _normZ, _texX, _texY, _texIndex;
	bool _hasColor, _hasNormal, _hasTexCoords;
};

#endif /* COMPONENTS_VERTEX_H_ */
