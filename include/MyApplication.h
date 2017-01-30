#ifndef __Application_H_
#define __Application_H_

#include "Application.h"
#include "ParticleSystem.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class MyApplication : public Application
{
public:

	MyApplication();
	virtual ~MyApplication();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);

	void CreateRandomParticleSystem();
	void CreateFountainParticleSystem();

	void CreateSmokeParticleSystem();

	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	ParticleSystem m_oParticleSystem;
	

	//make classes for different types of emitters e.g. cone emitter, sphere emitter
};

#endif // __Application_H_