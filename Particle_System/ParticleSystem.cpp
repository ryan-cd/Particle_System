#include "ParticleSystem.h"



Particle* particle; //temporary particle that is manipulated and used to create new particles in the linked list
float gParticleSize = 0.5; //size of particles to generate
float gAmountToRotate = 3; //amount to rotate each particle each frame
float gSpeed = 0.09; //speed multiplier
float gFriction = 0.9; //particles lose 10% speed upon hitting the ground

//constructor
ParticleSystem::ParticleSystem(float position[3], float gravity, float wind[3])
{
	this->minX = this->minY = this->minZ = 0; //default values of the platform dimensions
	this->gravity = gravity; //set the saved gravity to the argument
	this->friction = true; //friction on by default
	this->particleType = NORMAL; //default spawn is NORMAL particles

	//set default wind boundary amounts
	gMinWind = -0.4;
	gMaxWind = 0.4;

	//set the position and wind to the amount specified by the user
	for (int i = 0; i <= 2; i++)
	{
		this->position[i] = position[i];
		this->wind[i] = wind[i];
	}
	
	//initially the tail is iterator1
	tail = iterator1;
}

void ParticleSystem::spawnParticle(void)
{
	//if the head is not set (the list is empty) then make the new list the head
	//note that the newest element in the list will be iterator1
	if (head == NULL)
		head = iterator1;

	//initialize the particle's color values to be random
	float newColor[3] = { (float)(rand() / (float)(RAND_MAX + 1)), 
		(float)(rand() / (float)(RAND_MAX + 1)), 
		(float)(rand() / (float)(RAND_MAX + 1)) };

	//initialize the particle's direction to be random
	float direction[3] = { 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f,
		(-0.5 * (float)rand() / (float)RAND_MAX) - 0.5,
		2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f };
	
	//if the spawn type is RANDOM, pick a type that isn't RANDOM and spawn that kind of particle.
	if (this->particleType == RANDOM)
	{
		cout << "\nRandomly selected mode is: ";
		if ((float)rand() / (float)RAND_MAX > 0.66) {
			setParticleType(2); cout << "Float\n";
		}
		else if ((float)rand() / (float)RAND_MAX > 0.33){
			setParticleType(1); cout << "Bounce\n";
		}
		else{
			setParticleType(0); cout << "Normal\n";
		}
	}

	
	//create a pointer to a Particle type with all the information calculate before here
	particle = new Particle((int)this->particleType, this->position, direction, 1, 1, newColor);
	
	//iterator 2 will be the new element to add
	iterator2 = new ParticleList;
	//if the last place to be added to the list is not NULL then set its next to the new element
	if (iterator1 != NULL && iterator1->element != NULL)
		iterator1->next = iterator2;

	//set iterator2 to hold the newly made particle
	iterator2->element = particle;
	
	//if iterator1 is a particle then set iterator 2 to point backwards to it
	if (iterator1 != NULL && iterator1->element != NULL)
		iterator2->prev = iterator1;
	else
	{
		//otherwise iterator2 is the start of the list and its previous value is null
		iterator2->prev = NULL;
		head = iterator2;
	}

	//iterator2 is the newest element, set its next to hold NULL
	iterator2->next = NULL;
	
	//set iterator1 to hold the newest value
	iterator1 = iterator2;

	//the iterator named tail will hold the last element
	tail = iterator1;
}

void ParticleSystem::drawParticles(void)
{
	iteratorA = head; //set iteratorA to the start of the list
	
	//while the iteratorA position is on a valid particle element
	while (iteratorA != NULL && iteratorA->element != NULL)
	{
		glPushMatrix(); //push transformations
		//grab the color of the element and set the gl color to that
		glColor3f(iteratorA->element->getColor(0), 
			iteratorA->element->getColor(1), 
			iteratorA->element->getColor(2));
		
		//translate to the place the particle specifies
		glTranslatef(iteratorA->element->getPosition(0),
						iteratorA->element->getPosition(1),
						iteratorA->element->getPosition(2));

		//rotate the amount the particle specifies
		glRotatef(iteratorA->element->getRotation(0), 1, 0, 0);
		glRotatef(iteratorA->element->getRotation(1), 0, 1, 0);
		glRotatef(iteratorA->element->getRotation(2), 0, 0, 1);

		//create a cube with the parameters above
		glutSolidCube(gParticleSize);
		glPopMatrix(); //pop transformations

		iteratorA = iteratorA->next; //iterate to next position
	}
	
}

void ParticleSystem::updateParticles(void)
{
	iteratorA = head; //set iteratorA to the start of the list
	
	//variables for the new position and rotation
	float newPosition[3] = { 0, 0, 0 };
	float newRotation[3] = { 0, 0, 0 };

	//while iteratorA is pointing to a valid particle element
	while (iteratorA != NULL && iteratorA->element != NULL)
	{
		iteratorA->element->updateLife(); //update the particle's timeout time

		//if the particle timed out
		if (iteratorA->element->getLifeRemaining() <= 0)
		{
			//remake the list pointers to remove the dead particle
			if (iteratorA->prev != NULL)
				iteratorA->prev->next = iteratorA->next;
			if (iteratorA->next != NULL)
				iteratorA->next->prev = iteratorA->prev;

			//decrease the counter of the number of particles alive
			iteratorA->element->decrementNumParticles();

			//set the dead element to be null
			iteratorA->element = NULL;

			//iterate to the next list position
			iteratorA = iteratorA->next;
			//move the list head
			head = iteratorA;

			//skip the calculation steps because the particle is dead
			continue;
		}
		
		
		//set newPosition[3] to hold the new position of the particle
		for (int i = 0; i <= 2; i++)
		{
			//initialize the new position to the old position
			newPosition[i] = iteratorA->element->getPosition(i);

			//add the direction. apply speed and wind modifications
			newPosition[i] += iteratorA->element->getDirection(i) * gSpeed + this->wind[i];

			//if the type is bounce add more speed
			if (iteratorA->element->getParticleType() == 1)
			{
				newPosition[i] += iteratorA->element->getDirection(i) * gSpeed;
			}
			//if the type is float subtract speed
			else if (iteratorA->element->getParticleType() == 2)
			{
				newPosition[i] -= iteratorA->element->getDirection(i) * 0.3*gSpeed;
			}

			//set the rotation variable
			if (newRotation[i] += gAmountToRotate < 359)
				newRotation[i] += gAmountToRotate;
			else
				newRotation[i] = 360 - gAmountToRotate;
		}
		
		//apply gravity to the element
		iteratorA->element->applyGravity(getGravity());

		//if the particle is projected to hit the platform
		if (newPosition[1] < this->bounceY
			&& newPosition[0] > this->minX
			&& newPosition[0] < this->maxX
			&& newPosition[2] > this->minZ
			&& newPosition[2] < this->maxZ)
		{
			iteratorA->element->invertYDirection(); //flip y direction
			
			newPosition[1] = bounceY; //move the particle up a bit to bring it above the platform
			
			//if friction is on, apply the friction
			if (this->friction)
			{
				iteratorA->element->applyFriction(gFriction);
			}
				
		}
		
		//move the element to newPosition and apply newRotation
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
	//if the type is float then make gravity reduced
	if (this->particleType == 2)
		return this->gravity * 0.4;
	
	return this->gravity;
}

/* Grabs platform dimensions to calculate where its endpoints are*/
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
	head = tail = iteratorA = NULL; //NULLING these vectors will clear the list
}

//replace old wind with the provided wind
void ParticleSystem::updateWind(float newWind[3])
{
	for (int i = 0; i <= 2; i++)
	{
		if (newWind[i] > gMinWind && newWind[i] < gMaxWind)
			this->wind[i] = newWind[i];
	}
}

//set the type of particle to make
void ParticleSystem::setParticleType(int newType)
{
	if (newType >= 0 && newType <= 4)
		this->particleType = (_property)newType;
}

//get the max negative wind or max positive wind
float ParticleSystem::getWindBoundary(int direction)
{
	if (direction == 1)
		return this->gMaxWind;
	else if (direction == 0)
		return this->gMinWind;

	return 0;
}

//replace old cannon rotation with the new one
void ParticleSystem::setCannonRotation(float newRotation[3])
{
	for (int i = 0; i <= 2; i++)
	{
		if (newRotation[i] >= 0 && newRotation[i] < 360)
			this->cannonRotation[i] = newRotation[i];
		else
			this->cannonRotation[i] = 0;
	}
}

//retrieve the cannon rotation on a specific axis
float ParticleSystem::getCannonRotation(int axis)
{
	if (axis == 0)
		return this->cannonRotation[0];
	else if (axis == 1)
		return this->cannonRotation[1];
	else if (axis == 2)
		return this->cannonRotation[2];
	else
		return 0;
}