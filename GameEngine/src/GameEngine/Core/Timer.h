#pragma once
#include <chrono>

namespace GE {

	class Timer {
	public:
		Timer() {
			Reset();
		}

		void Reset() {
			m_Begin = std::chrono::high_resolution_clock::now();
		}

		// ƒ…√Î
		float elapsed() const {
			return 0.001f * 0.001f * 0.001f * std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Begin).count();
		}

		// Œ¢√Î
		float elapsed_micro() const {
			return 1000.0f * elapsed();
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Begin;
	};
}