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

		void Run();

		// todo: implement
		FrameDelta GetFrameDelta() const { return m_FrameDelta; }

	protected:
		bool m_Running = false;
		Context m_AppContext;
		FrameDelta m_FrameDelta;
	};

	Application* CreateApplication();
}
