/*
 * Terrain.cpp
 *
 *  Created on: May 9, 2015
 *      Author: ericwadkins
 */

#include "Terrain.h"
#include "../Application.h"

Terrain::Terrain(Application* application, int length, int width,
		int resolution) {
	_application = application;
	_length = length;
	_width = width;
	_i = length * resolution + 1;
	_j = width * resolution + 1;
	_resolution = resolution;
	_seed = clock();
	srand(_seed);
	_internalScaleX = 1;
	_internalScaleY = 1;
	_internalScaleZ = 1;
	_lightingType = ROUGH;
	_drawFaces = true;
	_drawOutline = true;
	_color = Vector<float>(0, 1, 0);

	_heightMap = new float*[_i];
	for (int i = 0; i < _i; i++) {
		_heightMap[i] = new float[_j];
		for (int j = 0; j < _j; j++)
			_heightMap[i][j] = -1;
	}
}

Terrain::Terrain(Application* application, int length, int width,
		int resolution, long seed) {
	_application = application;
	_length = length;
	_width = width;
	_i = length * resolution + 1;
	_j = width * resolution + 1;
	_resolution = resolution;
	_seed = seed;
	srand(_seed);
	_internalScaleX = 1;
	_internalScaleY = 1;
	_internalScaleZ = 1;
	_lightingType = ROUGH;
	_drawFaces = true;
	_drawOutline = true;
	_color = Vector<float>(0, 1, 0);

	_heightMap = new float*[_i];
	for (int i = 0; i < _i; i++) {
		_heightMap[i] = new float[_j];
		for (int j = 0; j < _j; j++)
			_heightMap[i][j] = -1;
	}
}

std::vector<float> mergeColors(float r1, float g1, float b1, float r2, float g2,
		float b2, float k) {
	std::vector<float> result;
	if (k >= 1) {
		result.push_back(r1);
		result.push_back(g1);
		result.push_back(b1);
	} else if (k <= 0) {
		result.push_back(r2);
		result.push_back(g2);
		result.push_back(b2);
	} else {
		result.push_back(r1 * k + r2 * (1 - k));
		result.push_back(g1 * k + g2 * (1 - k));
		result.push_back(b1 * k + b2 * (1 - k));
	}
	return result;
}

void Terrain::updateDrawables() {

	_application->_logger->log("Updating terrain drawables..").endLine();

	_drawables.clear();

	Matrix<float> rotationMatrix = GLMatrix::rotationMatrixXYZ(getRotationX(),
			getRotationY(), getRotationZ());

	Matrix<float> modelTransformationMatrix =
			GLMatrix::modelTransformationMatrix(getX(), getY(), getZ(),
					getRotationX(), getRotationY(), getRotationZ(), getScaleX(),
					getScaleY(), getScaleZ());

	std::vector<std::vector<GLVertex> > vertices;
	std::vector<GLVertex> rowVertices;
	int count = 0;
	int progress = 0;
	for (int i = 0; i < _i; i++) {
		rowVertices.clear();
		for (int j = 0; j < _j; j++) {
			count++;
			int temp = count * 100 / ((_i - 1) * (_j - 1));
			if (progress != temp)
				std::cout << "Creating vertices " << temp << "% (" << count
						<< " / " << ((_i - 1) * (_j - 1)) << ")" << std::endl;
			progress = temp;
			std::vector<float> color = mergeColors(0.4, 0.4, 0.4, _color[0],
					_color[1], _color[2], 1 - _heightMap[i][j]);
			GLVertex v = GLVertex(
					i * _internalScaleX / _resolution - (float) (_length) / 2,
					_heightMap[i][j] * _internalScaleY,
					j * _internalScaleZ / _resolution - (float) (_width) / 2,
					color[0], color[1], color[2]);
			v.transform(modelTransformationMatrix, rotationMatrix);
			rowVertices.push_back(v);
		}
		vertices.push_back(rowVertices);
	}

	count = 0;
	progress = 0;
	if (_lightingType == SMOOTH) {
		std::vector<std::vector<std::vector<Vector<float> > > > normals;
		std::vector<std::vector<Vector<float> > > rowNormals;
		std::vector<Vector<float> > faceNormals;
		Vector<float> normal, v1, v2;
		std::vector<float> pos1, pos2, pos3, pos4;
		for (int i = 0; i < _i - 1; i++) {
			rowNormals.clear();
			for (int j = 0; j < _j - 1; j++) {
				count++;
				int temp = count * 100 / ((_i - 1) * (_j - 1));
				if (progress != temp)
					std::cout << "Calculating normals " << temp << "% ("
							<< count << " / " << ((_i - 1) * (_j - 1)) << ")"
							<< std::endl;
				progress = temp;
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
		float mult[] = { 1, 0.5, 0.5, 0.5, 0.5, 1 };
		int i, j, k, l;
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
					l = mult[n];
					if (i >= 0 && i < normals.size() && j >= 0
							&& j < normals[0].size()) {
						normX += normals[i][j][k][0] * l;
						normY += normals[i][j][k][1] * l;
						normZ += normals[i][j][k][2] * l;
					}
				}
				float mag = sqrt(normX * normX + normY * normY + normZ * normZ);
				normX /= mag;
				normY /= mag;
				normZ /= mag;
				vertices[x][y].setNormal(normX, normY, normZ);
			}
	}

	count = 0;
	progress = 0;
	for (int i = 0; i < _i - 1; i++)
		for (int j = 0; j < _j - 1; j++) {
			count++;
			int temp = count * 100 / ((_i - 1) * (_j - 1));
			if (progress != temp)
				std::cout << "Creating drawables " << temp << "% (" << count
						<< " / " << ((_i - 1) * (_j - 1)) << ")" << std::endl;
			progress = temp;
			int texIndex = 0;
			GLVertex v1 = vertices[i][j];
			v1.setTexCoords(0, 0, texIndex);
			GLVertex v2 = vertices[i][j + 1];
			v2.setTexCoords(0, 1, texIndex);
			GLVertex v3 = vertices[i + 1][j + 1];
			v3.setTexCoords(1, 1, texIndex);
			GLVertex v4 = vertices[i + 1][j];
			v4.setTexCoords(1, 0, texIndex);
			Drawable* t1 = new Triangle(v1, v2, v4);
			Drawable* t2 = new Triangle(v2, v3, v4);
			t1->setDrawFaces(_drawFaces);
			t2->setDrawFaces(_drawFaces);
			t1->setDrawOutline(_drawOutline);
			t2->setDrawOutline(_drawOutline);
			_drawables.push_back(t1);
			_drawables.push_back(t2);
		}

	_needsUpdating = false;
}

Vector<float> Terrain::project(Vector<float> pos, bool bounded) {
	Matrix<float> modelTransformationMatrix =
			GLMatrix::modelTransformationMatrix(getX(), getY(), getZ(),
					getRotationX(), getRotationY(), getRotationZ(), getScaleX(),
					getScaleY(), getScaleZ());

	Matrix<float> inverseModelTransformationMatrix =
			GLMatrix::inverseModelTransformationMatrix(getX(), getY(), getZ(),
					getRotationX(), getRotationY(), getRotationZ(), getScaleX(),
					getScaleY(), getScaleZ());

	Matrix<float> m = Matrix<float>(4, 1);

	std::vector<float> pos1 = pos.getVector();
	pos1.push_back(1);
	m.setVector(pos1);
	m = m << inverseModelTransformationMatrix;
	pos = Vector<float>(m.get(0, 0), m.get(1, 0), m.get(2, 0));
	//pos = Vector<float>(pos[0] / _resolution, pos[1], pos[2] / _resolution);

	pos = Vector<float>(pos[0] + (float) (_length) / 2, pos[1],
			pos[2] + (float) (_width) / 2);

	float x = pos[0] / _internalScaleX * _resolution;
	float y = pos[2] / _internalScaleZ * _resolution;
	if (x < 0 || x >= _i - 1 || y < 0 || y >= _j - 1) {
		if (bounded) {
			x = std::fmax(0, std::fmin(_i - 1.001, x));
			y = std::fmax(0, std::fmin(_j - 1.001, y));
		}
		else
			return Vector<float>();
	}
	int i = (int) x;
	int j = (int) y;

	float height = 0;
	if (x - i <= 1 - (y - j)) {
		float dydx = (_heightMap[i + 1][j] - _heightMap[i][j]);
		float dydz = (_heightMap[i][j + 1] - _heightMap[i][j]);
		height = _heightMap[i][j] + dydx * (x - i) + dydz * (y - j);
	} else {
		float dydx = (_heightMap[i + 1][j + 1] - _heightMap[i][j + 1]);
		float dydz = (_heightMap[i + 1][j + 1] - _heightMap[i + 1][j]);
		height = _heightMap[i + 1][j + 1] - dydx * (1 - (x - i))
				- dydz * (1 - (y - j));
	}

	pos = Vector<float>(
			x * _internalScaleX / _resolution - (float) (_length) / 2,
			height * _internalScaleY,
			y * _internalScaleZ / _resolution - (float) (_width) / 2);

	pos1 = pos.getVector();
	pos1.push_back(1);
	m.setVector(pos1);
	m = m << modelTransformationMatrix;
	pos = Vector<float>(m.get(0, 0), m.get(1, 0), m.get(2, 0));

	return pos;
}

void Terrain::setLightingType(LightingType lightingType) {
	if (_lightingType != lightingType) {
		_lightingType = lightingType;
		_needsUpdating = true;
	}
}

void Terrain::setDrawFaces(bool drawFaces) {
	if (_drawFaces != drawFaces) {
		_drawFaces = drawFaces;
		_needsUpdating = true;
	}
}

void Terrain::setDrawOutline(bool drawOutline) {
	if (_drawOutline != drawOutline) {
		_drawOutline = drawOutline;
		_needsUpdating = true;
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
	for (int i = 0; i < _i; i++)
		for (int j = 0; j < _j; j++)
			points.push_back(Vector<float>(i, j));
	for (int n = 0; n < num; n++) {
		random_shuffle(points.begin(), points.end());
		for (int n = 0; n < points.size(); n++) {
			int i = points[n][0];
			int j = points[n][1];
			adjacentHeights.clear();
			float averageHeight = 0;
			for (int x = std::max(i - 1, 0); x <= std::min(i + 1, _i - 1); x++)
				for (int y = std::max(j - 1, 0); y <= std::min(j + 1, _j - 1);
						y++)
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

void Terrain::setColor(float r, float g, float b) {
	_color = Vector<float>(r, g, b);
}

void Terrain::logMatrixRepresentation() {
	Matrix<float> m = Matrix<float>(_i, _j);
	m.setMatrix(_heightMap);
	_application->_logger->log(m);
}

bool Terrain::checkFractal() {
	return (_i == _j && _i > 1 && ((_i - 1) & (_i - 2)) == 0);
}

