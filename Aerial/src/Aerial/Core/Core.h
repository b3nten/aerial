#pragma once
#include <memory>
#include <SDL3/SDL_log.h>
#include "./logger.h"
#include "./Profiler.h"

namespace aerial
{
	template<typename T>
	using arc = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr arc<T> make_arc(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using box = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr box<T> make_box(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename ... Ts>                                                 // (7)
	struct overload : Ts ... {
		using Ts::operator() ...;
	};

	typedef uint8_t   u8;
	typedef char16_t  c16;
	typedef int32_t   b32;
	typedef int32_t   i32;
	typedef uint32_t  u32;
	typedef uint64_t  u64;
	typedef float     f32;
	typedef double    f64;
	typedef uintptr_t uptr;
	typedef ptrdiff_t size;
	typedef size_t    usize;
	typedef std::byte byte;
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

namespace Ae = aerial;
namespace ae = aerial;
namespace Aerial = aerial;

#define AERIAL_API

namespace aerial::number_ext
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

