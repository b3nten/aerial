#pragma once
#include "../ECS/System.h"

namespace Aerial::CoreSystems {

	class RenderSystem : public System
	{
	public:
		RenderSystem();
		~RenderSystem();
	protected:
		void OnStart() override;
		void OnUpdate() override;
		void OnEnd() override;
	};

}