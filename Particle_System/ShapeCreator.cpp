#include "ShapeCreator.h"

ShapeCreator::ShapeCreator(){	//constructor
	
}

//note: the functionality of the box drawing is from the tutorial code for this course
void ShapeCreator::drawBox(float* origin, float w, float h, float d, float colors [6][3]){	//function to draw box
	float vertices[8][3] = { { origin[0] - w / 2, origin[1] - h / 2, origin[2] + d / 2 },
							{ origin[0] - w / 2, origin[1] + h / 2, origin[2] + d / 2 },
							{ origin[0] + w / 2, origin[1] + h / 2, origin[2] + d / 2 },
							{ origin[0] + w / 2, origin[1] - h / 2, origin[2] + d / 2 },
							{ origin[0] - w / 2, origin[1] - h / 2, origin[2] - d / 2 },
							{ origin[0] - w / 2, origin[1] + h / 2, origin[2] - d / 2 },
							{ origin[0] + w / 2, origin[1] + h / 2, origin[2] - d / 2 },
							{ origin[0] + w / 2, origin[1] - h / 2, origin[2] - d / 2 } };
	
	cube(vertices, colors);
}

/* drawPolygon - takes 4 indices and an array of vertices
*   and draws a polygon using the vertices indexed by the indices
*   Code is from class tutorial
*   this is a private function
*/
void ShapeCreator::drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
	glVertex3fv(v[a]);
	glVertex3fv(v[b]);
	glVertex3fv(v[c]);
	glVertex3fv(v[d]);
	glEnd();
}

/* cube - takes an array of 8 vertices, and draws 6 faces
*  with drawPolygon, making up a box
*  code is from our class's tutorial
*  this is a private function
*/
void ShapeCreator::cube(float v[8][3], float colors[6][3])
{
	glColor3fv(colors[1]);
	drawPolygon(0, 3, 2, 1, v);

	glColor3fv(colors[2]);
	//drawPolygon(1, 0, 4, 5, v);
	drawPolygon(0, 1, 5, 4, v);

	glColor3fv(colors[3]);
	drawPolygon(5, 1, 2, 6, v);

	glColor3fv(colors[4]);
	drawPolygon(2, 3, 7, 6, v);

	glColor3fv(colors[5]);
	//drawPolygon(6, 5, 4, 7, v);
	drawPolygon(4, 5, 6, 7, v);

	glColor3fv(colors[0]);
	//drawPolygon(4, 0, 3, 7, v);
	drawPolygon(0, 4, 7, 3, v);
}