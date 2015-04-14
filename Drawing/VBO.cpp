/*
 * VBO.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#include "../Drawing/VBO.h"

template<typename T>
VBO<T>::VBO(Type type) {
	_type = type;
	_vao = 0;
	_vbo = 0;
}

template<typename T>
void VBO<T>::add(T* drawable) {
	_drawables.push_back(drawable);
}

template<typename T>
void VBO<T>::updateData() {
	for (int i = 0; i < _drawables.size(); i++) {
		std::vector<Vertex*> vertices = _drawables[i]->getVertices();
		for (int j = 0; j < vertices.size(); j++) {
			Vertex* v = vertices[j];
			std::vector<float> pos = v->getPosition();
			std::vector<float> color = v->getColor();
			std::vector<float> norm = v->getNormal();
			std::vector<float> tex = v->getTexCoords();
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
void VBO<T>::create() {

	if (_type == STATIC) {
		// Make and bind the VAO
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Make and bind the VBO
		glGenBuffers(1, &_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(GLfloat), &_data[0],
		GL_STATIC_DRAW);

		// Add position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), 0);
		// Add color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),
				reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
		// Add normal attribute
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat),
				reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
		// Add tex coord attribute
		// XXX Not sure about the 6 * sizeof(GLfloat) for the tex coord attribute
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
	else
		throw "Non-static VBO not supported yet";

}

template<typename T>
void VBO<T>::draw() {

	int vertexCount = 0;
	for (int i = 0; i < _drawables.size(); i++)
		vertexCount += _drawables[i]->getVertices().size();

	// Bind the VAO
	glBindVertexArray(_vao);

	// Draw the VAO
	glDrawArrays(T::type, 0, vertexCount);

	// Unbind the VAO
	glBindVertexArray(0);

}

// Explicit instantiation of template classes
template class VBO<GLTriangle> ;
