#include "ParticleSystem.h"

Particle* particle; //used to create new particles in the linked list


ParticleSystem::ParticleSystem(float position[3], float gravity, float wind[3])
{
	
	this->gravity = gravity;

	for (int i = 0; i <= 2; i++)
		this->position[i] = position[i];
	


	iterator0 = NULL;
	iterator1 = NULL;
	iterator2 = NULL;
	
	tail = iterator1;

	for (int i = 0; i < 1; i++)
	{
		spawnParticle();
		if (i == 0)
			head = iterator1;
	}
	
}

void ParticleSystem::spawnParticle(void)
{
	
	glLoadIdentity();
	if (iteratorA != NULL)
		cout << "Num particles: " << iteratorA->element->getNumParticles() << "\n";
	float newColor[3] = { (float)(rand() / (float)(RAND_MAX + 1)), 
		(float)(rand() / (float)(RAND_MAX + 1)), 
		(float)(rand() / (float)(RAND_MAX + 1)) };
	

	float direction[3] = { 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f,
		getGravity(),
		2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f };
	
	//cout << "New Position x: " << direction[0] << " y: " << direction[1] << "z: " << direction[2] << endl;
	cout << this->position[0] << " " << this->position[1] << " " << this->position[2];

	particle = new Particle(0, this->position, direction, 1, 1, newColor);
	

	iterator2 = new ParticleList;
	if (iterator1 != NULL)
		iterator1->next = iterator2;

	iterator2->element = particle;
	
	iterator2->prev = iterator1;
	iterator2->next = NULL;

	iterator1 = iterator2;
	
	tail = iterator1;

}

void ParticleSystem::drawParticles(void)
{
	iteratorA = head;
	/*cout << endl << "before translatef: " << iteratorA->element->getPosition(0) << " " <<
		iteratorA->element->getPosition(1) << " " <<
		iteratorA->element->getPosition(2);*/
	
	while (iteratorA->next != NULL)
	{
		
		glPushMatrix();
		glColor3f(iteratorA->element->getColor(0), 
			iteratorA->element->getColor(1), 
			iteratorA->element->getColor(2));
		
		glTranslatef(iteratorA->element->getPosition(0),
						iteratorA->element->getPosition(1),
						iteratorA->element->getPosition(2));
		glutSolidCube(0.2);
		glPopMatrix();

		iteratorA = iteratorA->next;
	}
}

void ParticleSystem::updateParticles(void)
{
	iteratorA = head;
	/*cout << endl << iteratorD->element->getPosition(0) << " " <<
	iteratorD->element->getPosition(1) << " " <<
	iteratorD->element->getPosition(2);*/
	float newPosition[3];
	//add safety check

	//This initializes the newPosition values to the old position
	for (int i = 0; i <= 2; i++)
	{
		newPosition[i] = iteratorA->element->getPosition(i);
		
	}
	//cout << "\nposition of new: " << iteratorA->element->getPosition(1) << "\n";
	//Add a switch to go through all particle types (that will determine how to calculate next position)
	float amount = (float)1/ (rand() % 5 + 10);
	//cout << "Amount is " << amount;
	

	while (iteratorA->next != NULL)
	{
		for (int i = 0; i <= 2; i++)
			newPosition[i] += iteratorA->element->getDirection(i);

		//cout << "New Position x: " << newPosition[0] << " y: " << newPosition[1] << "z: " << newPosition[2] << endl;
		iteratorA->element->setPosition(newPosition);

		/*cout << endl << iteratorA->element->getPosition(0) << " " <<
		iteratorA->element->getPosition(1) << " " <<
		iteratorA->element->getPosition(2);*/

		iteratorA = iteratorA->next;
	}
}

/* Get Gravity */
/* Depending on the mode, this may be calculated differently*/
float ParticleSystem::getGravity()
{
	return this->gravity;
}