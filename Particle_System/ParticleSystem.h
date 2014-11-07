#ifndef __PARTICLE_SYSTEM_H__	//guard against cyclic dependancy
#define __PARTICLE_SYSTEM_H__

#include "Headers.h"
#include "Particle.h"
#include <stdlib.h>

class ParticleSystem{
public:
	ParticleSystem(float position[3], float gravity, float wind[3]);	//constructor
	float getLifeRemaining(void); //returns the health remaining of a particle.
	void spawnParticle(void);
	void drawParticles(void);
	void updateParticles(void);
	float getGravity(); //returns the saved gravity
	void setPlatformDimensions(float width, float height, float depth);
	void toggleFriction(); 

private:
	float position[3]; //where the particle system is
	float gravity; //gravity is a downward force in the -y direction
	float wind[3];//how much force to apply in the wind direction
	bool isExplosion; //the partice system behaves differently if it is an explosion
	float minX, minY, bounceY, minZ, maxX, maxZ;
	bool friction;

	//doubly linked list storing particles
	struct ParticleList{
		Particle* element;
		ParticleList* next;
		ParticleList* prev;
	};

	ParticleList* head;
	ParticleList* tail;
	ParticleList* iterator0; //iterator of the element before the one currently selected
	ParticleList* iterator1; //iterator of the currently selected element
	ParticleList* iterator2; //iterator of the element after the one currently selected
	ParticleList* iteratorA; //iterator for general purposes
	
};

#endif