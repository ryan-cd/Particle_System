#ifndef __SHAPE_CREATOR_H__	//guard against cyclic dependancy
#define __SHAPE_CREATOR_H__

#include "Headers.h"

class ShapeCreator{
public:
	ShapeCreator();	//constructor
	void drawBox(float* origin, float w, float h, float d, float colors[6][3]);	// 3d box shape

	
private:
	
	
	/* drawPolygon - takes 4 indices and an array of vertices
	*   and draws a polygon using the vertices indexed by the indices
	*/
	void drawPolygon(int a, int b, int c, int d, float v[8][3]);

	/* cube - takes an array of 8 vertices, and draws 6 faces
	*  with drawPolygon, making up a box
	*/
	void cube(float v[8][3], float colors[6][3]);
};

#endif