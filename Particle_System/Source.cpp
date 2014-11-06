#include "Headers.h"


//Globals.
float gCamPos[3] = { 0, 3, 20 }; // where the camera is

//float gPlatformVerteces[8][3] = { { -1, -1, 1 }, { -1, 1, 1 }, { 1, 1, 1 }, { 1, -1, 1 }, { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 }, { 1, -1, -1 } }; //vertices to make a platform box
float gPlatformColors[6][3] = { { 1, 0, 0 }, { 0, 1, 1 }, { 1, 1, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 } }; //colors of the faces of the platform box
float gPlatformWidth = 10;
float gPlatformHeight = 1;
float gPlatformDepth = 10;

float gParticleSysPos[3] = { 0, 5, 0 };
float gGravity = (float) -1/1.2;
float gWind[3] = { 1, 0, 0 };

bool gPause = false;

ShapeCreator shapeCreator;
ParticleSystem particleSystem(gParticleSysPos, gGravity, gWind);

void init(void)
{
	//set random number generator seed
	srand(time(NULL));


	/* Setup GL features */
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0, 0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	
}




/* Callbacks start here */

//Keyboard callback
void keyboard(unsigned char key, int xIn, int yIn)
{
	switch (key)
	{
	case 'p':
		//toggle pause
		gPause = (gPause == true) ? false : true;
		break;
	case 'w':
		particleSystem.spawnParticle();
		break;
	case 'e':
		particleSystem.updateParticles();
		break;
	case 'q':
	case 27:	//27 is the esc key
		exit(0);
		break;
	}
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch (key)
	{
	case GLUT_KEY_LEFT:
		gCamPos[0] -= 0.3;
		break;

	case GLUT_KEY_RIGHT:
		gCamPos[0] += 0.3;
		break;

	case GLUT_KEY_UP:
		gCamPos[2] -= 0.3;
		break;

	case GLUT_KEY_DOWN:
		gCamPos[2] += 0.3;
		break;

	case GLUT_KEY_HOME:
		gCamPos[1] += 0.3;
		break;

	case GLUT_KEY_END:
		gCamPos[1] -= 0.3;
		break;

	}
	glutPostRedisplay();
}

/* display function - GLUT display callback function
*		clears the screen, sets the camera position, draws the ground plane and movable box
*/
void display(void)
{
	float origin[3] = { 0, 0, 0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(gCamPos[0], gCamPos[1], gCamPos[2], 0, 0, 0, 0, 1, 0);
	

	
	shapeCreator.drawBox(origin, gPlatformWidth, gPlatformHeight, gPlatformDepth, gPlatformColors);
	
	
	particleSystem.drawParticles();
	
	glutSwapBuffers();
}

void timer(int value)
{
	glutTimerFunc(500, timer, 0);
	if (!gPause)
	{
		//particleSystem.spawnParticle();
		particleSystem.updateParticles();

		glutPostRedisplay();
	}
}


/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(1200, 1200);
	glutInitWindowPosition(600, 0);

	glutCreateWindow("Particle Generator");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(1, timer, 0);
	
	init(); //setup globals and other opengl features


	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
