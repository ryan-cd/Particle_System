/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
RYAN DAVIS
Tested and working on WINDOWS 8.1
Main Extra Features. Please see these in particular:

17) Wind. Use the function keys F1-F6 to manipulate the wind in the environment
19) Particle Properties. Use the keys 1-4 to change the particle properties

Optional third feature for bonus marks:

16) Particle Cannon. Use WASD to change the cannon angle
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include "Headers.h" //this file contains all the headers needed for the program


/*Globals.*/
float gCamPos[3] = { 0, 13, 50 }; // where the camera is
float gSceneRotation[3] = { 0, 0, 0 }; //the rotation of the scene

//variables for the platform
float gPlatformColors[6][3] = { { 1, 0, 0 }, { 0, 1, 1 }, { 1, 1, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 } }; //colors of the faces of the platform box
float gPlatformWidth = 30;
float gPlatformHeight = 1;
float gPlatformDepth = 30;

float gParticleSysPos[3] = { 0, 15, 0 }; //particle emmiter location
float gGravity = (float) -0.007; //this gets applied to the particles every update
float gWind[3] = { 0, 0, 0 }; //applied to the particles
float gCannonRotation[3] = { 0, 0, 0 }; //rotation of the cannon

bool gPause = false; //whether the simulation is running


ShapeCreator shapeCreator; //this will handle drawing the platform
ParticleSystem particleSystem(gParticleSysPos, gGravity, gWind); //this is the particle emmitter class


//runs some overhead code
void init(void)
{
	cout << "Welcome to Particle Generator\n\n"
		"Controls: \n"
		"SPACE to start/stop the simulation\n"
		"r to reset the simulation\n"
		"q to quit\n"
		"arrow keys to rotate the scene\n"
		"F1, F2 to rotate the wind on the x axis\n"
		"F3, F4 to rotate the wind on the y axis\n"
		"F5, F6 to rotate the wind on the z axis\n"
		"f to toggle friction. \n   (It is most noticeable if you \n   add a downward wind first (F4)\n"
		"W, S to rotate the cannon on the X axis\n"
		"A, D to rotate the cannon on the Z axis\n"
		"HOME, END to move the camera up and down\n"
		"1, 2, 3, 4 changes the type of particle to make";
	//set random number generator seed
	srand(time(NULL));

	//tell the particle system where the platform edges are
	particleSystem.setPlatformDimensions(gPlatformWidth, gPlatformHeight, gPlatformDepth);

	/* Setup GL features */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); //enable backface culling

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
	case ' ':
		//toggle pause
		gPause = (gPause == true) ? false : true;
		break;
	case 'r':
		//reset the simulation
		particleSystem.reset();
		break;

	/* WASD changes the rotation of the cannon */
	case 'w':
		if (gCannonRotation[0] > 0)
			gCannonRotation[0]--;
		else
			gCannonRotation[0] = 359;
		particleSystem.setCannonRotation(gCannonRotation);
		break;
	case 's':
		if (gCannonRotation[0] < 360)
			gCannonRotation[0]++;
		else
			gCannonRotation[0] = 0;
		particleSystem.setCannonRotation(gCannonRotation);
		break;
	case 'd':
		if (gCannonRotation[2] > 0)
			gCannonRotation[2]--;
		else
			gCannonRotation[2] = 359;
		particleSystem.setCannonRotation(gCannonRotation);
		break;
	case 'a':
		if (gCannonRotation[2] < 360)
			gCannonRotation[2]++;
		else
			gCannonRotation[2] = 0;
		particleSystem.setCannonRotation(gCannonRotation);
		break;

	case 'f':
		particleSystem.toggleFriction();
		break;

	/* 1234 changes the particle types*/
	case '1':
		particleSystem.setParticleType(0);
		break;
	case '2':
		particleSystem.setParticleType(1);
		break;
	case '3':
		particleSystem.setParticleType(2);
		break;
	case '4':
		particleSystem.setParticleType(3);
		break;

	/* quit program */
	case 'q':
	case 27:	//27 is the esc key
		exit(0);
		break;
	}
}

void special(int key, int x, int y)
{
	switch (key)
	{
	
		/* Arrow keys change the rotation of the scene*/
	case GLUT_KEY_RIGHT:
		gSceneRotation[1] -= 1;
		break;

	case GLUT_KEY_LEFT:
		gSceneRotation[1] += 1;
		break;

	case GLUT_KEY_UP:
		gSceneRotation[0] += 1;
		break;

	case GLUT_KEY_DOWN:
		gSceneRotation[0] -= 1;
		break;

		/*HOME/END moves the camera along the y axis*/
	case GLUT_KEY_HOME:
		gCamPos[1] += 0.3;
		break;

	case GLUT_KEY_END:
		gCamPos[1] -= 0.3;
		break;
		
		/*Function keys change the wind intensity in each direction*/
	case GLUT_KEY_F1:
		if (gWind[0] > particleSystem.getWindBoundary(0))
		{
			gWind[0] -= 0.05;
			particleSystem.updateWind(gWind);
		}
		break;

	case GLUT_KEY_F2:
		if (gWind[0] < particleSystem.getWindBoundary(1))
		{
			gWind[0] += 0.05;
			particleSystem.updateWind(gWind);
		}
		break;

	case GLUT_KEY_F3:
		if (gWind[1] < particleSystem.getWindBoundary(1))
		{
			gWind[1] += 0.05;
			particleSystem.updateWind(gWind);
		}
		break;

	case GLUT_KEY_F4:
		if (gWind[1] > particleSystem.getWindBoundary(0))
		{
			gWind[1] -= 0.05;
			particleSystem.updateWind(gWind);
		}
		break;

	case GLUT_KEY_F5:
		if (gWind[2] < particleSystem.getWindBoundary(1))
		{
			gWind[2] += 0.05;
			particleSystem.updateWind(gWind);
		}
		break;

	case GLUT_KEY_F6:
		if (gWind[2] > particleSystem.getWindBoundary(0))
		{
			gWind[2] -= 0.05;
			particleSystem.updateWind(gWind);
		}
		break;
	}

	glutPostRedisplay(); //run display function
}

/* display function - GLUT display callback function
*/
void display(void)
{
	float origin[3] = { 0, 0, 0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(gCamPos[0], gCamPos[1], gCamPos[2], 0, 0, 0, 0, 1, 0); //tell camera to look at origin
	

	glPushMatrix(); // push scene rotation
	//rotate the scene by the amount specified by the user
	glRotatef(gSceneRotation[0], 1, 0, 0);
	glRotatef(gSceneRotation[1], 0, 1, 0);

	//draw the platform
	shapeCreator.drawBox(origin, gPlatformWidth, gPlatformHeight, gPlatformDepth, gPlatformColors);
	
	glPushMatrix(); //push particle cannon rotation
	//rotate the cannon
	glRotatef(particleSystem.getCannonRotation(0), 1, 0, 0);
	glRotatef(particleSystem.getCannonRotation(2), 0, 0, 1);
	glPushMatrix(); //push cannon translation
	
	//move the cannon to the specified place
	glTranslatef(gParticleSysPos[0], gParticleSysPos[1]+1.1, gParticleSysPos[2]);
	glRotatef(270, 0, 0, 1);
	glutSolidTeapot(1); //draw the cannon

	glPopMatrix(); //pop cannon translation
	
	particleSystem.drawParticles(); //tell the particle system to draw the particles
	glPopMatrix(); //pop cannon rotation
	
	
	glPopMatrix(); //pop scene rotation

	glutSwapBuffers(); 
}

void timer(int value)
{
	glutTimerFunc(8, timer, 0); //set the time for the next timer call

	//only spawn particles if the simulation is not paused 
	if (!gPause)
	{
		particleSystem.spawnParticle();
	}

	//update the particle locations
	particleSystem.updateParticles();

	glutPostRedisplay(); //call display function
}


/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); 

	glutInitWindowSize(900, 900);
	glutInitWindowPosition(600, 0);

	glutCreateWindow("Particle Generator");	//creates the window

	//register callbacks
	glutDisplayFunc(display);	
	glutKeyboardFunc(keyboard); 
	glutSpecialFunc(special);
	glutTimerFunc(1, timer, 0);
	
	init(); //setup overhead stuff


	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
