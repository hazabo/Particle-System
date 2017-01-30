#pragma once

#include <glm/ext.hpp>

#ifndef __PARTICLE_H__
#define __PARTICLE_H__


class Particle
{
private:
	float m_fLifeTime;
	glm::vec3 m_v3Position;
	glm::vec3 m_v3LinearVelocity;
	glm::vec3 m_v3LinearAcceleration;
	glm::vec4 m_v4Colour;
	glm::vec4 m_v4ColourChange;
	//texture
public:
	//Default constructor will initialize a particle with lifetime set to -1 and null for everything else
	Particle();

	//constructor with position
	Particle(float a_fLifeTime, glm::vec3 a_v3Position, glm::vec3 a_v3LinearVelocity, glm::vec3 a_v3LinearAcceleration,
			 glm::vec4 a_v4Colour, glm::vec4 a_v4ColourChange);

	//constructor without position
	Particle(float a_fLifeTime, glm::vec3 a_v3LinearVelocity, glm::vec3 a_v3LinearAcceleration,
		glm::vec4 a_v4Colour, glm::vec4 a_v4ColourChange);

	~Particle();

	void Update(const float& deltaTime);
	//Takes in the points of a triangle with centre at 0,0, draws a triangle at it's position
	void Draw(const glm::vec3& topRight, const glm::vec3& topLeft, const glm::vec3& bottomRight, const glm::vec3& bottomLeft);
	//Sets position, used to move particle to emitters location
	void AddPostion(const glm::vec3& a_v3Position);
	//Sets lifetime to -1 making it not alive
	void Kill();
	//Returns true if lifetime > 0 
	bool IsAlive();
	//Returns a particle with properties randomized between 2 particles
	static Particle RandomParticle(const Particle& a_oParticle1, const Particle& a_oParticle2);
};



#endif // !__PARTICLE_H__