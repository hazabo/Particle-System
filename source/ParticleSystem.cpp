#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::ParticleSystem(ParticleEmitter * a_aoEmitterArray, int a_iEmitterArraySize)
{
	m_aoEmitterArray = a_aoEmitterArray;
	m_iEmitterArraySize = a_iEmitterArraySize;
	//one of emitters is handled by the main thread so 1 less thread is needed
	m_aoThreadsArray = new std::thread[m_iEmitterArraySize-1];
}

ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < m_iEmitterArraySize; i++)
	{
		m_aoEmitterArray[i].~ParticleEmitter();
	}
}

void ParticleSystem::Update(const float& a_fDeltaTime, const glm::mat4& a_cameraMatrix)
{
	//for each emitter except the first one which will be handled by this thread start a thread calling update on that emitter
	for (int i = 0; i < m_iEmitterArraySize-1; i++)
	{
		//use emitter array[i+1] as first is done in main
		m_aoThreadsArray[i] = std::thread(&ParticleEmitter::Update, &m_aoEmitterArray[i+1], a_fDeltaTime);
	}
	//this thread does something while it waits for the others
	m_aoEmitterArray[0].Update(a_fDeltaTime);
	//wait for the other threads to finish
	for (int i = 0; i < m_iEmitterArraySize-1; i++)
	{
		m_aoThreadsArray[i].join();
	}

	Draw(a_cameraMatrix);
}

void ParticleSystem::Draw(const glm::mat4& a_cameraMatrix)
{
	//Added mutex locking to AddTriangle to allow multi threading of this

	//for each emitter except the first one which will be handled by this thread start a thread calling update on that emitter
	for (int i = 0; i < m_iEmitterArraySize-1; i++)
	{
		//use emitter array[i+1] as first is done in main
		m_aoThreadsArray[i] = std::thread(&ParticleEmitter::Draw, &m_aoEmitterArray[i+1], a_cameraMatrix);
	}
	//this thread does something while it waits for the others
	m_aoEmitterArray[0].Draw(a_cameraMatrix);
	//wait for the other threads to finish
	for (int i = 0; i < m_iEmitterArraySize-1; i++)
	{
		m_aoThreadsArray[i].join();
	}
}

int ParticleSystem::GetParticleCount()
{
	int totalParticles = 0;
	for (int i = 0; i < m_iEmitterArraySize; i++)
	{
		totalParticles += m_aoEmitterArray[i].GetParticleCount();
	}
	return totalParticles;
}