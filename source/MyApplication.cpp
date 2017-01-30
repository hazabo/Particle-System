#include "MyApplication.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <iostream>

#include "TextureManager.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

MyApplication::MyApplication()
{

}

MyApplication::~MyApplication()
{

}

bool MyApplication::onCreate(int a_argc, char* a_argv[])
{
	// initialise the Gizmos helper class
	Gizmos::create( 1000000, 1000000);

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.75f, 0.75f, 0.75f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	std::string choice;
	std::cout << "Enter 1 for random particle system" << std::endl;
	std::cout << "Enter 2 for fountain particle system" << std::endl;
	std::cout << "Enter 3 for smoke particle system" << std::endl;
	std::cin >> choice;

	

	if(choice=="1")
		CreateRandomParticleSystem();
	else if(choice=="2")
		CreateFountainParticleSystem();
	else if(choice=="3")
		CreateSmokeParticleSystem();

	return true;
}

void MyApplication::CreateRandomParticleSystem()
{
	//create the particles for the emitters
	Particle minParticle = Particle(1, glm::vec3(-1, 0, 0), glm::vec3(-1, -1, -1), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec4(0, 0, 0, 0), glm::vec4(-0.1, -0.1, -0.1, -0.1));
	Particle maxParticle = Particle(10, glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec4(1, 1, 1, 1), glm::vec4(0.1, 0.1, 0.1, 0.1));

	//create the array of emitters
	ParticleEmitter* emitterArray = new ParticleEmitter[8];
	emitterArray[0] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);
	emitterArray[1] = ParticleEmitter(glm::vec3(1, 0, 0), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);
	emitterArray[2] = ParticleEmitter(glm::vec3(-1, 0, 0), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);
	emitterArray[3] = ParticleEmitter(glm::vec3(0, 0, 1), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);
	emitterArray[4] = ParticleEmitter(glm::vec3(0, 0, -1), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);
	emitterArray[5] = ParticleEmitter(glm::vec3(0, 1, 0), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);
	emitterArray[6] = ParticleEmitter(glm::vec3(0, -1, 0), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);
	emitterArray[7] = ParticleEmitter(glm::vec3(0, 2, 0), glm::vec2(0.1f, 0.1f), 1000000, 40, 25, minParticle, maxParticle);

	//create the particle system
	m_oParticleSystem = ParticleSystem(emitterArray, 8);
}

void MyApplication::CreateFountainParticleSystem()
{
	//create square fountain
	//create the particles for the low fountain
	Particle minParticle1_1 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(0.66f, 1.47f, -0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle1_1 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(0.66f, 1.47f, 0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle minParticle1_2 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(-0.66f, 1.47f, -0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle1_2 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(-0.66f, 1.47f, 0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle minParticle1_3 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(-0.66f, 1.47f, 0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle1_3 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(0.66f, 1.47f, 0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle minParticle1_4 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(-0.66f, 1.47f, -0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle1_4 = Particle(3.f, glm::vec3(0, 0, 0), glm::vec3(0.66f, 1.47f, -0.66f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	//create the particles for the high fountain
	Particle minParticle2_1 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(0.5f, 1.96f, -0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle2_1 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(0.5f, 1.96f, 0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle minParticle2_2 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(-0.5f, 1.96f, -0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle2_2 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(-0.5f, 1.96f, 0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle minParticle2_3 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(-0.5f, 1.96f, 0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle2_3 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(0.5f, 1.96f, 0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle minParticle2_4 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(-0.5f, 1.96f, -0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));
	Particle maxParticle2_4 = Particle(4.f, glm::vec3(0, 0, 0), glm::vec3(0.5f, 1.96f, -0.5f), glm::vec3(0.f, -0.98f, 0.f), glm::vec4(0, 0, 1, 0.7), glm::vec4(0.f, 0.f, 0.f, 0.f));

	//create the array of emitters
	ParticleEmitter* emitterArray = new ParticleEmitter[8];
	//low emitters
	emitterArray[0] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle1_1, maxParticle1_1);
	emitterArray[1] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle1_2, maxParticle1_2);
	emitterArray[2] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle1_3, maxParticle1_3);
	emitterArray[3] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle1_4, maxParticle1_4);
	//high emitters
	emitterArray[4] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle2_1, maxParticle2_1);
	emitterArray[5] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle2_2, maxParticle2_2);
	emitterArray[6] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle2_3, maxParticle2_3);
	emitterArray[7] = ParticleEmitter(glm::vec3(0, 0, 0), glm::vec2(0.03f, 0.03f), 1000000, 20, 100, minParticle2_4, maxParticle2_4);

	//create the particle system
	m_oParticleSystem = ParticleSystem(emitterArray, 8);
	//update it so it is filled
	m_oParticleSystem.Update(4.f, glm::inverse(m_cameraMatrix));
}

void MyApplication::CreateSmokeParticleSystem()
{
	//create the particles for the emitters
	Particle minParticle = Particle(5, glm::vec3(0, 0, 0), glm::vec3(-0.2f, 1.f, -0.2f), glm::vec3(0.f, 0.f, 0.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.5f), glm::vec4(0.f, 0.f, 0.f, -0.3f));
	Particle maxParticle = Particle(5, glm::vec3(0, 0, 0), glm::vec3(0.2f, 1.f, 0.2f), glm::vec3(0.f, 0.f, 0.f), glm::vec4(0.15f, 0.15f, 0.15f, 1), glm::vec4(0.f, 0.f, 0.f, -0.4f));

	//create the array of emitters
	ParticleEmitter* emitterArray = new ParticleEmitter[8];
	emitterArray[0] = ParticleEmitter(glm::vec3(0.f, 0, 0.16f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);
	emitterArray[1] = ParticleEmitter(glm::vec3(0.1f, 0, 0.1f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);
	emitterArray[2] = ParticleEmitter(glm::vec3(0.16f, 0, 0.f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);
	emitterArray[3] = ParticleEmitter(glm::vec3(0.1f, 0, -0.1f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);
	emitterArray[4] = ParticleEmitter(glm::vec3(0.f, 0, -0.16f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);
	emitterArray[5] = ParticleEmitter(glm::vec3(-0.1f, 0, -0.1f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);
	emitterArray[6] = ParticleEmitter(glm::vec3(-0.16f, 0, 0.f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);
	emitterArray[7] = ParticleEmitter(glm::vec3(-0.1f, 0, 0.1f), glm::vec2(0.2f, 0.2f), 1000000, 20, 2, minParticle, maxParticle);

	//create the array of emitters
	m_oParticleSystem = ParticleSystem(emitterArray, 8);
	//update it so it is partially filled
	m_oParticleSystem.Update(0.2f, glm::inverse(m_cameraMatrix));
}

void MyApplication::onUpdate(float a_deltaTime)
{
	std::cout << "FPS: " << 1 / a_deltaTime  << std::endl;
	std::cout << "Particles: " << m_oParticleSystem.GetParticleCount() << std::endl;
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();

	m_oParticleSystem.Update(a_deltaTime, glm::inverse(m_cameraMatrix));

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void MyApplication::onDraw()
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void MyApplication::onDestroy()
{
	// clean up anything we created
	TextureManager::DestroyInstance();

	Gizmos::destroy();

	m_oParticleSystem.~ParticleSystem();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	MyApplication* app = new MyApplication();
	
	if (app->create("Test Project",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}