#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
{
}

ParticleEmitter::ParticleEmitter(glm::vec3 a_v3Position, glm::vec2 a_v2ParticlesSize, int a_iMaxParticles, float a_fEmitsPerSecond, int a_iParticlesPerEmit, const Particle& a_oMinParticleProperties, const Particle& a_oMaxParticleProperties)
{
	m_v3Position = a_v3Position;
	m_v2ParticlesSize = a_v2ParticlesSize;
	m_iMaxParticles = a_iMaxParticles;
	m_fEmitsPerSecond = a_fEmitsPerSecond;
	m_iParticlesPerEmit =a_iParticlesPerEmit;
	m_oMinParticleProperties = a_oMinParticleProperties;
	m_oMaxParticleProperties = a_oMaxParticleProperties;
	//Make the particles position relative to the emitters position
	m_oMinParticleProperties.AddPostion(m_v3Position);
	m_oMaxParticleProperties.AddPostion(m_v3Position);

	//EmitsPerSecond is easier to understand but need frequency for code
	m_fEmitFrequency = 1 / m_fEmitsPerSecond;
	//sets all particles in the array to null 
	m_aoParticles = new Particle[m_iMaxParticles]{Particle()};
}

ParticleEmitter::ParticleEmitter(glm::vec3 a_v3Position, glm::vec2 a_v2ParticlesSize, int a_iMaxParticles, float a_fEmitsPerSecond, int a_iParticlesPerEmit, const Particle& a_oParticleProperties)
{
	m_v3Position = a_v3Position;
	m_v2ParticlesSize = a_v2ParticlesSize;
	m_iMaxParticles = a_iMaxParticles;
	m_fEmitsPerSecond = a_fEmitsPerSecond;
	m_iParticlesPerEmit =a_iParticlesPerEmit;
	m_oMinParticleProperties = a_oParticleProperties;
	m_oMaxParticleProperties = Particle();
	//Make the particles position relative to the emitters position
	m_oMinParticleProperties.AddPostion(m_v3Position);

	//EmitsPerSecond is easier to understand but need frequency for code
	m_fEmitFrequency = 1 / m_fEmitsPerSecond;
	//sets all particles in the array to null 
	m_aoParticles = new Particle[m_iMaxParticles];
}

ParticleEmitter::~ParticleEmitter()
{
	//destroy all particles in the emitter
	for (int i = 0; i < m_iMaxParticles; i++)
	{
		m_aoParticles[i].~Particle();
	}
	m_oMaxParticleProperties.~Particle();
	m_oMinParticleProperties.~Particle();
}

void ParticleEmitter::Update(const float& a_fDeltaTime )
{
	//update all the particles in particles array
	for (int i = 0; i<m_iNumAliveParticles; i++)
	{

		//if particle is alive update it
		//else move the last particle in the array to it's position

		if (m_aoParticles[i].IsAlive())
		{
			m_aoParticles[i].Update(a_fDeltaTime);
		}
		else
		{
			//delete then move last alive particle to deleted's position, ++i
			m_aoParticles[i] = m_aoParticles[m_iNumAliveParticles - 1];
			//particle moved still needs to be evaluated so decrease i
			i--;
			m_iNumAliveParticles--;
		}
	}

	m_fTimePassed += a_fDeltaTime;
	//using a while loop and passing excess time to update makes emitter work as expected and barely 
	//affects frame rate previously time passed would go above emit frequency and just spawn every frame
	while (m_fTimePassed>m_fEmitFrequency)
	{
		m_fTimePassed -= m_fEmitFrequency;

		//spawn particle(s)

		for (int i = 0; i < m_iParticlesPerEmit; i++)
		{
			Particle particleToEmit;
			//get particle
			if (!m_oMaxParticleProperties.IsAlive())
			{
				//not a random particle
				particleToEmit = m_oMinParticleProperties;
			}
			else
			{
				//a random particle
				particleToEmit = Particle::RandomParticle(m_oMinParticleProperties, m_oMaxParticleProperties);
			}
			
			//pass the excess delta time to update the particle 
			particleToEmit.Update(m_fTimePassed);
			//emit the particle
			m_aoParticles[m_iNumAliveParticles] = particleToEmit;
			m_iNumAliveParticles++;
		}		
	}
}

void ParticleEmitter::Draw(const glm::mat4& a_cameraMatrix)
{
	glm::mat4 scale = glm::mat4(m_v2ParticlesSize.x, 0, 0, 0, 0, m_v2ParticlesSize.y, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)  * a_cameraMatrix;

	glm::vec3 topRight = (glm::vec4(0.5f, 0.5f, 0.f, 0.f) * scale).xyz;
	glm::vec3 topLeft = (glm::vec4(-0.5f, 0.5f, 0, 0.f) * scale).xyz;
	glm::vec3 bottomRight = (glm::vec4(0.5f, -0.5f, 0, 0.f) * scale).xyz;
	glm::vec3 bottomLeft = (glm::vec4(-0.5f, -0.5f, 0, 0.f) * scale).xyz;
	for (int i=0; i<m_iNumAliveParticles;i++)
	{
		m_aoParticles[i].Draw(topRight, topLeft, bottomRight, bottomLeft);
	}
}

int ParticleEmitter::GetParticleCount()
{
	return m_iNumAliveParticles;
}
