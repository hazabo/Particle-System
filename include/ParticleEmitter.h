#pragma once

#include <glm/ext.hpp>
#include "Particle.h"

#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

class ParticleEmitter
{
private:
	glm::vec3 m_v3Position;
	glm::vec2 m_v2ParticlesSize;
	int m_iMaxParticles;
	float m_fEmitsPerSecond; //Number of emits per second
	int m_iParticlesPerEmit; //Number of particles per emit
	Particle m_oMinParticleProperties; //Particle with minimum wanted values
	Particle m_oMaxParticleProperties; //Particle with maximum wanted values

	float m_fEmitFrequency; //Time between emits
	Particle* m_aoParticles; //Particles array
	float m_fTimePassed = 0.0f; //Holds Time since last article emit
	int m_iNumAliveParticles = 0; //The number of alive particles

	//make it so update is called on new particles passing the excess time passed

public:
	//default constructor 
	ParticleEmitter();
	//constructor for an emitter that spawns particles with properties between 2 values
	ParticleEmitter(glm::vec3 a_v3Position, glm::vec2 a_v2ParticlesSize, int a_iMaxParticles,
					float a_fEmitRatePerSecond, int a_fParticlesPerEmit, 
					const Particle& a_oMinParticleProperties, const Particle& a_oMaxParticleProperties);
	//constructor for an emitter that spawns a set particle
	ParticleEmitter(glm::vec3 a_v3Position, glm::vec2 a_v2ParticlesSize, int a_iMaxParticles,
					float a_fEmitRatePerSecond, int a_fParticlesPerEmit,
					const Particle& a_oParticleProperties);
	~ParticleEmitter();

	void Update(const float& a_fDeltaTime);
	//Draws all Particles which are alive
	void Draw(const glm::mat4& a_cameraMatrix);
	int GetParticleCount();
};



#endif // !__PARTICLE_EMITTER_H__