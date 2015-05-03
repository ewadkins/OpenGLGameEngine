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
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	Triangle(Triangle* other);
	Triangle();
	virtual ~Triangle() {
	}
	virtual std::vector<GLComponent*> getComponents();
	virtual std::vector<GLTriangle*> getTransformedTriangles();
	virtual std::vector<GLTriangle*> getTriangles();
	virtual std::vector<GLLine*> getTransformedLines();
	virtual std::vector<GLLine*> getLines();
	virtual Drawable* clone();
	GLTriangle* _triangle;
	GLLine* _l1;
	GLLine* _l2;
	GLLine* _l3;
protected:
	virtual void setTransformed(Drawable* transformed);
private:
	std::vector<GLTriangle*> _triangles;
	std::vector<GLLine*> _lines;
	Triangle* _transformed;
};

#endif /* TRIANGLE_H_ */
