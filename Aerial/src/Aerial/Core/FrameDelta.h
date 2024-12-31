#pragma once

namespace aerial {

	class FrameDelta {
	public:
		explicit FrameDelta(float time = 0.0f)
		{
			// clamp at 120fps if < 0
			if(time < 0.0f) m_time = 0.008f;
			// clamp at 0.06 if > 0.06
			else if (time > 0.06f) m_time = 0.06f;
			else m_time = time;
		}
		explicit operator float() const { return m_time; }
		explicit operator double() const { return static_cast<double>(m_time); }
		[[nodiscard]] float get_sec() const { return m_time; }
		[[nodiscard]] float get_ms() const { return m_time * 1000.0f; }
	private:
		float m_time;
	};

}