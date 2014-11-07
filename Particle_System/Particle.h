#ifndef __PARTICLE_H__
#define __PARTICLE_H__


class Particle{
	
private:
	static long numParticles; //stores number of generated alive particles

	float position[3]; 
	float direction[3];
	float speed;
	float rotation[3];

	
	float color[3];
	float size;
	float lifeRemaining; // when this value reaches 0 the particle has timed out
	enum _property {NORMAL, BOUNCE, FLOAT, EXPLOSION} particleType;

public:
	Particle(int particleType, float position[3], float direction[3], float speed, float size, float color[3]);
	void updateLife(); //this will update a particle's information (ie position and rotation)
	
	
	//getters
	float getLifeRemaining(void); // get the time until timeout
	float getPosition(int position);
	float getDirection(int direction);
	float getColor(int newColor);
	long getNumParticles(void); //get the number of alive particles
	float getRotation(int axis);
	int getParticleType(void);

	//setters
	void setPosition(float newPosition[3]);
	void setRotation(float newRotation[3]);
	void setLifeRemaining(int newLifeRemaining); //set time to timeout
	void decrementNumParticles(void); //decrement the amount of alive particles
	void invertYDirection(void); //flip the Y direction
	void applyFriction(float friction);
	void applyGravity(float gravity);
	void setNumParticles(unsigned int amount);
};
#endif