#pragma once

#include"ParticleEmitter.h"
#include <thread>

#ifndef __PARTICLE_SYSTEM_H__
#define __PARTICLE_SYSTEM_H__

class ParticleSystem
{
private:
	ParticleEmitter* m_aoEmitterArray;
	std::thread* m_aoThreadsArray;
	int m_iEmitterArraySize;

	void Draw(const glm::mat4& a_cameraMatrix);
public:
	ParticleSystem();
	ParticleSystem(ParticleEmitter* a_aoEmitterArray ,int a_iEmitterArraySize);
	~ParticleSystem();

	//update also handles drawing
	void Update(const float& a_fDeltaTime, const glm::mat4& a_cameraMatrix);
	
	int GetParticleCount();

};

#endif // !__PARTICLE_SYSTEM_H__