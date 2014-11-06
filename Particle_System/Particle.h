#ifndef __PARTICLE_H__
#define __PARTICLE_H__


class Particle{
	
private:
	static long numParticles;

	float position[3];
	float nextPosition[3];
	float direction[3];
	float speed;
	bool isMoving;
	float rotation[3];

	
	float color[3];
	float size;
	float lifeRemaining;
	enum _property {NORMAL, BOUNCE, FLOAT, EXPLOSION} particleType;

public:
	Particle(int particleType, float position[3], float direction[3], float speed, float size, float color[3]);
	void updateLife(); //this will update a particle's information (ie position and rotation)
	
	
	//getters
	float getLifeRemaining(void);
	float getPosition(int position);
	float getDirection(int direction);
	float getColor(int newColor);
	long getNumParticles(void);

	//setters
	void setPosition(float newPosition[3]);
	void setLifeRemaining(int newLifeRemaining);
	void decrementNumParticles(void);
};
#endif