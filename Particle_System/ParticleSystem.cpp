#include "ParticleSystem.h"

//IMPLEMENT DELETING WHEN FALLING TOO FAR OFF STAGE

Particle* particle; //used to create new particles in the linked list
float gParticleSize = 0.5;
float gAmountToRotate = 10;
float gSpeed = 0.09;
float gFriction = 0.9;

ParticleSystem::ParticleSystem(float position[3], float gravity, float wind[3])
{
	this->minX = this->minY = this->minZ = 0;
	this->gravity = gravity;
	this->friction = true;

	for (int i = 0; i <= 2; i++)
		this->position[i] = position[i];
	


	iterator0 = NULL;
	iterator1 = NULL;
	iterator2 = NULL;
	
	tail = iterator1;

	
}

void ParticleSystem::spawnParticle(void)
{
	//if the head is not set (the list is empty) then make the new list the head
	if (head == NULL)
		head = iterator1;

	
	float newColor[3] = { (float)(rand() / (float)(RAND_MAX + 1)), 
		(float)(rand() / (float)(RAND_MAX + 1)), 
		(float)(rand() / (float)(RAND_MAX + 1)) };

	float direction[3] = { 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f,
		(-0.5 * (float)rand() / (float)RAND_MAX) - 0.5,
		2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f };
	
	
	particle = new Particle(0, this->position, direction, 1, 1, newColor);
	

	iterator2 = new ParticleList;
	if (iterator1 != NULL && iterator1->element != NULL)
		iterator1->next = iterator2;

	iterator2->element = particle;
	
	if (iterator1 != NULL && iterator1->element != NULL)
		iterator2->prev = iterator1;
	else
	{
		iterator2->prev = NULL;
		head = iterator2;
	}

	iterator2->next = NULL;
	
	iterator1 = iterator2;

	tail = iterator1;

}

void ParticleSystem::drawParticles(void)
{
	
	iteratorA = head;
	//printf("Num Elements: %d", iteratorA != NULL ? iteratorA->element->getNumParticles() : 0);
	
	
	
	while (iteratorA != NULL && iteratorA->element != NULL)
	{
		glPushMatrix();
		glColor3f(iteratorA->element->getColor(0), 
			iteratorA->element->getColor(1), 
			iteratorA->element->getColor(2));
		
		glTranslatef(iteratorA->element->getPosition(0),
						iteratorA->element->getPosition(1),
						iteratorA->element->getPosition(2));

		glRotatef(iteratorA->element->getRotation(0), 1, 0, 0);
		glRotatef(iteratorA->element->getRotation(1), 0, 1, 0);
		glRotatef(iteratorA->element->getRotation(2), 0, 0, 1);

		glutSolidCube(gParticleSize);
		glPopMatrix();

		iteratorA = iteratorA->next;
	}
	
}

void ParticleSystem::updateParticles(void)
{
	iteratorA = head;
	
	
	
	float newPosition[3] = { 0, 0, 0 };
	float newRotation[3] = { 0, 0, 0 };

	while (iteratorA != NULL && iteratorA->element != NULL)
	{

		iteratorA->element->updateLife();
		if (iteratorA->element->getLifeRemaining() <= 0)
		{

			if (iteratorA->prev != NULL)
				iteratorA->prev->next = iteratorA->next;
			if (iteratorA->next != NULL)
				iteratorA->next->prev = iteratorA->prev;

			iteratorA->element->decrementNumParticles();

			iteratorA->element = NULL;
			iteratorA = iteratorA->next;
			head = iteratorA;

			continue;

		}

		//set newPosition[3] to hold the new position of the particle
		for (int i = 0; i <= 2; i++)
		{
			newPosition[i] = iteratorA->element->getPosition(i);
			newPosition[i] += iteratorA->element->getDirection(i) * gSpeed;

			newRotation[i] += gAmountToRotate;
		}
		iteratorA->element->applyGravity(getGravity());

		if (newPosition[1] < this->bounceY
			&& newPosition[0] > this->minX
			&& newPosition[0] < this->maxX
			&& newPosition[2] > this->minZ
			&& newPosition[2] < this->maxZ)
		{
			iteratorA->element->invertYDirection();
			//iteratorA->element->applyGravity(0.5);
			newPosition[1] = bounceY;
			if (this->friction)
			{
				iteratorA->element->applyFriction(gFriction);
			}
				
		}
		
		//move the element to newPosition
		iteratorA->element->setPosition(newPosition);
		iteratorA->element->setRotation(newRotation);

		//tell newPosition to go back to the spawn position
		for (int i = 0; i < 2; i++)
			newPosition[i] = this->position[i];
		
		//iterate to the next particle
		iteratorA = iteratorA->next;
	}
}

/* Get Gravity */
/* Depending on the mode, this may be calculated differently*/
float ParticleSystem::getGravity()
{
	return this->gravity;
}

void ParticleSystem::setPlatformDimensions(float width, float height, float depth)
{
	minX = -width / 2;
	maxX = width / 2;
	minY = -width; // erase when fallen too far past the floor
	bounceY = height / 2; //y value where a bounce should happen (top of platform)
	minZ = -depth / 2;
	maxZ = depth / 2;
}

void ParticleSystem::toggleFriction(void)
{
	this->friction = this->friction ? false : true;
}

void ParticleSystem::reset()
{
	if (head)
		head->element->setNumParticles(0);
	head = tail = iteratorA = NULL;
}