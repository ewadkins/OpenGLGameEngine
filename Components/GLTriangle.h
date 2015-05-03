/*
 * Triangle.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ericwadkins
 */

#ifndef COMPONENTS_GLTRIANGLE_H_
#define COMPONENTS_GLTRIANGLE_H_

#include "../Components/GLComponent.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLTriangle : public GLComponent {
public:
	GLTriangle(Vertex* v1, Vertex* v2, Vertex* v3);
	virtual ~GLTriangle() {
	}
	virtual std::vector<Vertex*> getVertices();
	virtual void setVertices(std::vector<Vertex*> vertices);
	virtual GLComponent* clone();
	void useFaceNormal();
	static int _type;
private:
	std::vector<Vertex*> _vertices;
};

#endif /* COMPONENTS_GLTRIANGLE_H_ */
