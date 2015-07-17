/*
 * FractalMountainTerrain.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: ericwadkins
 */

#include "FractalMountainTerrain.h"
#include "../Application.h"

int FractalMountainTerrain::fractalIterations = 0;
// typically between 0 and 1, larger random factor = smoother
float FractalMountainTerrain::randomFactor = 1;

FractalMountainTerrain::FractalMountainTerrain(Application* application, int length, int width) :
		Terrain(application, length, width, std::pow(2, fractalIterations)) {
	_internalScaleY = length / 2;
	_lightingType = SMOOTH;
	setColor(0, 1, 0);
}

FractalMountainTerrain::FractalMountainTerrain(Application* application, int length, int width,
		long seed) :
		Terrain(application, length, width, std::pow(2, fractalIterations), seed) {
	_internalScaleY = length / 2;
	_lightingType = SMOOTH;
	setColor(0, 1, 0);
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
		bool show = (false);
		if (show)
			_application->_logger->log("k = ").log(k).endLine();
		if (show)
			_application->_logger->log("n = ").log(n).log(":").endLine().increaseIndent();
		if (show)
			_application->_logger->log("Diamond step:").endLine().increaseIndent();
		for (int i = 0; i < _i - 1; i += n) {
			if (show)
				_application->_logger->log("i = ").log(i).log(":").endLine().increaseIndent();
			for (int j = 0; j < _j - 1; j += n) {
				if (show)
					_application->_logger->log("j = ").log(j).endLine().increaseIndent();
				float h1 = _heightMap[i][j];
				float h2 = _heightMap[i][j + n];
				float h3 = _heightMap[i + n][j + n];
				float h4 = _heightMap[i + n][j];
				if (show) {
					_application->_logger->log("h1 = ").log(h1).endLine();
					_application->_logger->log("h2 = ").log(h2).endLine();
					_application->_logger->log("h3 = ").log(h3).endLine();
					_application->_logger->log("h4 = ").log(h4).endLine();
				}
				float random = (randomFloat() * 2 - 1) * k;
				float h = std::fmax(0, std::fmin(1, (h1 + h2 + h3 + h4) / 4 + random));
				_heightMap[i + n / 2][j + n / 2] = h;
				if (show) {
					_application->_logger->log("random = ").log(random).endLine();
					_application->_logger->log("height = ").log(h).endLine();
					logMatrixRepresentation();
					_application->_logger->decreaseIndent();
				}
			}
			if (show)
				_application->_logger->decreaseIndent();
		}
		if (show)
			_application->_logger->decreaseIndent();
		if (show)
			_application->_logger->log("Square step:").endLine().increaseIndent();
		int di[] = { 0, -n / 2, 0, n / 2 };
		int dj[] = { n / 2, 0, -n / 2, 0 };
		for (int i = 0; i < _i; i += n / 2) {
			if (show)
				_application->_logger->log("i = ").log(i).log(":").endLine().increaseIndent();
			for (int j = n / 2 * ((i * 2 / n + 1) % 2); j < _j; j += n) {
				if (show)
					_application->_logger->log("j = ").log(j).endLine().increaseIndent();
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
				if (show) {
					_application->_logger->log("random = ").log(random).endLine();
					_application->_logger->log("height = ").log(h).endLine();
					logMatrixRepresentation();
					_application->_logger->decreaseIndent();
				}
			}
			if (show)
				_application->_logger->decreaseIndent();
		}
		n /= 2;
		k /= 2;
		if (show)
			_application->_logger->decreaseIndent();
		if (show)
			_application->_logger->decreaseIndent();
	}

	_application->_logger->log("Done building height map!").endLine().decreaseIndent();

	_application->_logger->log("Smoothing terrain..").endLine();
	smooth(1.0, 2);

	_application->_logger->log("Successfully generated terrain!").endLine().decreaseIndent();

	//logMatrixRepresentation();
}

