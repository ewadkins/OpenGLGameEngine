/*
 * FractalMountainTerrain.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: ericwadkins
 */

#include "FractalMountainTerrain.h"
#include "../Application.h"

int FractalMountainTerrain::fractalIterations = 2;
// typically between 0 and 1, larger random factor = smoother
float FractalMountainTerrain::randomFactor = 1;

FractalMountainTerrain::FractalMountainTerrain(Application* application, int length, int width) :
		Terrain(application, length, width, std::pow(2, fractalIterations)) {
	_internalScaleY = length / 2;
	_lightingType = SMOOTH;
	setColor(0.4, 0.4, 0.4);
}

FractalMountainTerrain::FractalMountainTerrain(Application* application, int length, int width,
		long seed) :
		Terrain(application, length, width, std::pow(2, fractalIterations), seed) {
	_internalScaleY = length / 2;
	_lightingType = SMOOTH;
	setColor(1, 1, 1);
}

void FractalMountainTerrain::generate() {
	if (!checkFractal()) {
		_application->_logger->log("Conditions for fractal terrain not met. The terrain must be square with a size of a power of 2").endLine();
		return;
	}
	_application->_logger->log("Generating fractal mountain terrain (").log(_length).log(
			"x").log(_width).log(")..").endLine().increaseIndent();

	_application->_logger->log("Building height map..").endLine().increaseIndent();

	_heightMap[0][0] = 0.5 + 0.2 * (randomFloat() - 0.5);
	_heightMap[0][_j - 1] = 0.5 + 0.2 * (randomFloat() - 0.5);
	_heightMap[_i - 1][_j - 1] = 0.5 + 0.2 * (randomFloat() - 0.5);
	_heightMap[_i - 1][0] = 0.5 + 0.2 * (randomFloat() - 0.5);

	int n = _i - 1;
	float k = std::pow(2, -randomFactor);
	while (n > 1) {
		for (int i = 0; i < _i - 1; i += n) {
			for (int j = 0; j < _j - 1; j += n) {
				float h1 = _heightMap[i][j];
				float h2 = _heightMap[i][j + n];
				float h3 = _heightMap[i + n][j + n];
				float h4 = _heightMap[i + n][j];
				float random = (randomFloat() * 2 - 1) * k;
				float h = std::fmax(0, std::fmin(1, (h1 + h2 + h3 + h4) / 4 + random));
				_heightMap[i + n / 2][j + n / 2] = h;
			}
		}
		int di[] = { 0, -n / 2, 0, n / 2 };
		int dj[] = { n / 2, 0, -n / 2, 0 };
		for (int i = 0; i < _i; i += n / 2) {
			for (int j = n / 2 * ((i * 2 / n + 1) % 2); j < _j; j += n) {
				int count = 0;
				float h = 0;
				for (int d = 0; d < 4; d++) {
					if (i + di[d] > 0 && i + di[d] < _i && j + dj[d] > 0 && j + dj[d] < _j) {
						h += _heightMap[i + di[d]][j + dj[d]];
						count++;
					}
				}
				float random = (randomFloat() * 2 - 1) * k;
				h = std::fmax(0, std::fmin(1, h / count + random));
				_heightMap[i][j] = h;
			}
		}
		n /= 2;
		k /= 2;
	}

	_application->_logger->log("Done building height map!").endLine().decreaseIndent();

	_application->_logger->log("Smoothing terrain..").endLine();
	//smooth(1.0, 2);

	_application->_logger->log("Successfully generated terrain!").endLine().decreaseIndent();

	//logMatrixRepresentation();
}

