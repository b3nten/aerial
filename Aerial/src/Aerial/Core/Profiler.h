#pragma once

#if AERIAL_DEBUG_MODE && TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

#if AERIAL_DEBUG_MODE && TRACY_ENABLE
#define AERIAL_PROFILE_FUNC ZoneScoped
#define AERIAL_PROFILE_SCOPE(name) ZoneScopedN(name)
#define AERIAL_PROFILE_FRAME FrameMark
#else
#define AERIAL_PROFILE
#define AERIAL_PROFILE(name)
#define AERIAL_PROFILE_FRAME
#endif