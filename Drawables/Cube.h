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
	virtual std::vector<GLTriangle*> getTriangles();
	virtual std::vector<GLLine*> getLines();
	GLTriangle* _face1Tri1;
	GLTriangle* _face1Tri2;
	GLTriangle* _face2Tri1;
	GLTriangle* _face2Tri2;
	GLTriangle* _face3Tri1;
	GLTriangle* _face4Tri1;
	GLTriangle* _face3Tri2;
	GLTriangle* _face4Tri2;
	GLTriangle* _face5Tri1;
	GLTriangle* _face5Tri2;
	GLTriangle* _face6Tri1;
	GLTriangle* _face6Tri2;
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
