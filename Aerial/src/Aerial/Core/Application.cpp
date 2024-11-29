#include "Application.h"

namespace Aerial
{
	Application::Application()
		: m_Running(true)
	{

	}

	void Application::Run() const
	{
		this->m_AppContext.Create();

		while (m_Running)
		{
			this->m_AppContext.Update();
		}
	}
}
