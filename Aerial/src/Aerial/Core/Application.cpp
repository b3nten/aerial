#include "Application.h"

#include "Timer.h"

namespace Aerial
{
	Application::Application()
	{
		// add default systems here
	}

	void Application::Run()
	{
		ASSERT(!m_Running, "Application::Run should only be called once.");

		this->m_AppContext.Create();

		while (m_Running)
		{
			FrameDelta delta(0.016);
			this->m_AppContext.Update();
		}
	}
}
