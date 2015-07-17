/*
 * CanyonTerrain.cpp
 *
 *  Created on: May 20, 2015
 *      Author: ericwadkins
 */

#include "CanyonTerrain.h"
#include "../Application.h"

CanyonTerrain::CanyonTerrain(Application* application, int length, int width) :
		Terrain(application, length, width, 1) {
	_internalScaleY = 5;
	_lightingType = SMOOTH;
	setColor(1, 0.4, 0.4);
}

CanyonTerrain::CanyonTerrain(Application* application, int length, int width,
		long seed) :
		Terrain(application, length, width, 1, seed) {
	_internalScaleY = 5;
	_lightingType = SMOOTH;
	setColor(1, 0.4, 0.4);
}

void CanyonTerrain::generate() {
	_application->_logger->log("Generating canyon terrain (").log(_i - 1).log(
			"x").log(_j - 1).log(")..").endLine().increaseIndent();

	_application->_logger->log("Setting initial points..").endLine();
	std::vector<Vector<float> > initPoints;
	bool success = false;
	while (!success) {
		for (int i = 0; i < _i; i++)
			for (int j = 0; j < _j; j++)
				if (randomFloat() < .02) {
					_heightMap[i][j] = 1 - randomFloat() / 10;
					initPoints.push_back(Vector<float>(i, j));
				}
		for (int i = 0; i < _i; i++)
			for (int j = 0; j < _j; j++)
				if (_heightMap[i][j] != -1)
					success = true;
	}

	_application->_logger->log("Building height map..").endLine().increaseIndent();
	std::vector<Vector<float> > unvisited;
	std::vector<float> adjacentHeights;
	int attemptCount = 0;

	while (true) {
		attemptCount++;
		_application->_logger->log("Attempt ").log(attemptCount).log("..").endLine();
		unvisited.clear();
		for (int i = 0; i < _i; i++)
			for (int j = 0; j < _j; j++)
				if (_heightMap[i][j] == -1)
					unvisited.push_back(Vector<float>(i, j));
		if (unvisited.size() == 0)
			break;
		random_shuffle(unvisited.begin(), unvisited.end());

		for (int n = 0; n < unvisited.size(); n++) {
			int i = unvisited[n][0];
			int j = unvisited[n][1];
			adjacentHeights.clear();
			float averageHeight = 0;
			for (int x = std::max(i - 1, 0); x <= std::min(i + 1, _i - 1);
					x++)
				for (int y = std::max(j - 1, 0);
						y <= std::min(j + 1, _j - 1); y++)
					if (_heightMap[x][y] != -1)
						adjacentHeights.push_back(_heightMap[x][y]);
			if (adjacentHeights.size() > 0) {
				for (int k = 0; k < adjacentHeights.size(); k++)
					averageHeight += adjacentHeights[k];
				averageHeight /= adjacentHeights.size();

				float minDist = std::numeric_limits<float>::max();
				for (int k = 0; k < initPoints.size(); k++) {
					int x = initPoints[k][0];
					int y = initPoints[k][1];
					float dist = std::sqrt(
							(i - x) * (i - x) + (j - y) * (j - y));
					if (dist < minDist)
						minDist = dist;
				}
				float temp = std::fmax(
						averageHeight - randomFloat() * minDist / 50, 0);
				if (1 - temp > 0.1)
					_heightMap[i][j] = randomFloat() * 0.1;
				else
					_heightMap[i][j] = 1 - randomFloat() / 20;
			}
		}
	}
	_application->_logger->log("Done building height map!").endLine().decreaseIndent();

	_application->_logger->log("Smoothing terrain..").endLine();
	smooth(0.5, 2);

	_application->_logger->log("Successfully generated terrain!").endLine().decreaseIndent();

	//logMatrixRepresentation();
}

