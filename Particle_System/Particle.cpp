#include "Particle.h"
#include <iostream>

long Particle::numParticles;

Particle::Particle(int particleType, float position[3], float direction[3], float speed, float size, float color[3])
{
	numParticles++;
	this->lifeRemaining = 30;
	for (int i = 0; i <= 2; i++)
		this->rotation[i] = rand() % 359;
	
	for (int i = 0; i <= 2; i++)
	{
		this->position[i] = position[i];
		this->direction[i] = direction[i];
		this->color[i] = color[i];
	}
}

void Particle::updateLife()
{
	this->lifeRemaining--;
}

/*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Getters
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

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

/* 
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Setters 
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


void Particle::setPosition(float newPosition[3])
{
	//add safety checks
	this->position[0] = newPosition[0];
	this->position[1] = newPosition[1];
	this->position[2] = newPosition[2];
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