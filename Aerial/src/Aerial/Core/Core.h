#pragma once
#include <memory>
#include "./Logger.h"
#include "./Profiler.h"

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
	using Box = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr Box<T> CreateBox(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename ... Ts>                                                 // (7)
	struct Overload : Ts ... {
		using Ts::operator() ...;
	};

}


#define AERIAL_ASSERT(x, ...) if (!(x)) { AERIAL_LOG_ERROR(__VA_ARGS__); __debugbreak(); }
#define BIT(x) (1 << x)

// // API export/import macro
// #ifdef AERIAL_PLATFORM_WINDOWS
// #ifdef AERIAL_BUILD_DLL
// #define AERIAL_API __declspec(dllexport)
// #else
// #define AERIAL_API __declspec(dllimport)
// #endif
// #else
// #define AERIAL_API  // Empty on other platforms
// #endif

#define AERIAL_API

namespace Aerial::NumberExtensions
{
	constexpr std::size_t operator""_KiB(unsigned long long int x) {
		return 1024ULL * x;
	}

	constexpr std::size_t operator""_MiB(unsigned long long int x) {
		return 1024_KiB * x;
	}

	constexpr std::size_t operator""_GiB(unsigned long long int x) {
		return 1024_MiB * x;
	}

	constexpr std::size_t operator""_TiB(unsigned long long int x) {
		return 1024_GiB * x;
	}

	constexpr std::size_t operator""_PiB(unsigned long long int x) {
		return 1024_TiB * x;
	}
}

