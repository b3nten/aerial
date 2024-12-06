#pragma once

#if AERIAL_DEBUG_MODE
#include <Tracy/Tracy.hpp>
#endif

#if AERIAL_DEBUG_MODE
#define AERIAL_PROFILE_FUNC ZoneScoped
#define AERIAL_PROFILE_SCOPE(name) ZoneScopedN(name)
#define AERIAL_PROFILE_FRAME FrameMark
#else
#define AERIAL_PROFILE_FUNC
#define AERIAL_PROFILE_SCOPE
#define AERIAL_PROFILE_FRAME
#endif