#pragma once
#include "../ECS/System.h"

namespace Aerial::CoreSystems {

	class RenderSystem : public System
	{

	protected:
		void OnStart() override;
		void OnUpdate() override;
	};

}