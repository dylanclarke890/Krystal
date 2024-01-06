#pragma once

#include "Krystal/Core/TimeStep.h"
#include "Krystal/Renderer/OrthographicCamera.h"

namespace Krys
{
	struct ParticleProps
	{
		glm::vec3 Position;
		glm::vec2 Velocity, VelocityVariation;
		glm::vec4 ColorBegin, ColorEnd;
		float SizeBegin, SizeEnd, SizeVariation;
		float LifeTime = 1.0f;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem();

		void OnUpdate(TimeStep ts);
		void OnRender(OrthographicCamera& camera);

		void Emit(const ParticleProps& particleProps);
	private:
		struct Particle
		{
			glm::vec3 Position = glm::vec3(0.0f);
			glm::vec2 Velocity = glm::vec2(0.0f);
			glm::vec4 ColorBegin = glm::vec4(0.0f), ColorEnd = glm::vec4(0.0f);
			float Rotation = 0.0f;
			float SizeBegin = 0.0f, SizeEnd = 0.0f;

			float LifeTime = 1.0f;
			float LifeRemaining = 0.0f;

			bool Active = false;
		};
		std::vector<Particle> m_ParticlePool;
		uint32_t m_PoolIndex = 999;
	};
}
