/*
 * Cube.h
 *
 *  Created on: Apr 14, 2015
 *      Author: ericwadkins
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Drawable.h"

class Cube: public Drawable {
public:
	Cube();
	virtual ~Cube() {
	}
	virtual std::vector<GLComponent*> getComponents();
	virtual std::vector<GLTriangle*> getTriangles();
	virtual std::vector<GLLine*> getLines();
	virtual Drawable* clone();
	GLTriangle* _f1t1;
	GLTriangle* _f1t2;
	GLTriangle* _f2t1;
	GLTriangle* _f2t2;
	GLTriangle* _f3t1;
	GLTriangle* _f4t1;
	GLTriangle* _f3t2;
	GLTriangle* _f4t2;
	GLTriangle* _f5t1;
	GLTriangle* _f5t2;
	GLTriangle* _f6t1;
	GLTriangle* _f6t2;
	GLLine* _l1;
	GLLine* _l2;
	GLLine* _l3;
	GLLine* _l4;
	GLLine* _l5;
	GLLine* _l6;
	GLLine* _l7;
	GLLine* _l8;
	GLLine* _l9;
	GLLine* _l10;
	GLLine* _l11;
	GLLine* _l12;
};

#endif /* CUBE_H_ */
