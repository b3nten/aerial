#pragma once
#include "../Core/Core.h"
#include "./System.h"

namespace Aerial
{
	class AERIAL_API System
	{
		friend class Context;
	public:
		System() = default;
		virtual ~System() = default;

	protected:
		virtual void OnStart(){}
		virtual void OnUpdate(){}
		virtual void OnEnd(){}
		Context* m_Context;

	private:
		bool m_HasRunOnStart = false;
	};
}
