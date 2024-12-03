#pragma once
#define FMT_HEADER_ONLY
// ReSharper disable once CppUnusedIncludeDirective
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <SDL3/SDL_log.h>
#include <print>

namespace Aerial
{
	class Logger
	{
	public:
		template<typename... Args>
		static void Warn(fmt::format_string<Args...> fmt, Args&&... args)
		{
			std::println("Warning: {}", fmt::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void Error(fmt::format_string<Args...> fmt, Args&&... args)
		{
			std::println("Error: {}", fmt::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void Info(fmt::format_string<Args...> fmt, Args&&... args)
		{
			std::println("Info: {}", fmt::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void Debug(fmt::format_string<Args...> fmt, Args&&... args)
		{
			std::println("Debug: {}", fmt::format(fmt, std::forward<Args>(args)...));
		}

		static void Debug(const char* str)
		{
			std::println("Debug: {}", str);
		}

		template<typename... Args>
		static void Fatal(fmt::format_string<Args...> fmt, Args&&... args)
		{
			std::println("Fatal: {}", fmt::format(fmt, std::forward<Args>(args)...));
		}
	};
}

#ifdef AERIAL_DEBUG_MODE
#define AERIAL_LOG_WARN(...) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define AERIAL_LOG_ERROR(...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define AERIAL_LOG_INFO(...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define AERIAL_LOG_DEBUG(...) SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define AERIAL_LOG_FATAL(...) SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#else
#define AERIAL_LOG_WARN(...)
#define AERIAL_LOG_ERROR(...)
#define AERIAL_LOG_INFO(...)
#define AERIAL_LOG_DEBUG(...)
#define AERIAL_LOG_FATAL(...)
#endif