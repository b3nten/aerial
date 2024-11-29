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
		virtual void OnCreate() = 0;
		virtual void OnUpdate() = 0;
	};
}
