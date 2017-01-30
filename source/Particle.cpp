#include "Particle.h"

#include "Gizmos.h"
#include <random>
#include <chrono>

Particle::Particle()
{
	m_fLifeTime = -1;
	m_v3Position = glm::vec3(NULL, NULL, NULL);
	m_v3LinearVelocity = glm::vec3(NULL, NULL, NULL);
	m_v4Colour = glm::vec4(NULL, NULL, NULL, NULL);
	m_v4ColourChange = glm::vec4(NULL, NULL, NULL, NULL);
}

Particle::Particle(float a_fLifeTime, glm::vec3 a_v3Position, glm::vec3 a_v3LinearVelocity, glm::vec3 a_v3LinearAcceleration,
				   glm::vec4 a_v4Colour, glm::vec4 a_v4ColourChange)
{
	m_fLifeTime = a_fLifeTime;
	m_v3Position = a_v3Position;
	m_v3LinearVelocity = a_v3LinearVelocity;
	m_v3LinearAcceleration = a_v3LinearAcceleration;
	m_v4Colour = a_v4Colour;
	m_v4ColourChange = a_v4ColourChange;
}

Particle::Particle(float a_fLifeTime, glm::vec3 a_v3LinearVelocity, glm::vec3 a_v3LinearAcceleration,
				   glm::vec4 a_v4Colour, glm::vec4 a_v4ColourChange)
{
	m_fLifeTime = a_fLifeTime;
	m_v3LinearVelocity = a_v3LinearVelocity;
	m_v3LinearAcceleration = a_v3LinearAcceleration;
	m_v4Colour = a_v4Colour;
	m_v4ColourChange = a_v4ColourChange;
}

Particle::~Particle()
{
}

void Particle::Update(const float& a_fdeltaTime)
{
	m_fLifeTime -= a_fdeltaTime;
	
	//If there is no acceleration
	if (m_v3LinearAcceleration == glm::vec3(0, 0, 0))
	{
		m_v3Position += m_v3LinearVelocity * a_fdeltaTime;
	}
	//If there is acceleration
	else
	{
		//s=(u+0.5at)t
		m_v3Position += (m_v3LinearVelocity + 0.5f * m_v3LinearAcceleration * a_fdeltaTime) * a_fdeltaTime;
	}

	m_v3LinearVelocity += m_v3LinearAcceleration * a_fdeltaTime;

	m_v4Colour += m_v4ColourChange * a_fdeltaTime;
}

void Particle::Draw(const glm::vec3& topRight, const glm::vec3& topLeft, const glm::vec3& bottomRight, const glm::vec3& bottomLeft)
{
	//Add particle's position to the vertices passed 
	Gizmos::addTri(m_v3Position + bottomRight, m_v3Position + topRight, m_v3Position + topLeft, m_v4Colour);

	Gizmos::addTri(m_v3Position + bottomLeft, m_v3Position + bottomRight, m_v3Position + topLeft, m_v4Colour);
}

void Particle::AddPostion(const glm::vec3& a_v3Position)
{
	m_v3Position += a_v3Position;
}

void Particle::Kill()
{
	m_fLifeTime = -1;
}

bool Particle::IsAlive()
{
	return (m_fLifeTime>0);
}

Particle Particle::RandomParticle(const Particle& a_oParticle1, const Particle& a_oParticle2)
{
	Particle returnParticle = Particle();
	//Initialize generator using time and thread ID so that different threads do not have the same seed
	unsigned seed = (unsigned int)static_cast<int> (std::chrono::system_clock::now().time_since_epoch().count()) + std::hash<std::thread::id>()(std::this_thread::get_id());//(int)(std::this_thread::get_id().std::hash();
	std::mt19937 generator(seed);
	//distribustion between 0 and 1
	std::uniform_real_distribution<float> distribution(0, 1);
	//For each value in the particle where the range is x to y use x + difference between x and y * a random number between 0 and 1
	//For each value value if there is only 1 possible value do not randomise it
	
	if (a_oParticle1.m_v3Position != a_oParticle2.m_v3Position)
	{
		returnParticle.m_v3Position.x = a_oParticle1.m_v3Position.x + (a_oParticle2.m_v3Position.x - a_oParticle1.m_v3Position.x)* distribution(generator);
		returnParticle.m_v3Position.y = a_oParticle1.m_v3Position.y + (a_oParticle2.m_v3Position.y - a_oParticle1.m_v3Position.y)* distribution(generator);
		returnParticle.m_v3Position.z = a_oParticle1.m_v3Position.z + (a_oParticle2.m_v3Position.z - a_oParticle1.m_v3Position.z)* distribution(generator);
	}
	else
	{
		returnParticle.m_v3Position = a_oParticle1.m_v3Position;
	}

	if (a_oParticle1.m_fLifeTime!= a_oParticle2.m_fLifeTime)
	{
		returnParticle.m_fLifeTime = a_oParticle1.m_fLifeTime + (a_oParticle2.m_fLifeTime - a_oParticle1.m_fLifeTime)* distribution(generator);
	}
	else
	{
		returnParticle.m_fLifeTime = a_oParticle1.m_fLifeTime;
	}

	if (a_oParticle1.m_v3LinearVelocity != a_oParticle2.m_v3LinearVelocity)
	{
		returnParticle.m_v3LinearVelocity.x = a_oParticle1.m_v3LinearVelocity.x + (a_oParticle2.m_v3LinearVelocity.x - a_oParticle1.m_v3LinearVelocity.x)* distribution(generator);
		returnParticle.m_v3LinearVelocity.y = a_oParticle1.m_v3LinearVelocity.y + (a_oParticle2.m_v3LinearVelocity.y - a_oParticle1.m_v3LinearVelocity.y)* distribution(generator);
		returnParticle.m_v3LinearVelocity.z = a_oParticle1.m_v3LinearVelocity.z + (a_oParticle2.m_v3LinearVelocity.z - a_oParticle1.m_v3LinearVelocity.z)* distribution(generator);
	}
	else
	{
		returnParticle.m_v3LinearVelocity = a_oParticle1.m_v3LinearVelocity;
	}
	
	if (a_oParticle1.m_v3LinearAcceleration != a_oParticle2.m_v3LinearAcceleration)
	{
		returnParticle.m_v3LinearAcceleration.x = a_oParticle1.m_v3LinearAcceleration.x + (a_oParticle2.m_v3LinearAcceleration.x - a_oParticle1.m_v3LinearAcceleration.x)* distribution(generator);
		returnParticle.m_v3LinearAcceleration.y = a_oParticle1.m_v3LinearAcceleration.y + (a_oParticle2.m_v3LinearAcceleration.y - a_oParticle1.m_v3LinearAcceleration.y)* distribution(generator);
		returnParticle.m_v3LinearAcceleration.z = a_oParticle1.m_v3LinearAcceleration.z + (a_oParticle2.m_v3LinearAcceleration.z - a_oParticle1.m_v3LinearAcceleration.z)* distribution(generator);
	}
	else
	{
		returnParticle.m_v3LinearAcceleration = a_oParticle1.m_v3LinearAcceleration;
	}
	
	if (a_oParticle1.m_v4Colour != a_oParticle2.m_v4Colour)
	{
		returnParticle.m_v4Colour.x = a_oParticle1.m_v4Colour.x + (a_oParticle2.m_v4Colour.x - a_oParticle1.m_v4Colour.x)* distribution(generator);
		returnParticle.m_v4Colour.y = a_oParticle1.m_v4Colour.y + (a_oParticle2.m_v4Colour.y - a_oParticle1.m_v4Colour.y)* distribution(generator);
		returnParticle.m_v4Colour.z = a_oParticle1.m_v4Colour.z + (a_oParticle2.m_v4Colour.z - a_oParticle1.m_v4Colour.z)* distribution(generator);
		returnParticle.m_v4Colour.w = a_oParticle1.m_v4Colour.w + (a_oParticle2.m_v4Colour.w - a_oParticle1.m_v4Colour.w)* distribution(generator);
	}
	else
	{
		returnParticle.m_v4Colour = a_oParticle1.m_v4Colour;
	}

	if (a_oParticle1.m_v4ColourChange != a_oParticle2.m_v4ColourChange)
	{
		returnParticle.m_v4ColourChange.x = a_oParticle1.m_v4ColourChange.x + (a_oParticle2.m_v4ColourChange.x - a_oParticle1.m_v4ColourChange.x)* distribution(generator);
		returnParticle.m_v4ColourChange.y = a_oParticle1.m_v4ColourChange.y + (a_oParticle2.m_v4ColourChange.y - a_oParticle1.m_v4ColourChange.y)* distribution(generator);
		returnParticle.m_v4ColourChange.z = a_oParticle1.m_v4ColourChange.z + (a_oParticle2.m_v4ColourChange.z - a_oParticle1.m_v4ColourChange.z)* distribution(generator);
		returnParticle.m_v4ColourChange.w = a_oParticle1.m_v4ColourChange.w + (a_oParticle2.m_v4ColourChange.w - a_oParticle1.m_v4ColourChange.w)* distribution(generator);
	}
	else
	{
		returnParticle.m_v4ColourChange = a_oParticle1.m_v4ColourChange;
	}

	return returnParticle;
}
