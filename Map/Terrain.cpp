/*
 * Terrain.cpp
 *
 *  Created on: May 9, 2015
 *      Author: ericwadkins
 */

#include "Terrain.h"
#include "../Application.h"

Terrain::Terrain(Application* application, int length, int width) {
	_application = application;
	_length = length;
	_width = width;
	_seed = clock();
	srand(_seed);
	_heightScale = 1;
	_lightingType = ROUGH;

	_heightMap = new float*[length];
	for (int i = 0; i < length; i++) {
		_heightMap[i] = new float[width];
		for (int j = 0; j < width; j++)
			_heightMap[i][j] = -1;
	}
}

Terrain::Terrain(Application* application, int length, int width, long seed) {
	_application = application;
	_length = length;
	_width = width;
	_seed = seed;
	srand(_seed);
	_heightScale = 1;
	_lightingType = ROUGH;

	_heightMap = new float*[length];
	for (int i = 0; i < length; i++) {
		_heightMap[i] = new float[width];
		for (int j = 0; j < width; j++)
			_heightMap[i][j] = -1;
	}
}

void Terrain::updateDrawables() {

	_application->_logger->log("Updating terrain drawables..").endLine();

	_drawables.clear();

	std::vector<std::vector<GLVertex> > vertices;
	std::vector<GLVertex> rowVertices;
	for (int i = 0; i < _length; i++) {
		rowVertices.clear();
		for (int j = 0; j < _width; j++)
			rowVertices.push_back(
					GLVertex(i, _heightMap[i][j] * _heightScale, j,
							1 - _heightMap[i][j], 1, 1 - _heightMap[i][j]));
		vertices.push_back(rowVertices);
	}

	if (_lightingType == SMOOTH) {

		std::vector<std::vector<std::vector<Vector<float> > > > normals;
		std::vector<std::vector<Vector<float> > > rowNormals;
		std::vector<Vector<float> > faceNormals;
		Vector<float> normal, v1, v2;
		std::vector<float> pos1, pos2, pos3, pos4;
		for (int i = 0; i < _length - 1; i++) {
			rowNormals.clear();
			for (int j = 0; j < _width - 1; j++) {
				faceNormals.clear();
				pos1 = vertices[i][j].getPosition();
				pos2 = vertices[i][j + 1].getPosition();
				pos3 = vertices[i + 1][j + 1].getPosition();
				pos4 = vertices[i + 1][j].getPosition();
				v2 = Vector<float>(pos4[0] - pos1[0], pos4[1] - pos1[1],
						pos4[2] - pos1[2]);
				v1 = Vector<float>(pos2[0] - pos1[0], pos2[1] - pos1[1],
						pos2[2] - pos1[2]);
				normal = v1.cross(v2);
				normal = normal.normalize();
				faceNormals.push_back(normal);
				v2 = Vector<float>(pos4[0] - pos2[0], pos4[1] - pos2[1],
						pos4[2] - pos2[2]);
				v1 = Vector<float>(pos3[0] - pos2[0], pos3[1] - pos2[1],
						pos3[2] - pos2[2]);
				normal = v1.cross(v2);
				normal = normal.normalize();
				faceNormals.push_back(normal);
				rowNormals.push_back(faceNormals);

			}
			normals.push_back(rowNormals);
		}

		int deltaX[] = { 0, 0, 0, -1, -1, -1 };
		int deltaY[] = { 0, -1, -1, 0, 0, -1 };
		int face[] = { 0, 0, 1, 0, 1, 1 };
		int i, j, k;
		float normX, normY, normZ;
		for (int x = 0; x < vertices.size(); x++)
			for (int y = 0; y < vertices[0].size(); y++) {
				normX = 0;
				normY = 0;
				normZ = 0;
				for (int n = 0; n < 6; n++) {
					i = x + deltaX[n];
					j = y + deltaY[n];
					k = face[n];
					if (i >= 0 && i < normals.size() && j >= 0
							&& j < normals[0].size()) {
						normX += normals[i][j][k][0];
						normY += normals[i][j][k][1];
						normZ += normals[i][j][k][2];
					}
				}
				float mag = sqrt(normX * normX + normY * normY + normZ * normZ);
				normX /= mag;
				normY /= mag;
				normZ /= mag;
				vertices[x][y].setNormal(normX, normY, normZ);
			}
	}

	for (int i = 0; i < _length - 1; i++)
		for (int j = 0; j < _width - 1; j++) {
			GLVertex v1 = vertices[i][j];
			GLVertex v2 = vertices[i][j + 1];
			GLVertex v3 = vertices[i + 1][j + 1];
			GLVertex v4 = vertices[i + 1][j];
			Drawable* t1 = new Triangle(v1, v2, v4);
			Drawable* t2 = new Triangle(v2, v3, v4);
			//t1->setDrawOutline(false);
			//t2->setDrawOutline(false);
			_drawables.push_back(t1);
			_drawables.push_back(t2);
		}
}

void Terrain::setLightingType(LightingType lightingType) {
	if (_lightingType != lightingType) {
		_lightingType = lightingType;
		updateDrawables();
	}
}

std::vector<Drawable*> Terrain::getDrawables() {
	return _drawables;
}

float Terrain::randomFloat() {
	return (float) rand() / RAND_MAX;
}

void Terrain::smooth(float smoothness, int num) {
	std::vector<float> adjacentHeights;
	std::vector<Vector<float> > points;
	for (int i = 0; i < _length; i++)
		for (int j = 0; j < _width; j++)
			points.push_back(Vector<float>(i, j));
	for (int n = 0; n < num; n++) {
		random_shuffle(points.begin(), points.end());
		for (int n = 0; n < points.size(); n++) {
			int i = points[n][0];
			int j = points[n][1];
			adjacentHeights.clear();
			float averageHeight = 0;
			for (int x = std::max(i - 1, 0); x <= std::min(i + 1, _length - 1);
					x++)
				for (int y = std::max(j - 1, 0);
						y <= std::min(j + 1, _width - 1); y++)
					adjacentHeights.push_back(_heightMap[x][y]);
			if (adjacentHeights.size() > 0) {
				for (int k = 0; k < adjacentHeights.size(); k++)
					averageHeight += adjacentHeights[k];
				averageHeight /= adjacentHeights.size();
				if (std::abs(averageHeight - _heightMap[i][j])
						> (1 - smoothness))
					_heightMap[i][j] = averageHeight;
			}
		}
	}
}

void Terrain::logMatrixRepresentation() {
	Matrix<float> m = Matrix<float>(_length, _width);
	m.setMatrix(_heightMap);
	_application->_logger->log(m);
}

