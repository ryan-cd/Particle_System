#ifndef __PARTICLE_SYSTEM_H__	//guard against cyclic dependancy
#define __PARTICLE_SYSTEM_H__

#include "Headers.h"
#include "Particle.h"
#include <stdlib.h>

class ParticleSystem{
public:
	ParticleSystem(float position[3], float gravity, float wind[3]);	//constructor
	float getLifeRemaining(void); //returns the health remaining of a particle.
	void spawnParticle(void); //add a particle to the list
	void drawParticles(void); //draw all particles in the list
	void updateParticles(void); //update the properties of every particle in list
	float getGravity(); //returns the saved gravity
	void setPlatformDimensions(float width, float height, float depth); //sets the dimensions of the platform to be bounced on
	void toggleFriction(); 
	void reset(); //clears the list of particles
	void updateWind(float newWind[3]);
	void setParticleType(int newType); //set the type of particles to make
	float getWindBoundary(int direction); // retireves min or max wind
	void setCannonRotation(float newRotation[3]); //sets rotation of the cannon
	float getCannonRotation(int axis); 

private:
	float position[3]; //where the particle system is
	float gravity; //gravity is a downward force in the -y direction
	float wind[3];//how much force to apply in the wind direction
	bool isExplosion; //the partice system behaves differently if it is an explosion
	float minX, minY, bounceY, minZ, maxX, maxZ; //these variables will show where the area is to bounce
	bool friction; //whether to apply friction
	enum _property { NORMAL, BOUNCE, FLOAT, RANDOM } particleType; //type of particle to make
	float gMinWind; //maximum amount of negative wind you can set in an axis
	float gMaxWind;//maximum amount of positive wind you can set in an axis
	float cannonRotation[3]; //the rotation of the cannon spewing particles
	

	//doubly linked list storing particles
	struct ParticleList{
		Particle* element;
		ParticleList* next;
		ParticleList* prev;
	};

	ParticleList* head; //start of list
	ParticleList* tail; //end of list
	ParticleList* iterator0; //iterator of the element before the one currently selected (unused)
	ParticleList* iterator1; //iterator of the last added element
	ParticleList* iterator2; //iterator of the element to add after the last one added
	ParticleList* iteratorA; //iterator for general purposes
	
};

#endif