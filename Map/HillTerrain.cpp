/*
 * HillTerrain.cpp
 *
 *  Created on: May 9, 2015
 *      Author: ericwadkins
 */

#include "HillTerrain.h"
#include "../Application.h"

HillTerrain::HillTerrain(Application* application, int length, int width) {
	_application = application;
	_length = length;
	_width = width;
	_seed = clock();
	srand(_seed);
	_maxHeight = 5;
}

HillTerrain::HillTerrain(Application* application, int length, int width,
		long seed) {
	_application = application;
	_length = length;
	_width = width;
	_seed = seed;
	srand(_seed);
	_maxHeight = 5;
}

void HillTerrain::generate() {
	_application->_logger->log("Generating hill terrain (").log(_length).log(
			"x").log(_width).log(")..").endLine().increaseIndent();

	_application->_logger->log("Creating empty height map..").endLine();
	_heightMap = new float*[_length];
	for (int i = 0; i < _length; i++) {
		_heightMap[i] = new float[_width];
		for (int j = 0; j < _width; j++)
			_heightMap[i][j] = -1;
	}

	_application->_logger->log("Generating initial points..").endLine();
	std::vector<Vector<float> > initPoints;
	bool success = false;
	while (!success) {
		for (int i = 0; i < _length; i++)
			for (int j = 0; j < _width; j++)
				if (randomFloat() < .02) {
					_heightMap[i][j] = randomFloat();
					initPoints.push_back(Vector<float>(i, j));
				}
		for (int i = 0; i < _length; i++)
			for (int j = 0; j < _width; j++)
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
		for (int i = 0; i < _length; i++)
			for (int j = 0; j < _width; j++)
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
			for (int x = std::max(i - 1, 0); x <= std::min(i + 1, _length - 1);
					x++)
				for (int y = std::max(j - 1, 0);
						y <= std::min(j + 1, _width - 1); y++)
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
				_heightMap[i][j] = std::fmax(
						averageHeight - randomFloat() * minDist / 20, 0);
			}
		}
	}
	_application->_logger->log("Done building height map!").endLine().decreaseIndent();

	_application->_logger->log("Smoothing terrain..").endLine();
	smooth(1.0);

	_application->_logger->log("Successfully generated terrain!").endLine().decreaseIndent();

	logMatrixRepresentation();
}

