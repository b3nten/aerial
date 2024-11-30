#pragma once

namespace Aerial {

	class FrameDelta
	{
	public:
		explicit FrameDelta(float time = 0.0f)
		{
			// clamp at 120fps if < 0
			if(time < 0.0f) m_Time = 0.008f;
			// clamp at 0.06 if > 0.06
			else if (time > 0.06f) m_Time = 0.06f;
			else m_Time = time;
		}
		explicit operator float() const { return m_Time; }
		explicit operator double() const { return static_cast<double>(m_Time); }
		[[nodiscard]] float GetSeconds() const { return m_Time; }
		[[nodiscard]] float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}