/*
 * Triangle.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Drawable.h"

class Triangle: public Drawable {
public:
	Triangle(Vertex* v1, Vertex* v2, Vertex* v3);
	Triangle();
	virtual ~Triangle() {
	}
	virtual std::vector<GLTriangle*> getTriangles();
	virtual std::vector<GLLine*> getLines();
	virtual Drawable* clone();
	GLTriangle* _triangle;
	GLLine* _l1;
	GLLine* _l2;
	GLLine* _l3;
};

#endif /* TRIANGLE_H_ */
