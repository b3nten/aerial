#pragma once

#include <chrono>

namespace aerial {

	class timer
	{
	public:
		timer() { reset(); }

		void reset()
		{
			m_start = std::chrono::high_resolution_clock::now();
		}

		float elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_start).count() * 0.001f * 0.001f * 0.001f;
		}

		float elapsed_ms()
		{
			return elapsed() * 1000.0f;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	};

}