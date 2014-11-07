#include "Particle.h"
#include <iostream>

long Particle::numParticles;

Particle::Particle(int particleType, float position[3], float direction[3], float speed, float size, float color[3])
{
	this->particleType = (_property) particleType; //use the particleType from argument list
	numParticles++; //add to the number of alive particles
	this->lifeRemaining = 900; //timeout time default
	//random rotation on each axis
	for (int i = 0; i <= 2; i++)
		this->rotation[i] = rand() % 359; 
	
	//set the position, direction, and color
	for (int i = 0; i <= 2; i++)
	{
		this->position[i] = position[i];
		this->direction[i] = direction[i];
		this->color[i] = color[i];
	}
}

//decrement the timeout timer
void Particle::updateLife()
{
	this->lifeRemaining--;
}

/*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Getters
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

//get time to timeout
float Particle::getLifeRemaining()
{
	return this->lifeRemaining;
}

float Particle::getPosition(int position)
{
	if (0 <= position && position <= 2)
		return this->position[position];
	else
	{
		//This is an exception case
		return 0;
	}
}

float Particle::getDirection(int direction)
{
	if (0 <= direction && direction <= 2)
		return this->direction[direction];
	else
	{
		//This is an exception case

		return 0;
	}
}

float Particle::getColor(int newColor)
{
	if (0 <= newColor && newColor <= 2)
		return this->color[newColor];
	else
	{
		//This is an exception case

		return 0;
	}
}

long Particle::getNumParticles(void)
{
	return numParticles;
}

float Particle::getRotation(int axis)
{
	if (0 <= axis && axis <= 2)
		return this->rotation[axis];
	else
		return 0;
}

int Particle::getParticleType(void)
{
	return (int)this->particleType;
}



/* 
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Setters 
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


void Particle::setPosition(float newPosition[3])
{
	this->position[0] = newPosition[0];
	this->position[1] = newPosition[1];
	this->position[2] = newPosition[2];
}

void Particle::setRotation(float newRotation[3])
{
	for (int i = 0; i <= 2; i++)
		this->rotation[i] = newRotation[i];
}

void Particle::setLifeRemaining(int newLifeRemaining)
{
	this->lifeRemaining = newLifeRemaining;
}

void Particle::decrementNumParticles(void)
{
	this->numParticles--;
}

void Particle::invertYDirection(void)
{
	this->direction[1] *= -1;
}

void Particle::applyFriction(float friction)
{
	for (int i = 0; i <= 2; i++)
		this->direction[i] *= friction;
}

void Particle::applyGravity(float gravity)
{
	if (this->direction[1] > -0.3)
		this->direction[1] += gravity;
}

void Particle::setNumParticles(unsigned int amount)
{
	numParticles = amount;
}