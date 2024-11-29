#pragma once
#include <memory>
#include "./Logger.h"

namespace Aerial
{
	template<typename T>
	using Arc = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Arc<T> CreateArc(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
}

// API export/import macro
#ifdef AERIAL_PLATFORM_WINDOWS
#ifdef AERIAL_BUILD_DLL
#define AERIAL_API __declspec(dllexport)
#else
#define AERIAL_API __declspec(dllimport)
#endif
#else
#define AERIAL_API  // Empty on other platforms
#endif
