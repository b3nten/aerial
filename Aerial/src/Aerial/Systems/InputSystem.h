#pragma once
#include "../Core/Core.h"
#include "../ECS/System.h"

namespace Aerial::CoreSystems
{
	class InputSystem : public System
	{

	protected:
		void OnStart() override {}
		void OnUpdate() override;
		void OnEnd() override {}
	};
}

