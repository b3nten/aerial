#pragma once
#include "./Core.h"
#include "../ECS/Context.h"

namespace Aerial
{
	class AERIAL_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run() const;

	protected:
		bool m_Running = false;
		Context m_AppContext;
	};

	Application* CreateApplication();
}
