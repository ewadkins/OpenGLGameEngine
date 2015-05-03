/*
 * Line.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef COMPONENTS_GLLINE_H_
#define COMPONENTS_GLLINE_H_

#include "../Components/GLComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLLine : public GLComponent {
public:
	GLLine(Vertex v1, Vertex v2);
	virtual ~GLLine() {
	}
	virtual std::vector<Vertex> getVertices();
	virtual void setVertices(std::vector<Vertex> vertices);
	GLLine* clone();
	static int _type;
private:
	std::vector<Vertex> _vertices;
};

#endif /* COMPONENTS_GLLINE_H_ */
