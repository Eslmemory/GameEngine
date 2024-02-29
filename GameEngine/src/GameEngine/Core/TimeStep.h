#pragma once
#include "gepch.h"
#include "GameEngine/Core/Core.h"

namespace GE {
	class GE_API TimeStep {
	public:
		TimeStep(float time)
			: m_Time(time) {}
		~TimeStep() {}

		float GetSeconds() { return m_Time; }
		float GetMilliseconds() { return 1000 * m_Time; }
		operator float() { return m_Time; }

	private:
		float m_Time;
	};
}