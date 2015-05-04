/*
 * VBO.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "VBO.h"

template<typename T>
VBO<T>::VBO(Type type) {
	_type = type;
	_vao = 0;
	_vbo = 0;
}

template<typename T>
void VBO<T>::add(T component) {
	_components.push_back(component);
}

template<typename T>
void VBO<T>::clear() {
	_components.clear();
}

template<typename T>
void VBO<T>::updateData() {
	_data.clear();
	for (int i = 0; i < _components.size(); i++) {
		std::vector<Vertex> vertices = _components[i].getVertices();
		for (int j = 0; j < vertices.size(); j++) {
			Vertex v = vertices[j];
			std::vector<float> pos = v.getPosition();
			std::vector<float> color = v.getColor();
			std::vector<float> norm = v.getNormal();
			std::vector<float> tex = v.getTexCoords();

			_data.push_back(pos[0]);
			_data.push_back(pos[1]);
			_data.push_back(pos[2]);
			_data.push_back(color[0]);
			_data.push_back(color[1]);
			_data.push_back(color[2]);
			_data.push_back(norm[0]);
			_data.push_back(norm[1]);
			_data.push_back(norm[2]);
			_data.push_back(tex[0]);
			_data.push_back(tex[1]);
		}
	}
}

template<typename T>
void VBO<T>::pushToBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	if (_type == STREAM)
		glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(GLfloat), &_data[0],
		GL_STREAM_DRAW);
	else if (_type == DYNAMIC)
		glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(GLfloat), &_data[0],
		GL_DYNAMIC_DRAW);
	else if (_type == STATIC)
		glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(GLfloat), &_data[0],
		GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void VBO<T>::create() {

	// Make and bind the VAO
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Make and bind the VBO
	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Add position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), 0);
	// Add color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),
			reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	// Add normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),
			reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
	// Add tex coord attribute
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),
			reinterpret_cast<GLvoid*>(9 * sizeof(GLfloat)));

	// Enable the attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

template<typename T>
void VBO<T>::draw() {

	if (_data.size() > 0) {
		int vertexCount = 0;
		for (int i = 0; i < _components.size(); i++)
			vertexCount += _components[i].getVertices().size();

		// Bind the VAO
		glBindVertexArray(_vao);

		// Draw the VAO
		glDrawArrays(T::_type, 0, vertexCount);

		// Unbind the VAO
		glBindVertexArray(0);
	}

}

// Explicit instantiation of template classes
template class VBO<GLTriangle> ;
template class VBO<GLLine> ;
