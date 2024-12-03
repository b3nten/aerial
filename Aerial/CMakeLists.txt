# Engine library CMake configuration
set(ENGINE_NAME Aerial)

add_library(${ENGINE_NAME} STATIC
        "src/Aerial/Core/Core.h"
        "src/Aerial/Core/Application.cpp"
        "src/Aerial/Core/Logger.h"
        "src/Aerial/Core/EntryPoint.h"
        "src/Aerial/Core/Profiler.h"
        "src/Aerial/Core/Timer.h"
        "src/Aerial/Core/UUID.h"
        "src/Aerial/Core/FrameDelta.h"

        "src/Aerial/ECS/Context.cpp"
        "src/Aerial/ECS/Entity.cpp"
        "src/Aerial/ECS/System.h"

        "src/Aerial/Systems/AssetSystem.cpp"
        "src/Aerial/Systems/AudioSystem.cpp"
        "src/Aerial/Systems/RenderSystem.cpp"
        "src/Aerial/Systems/EventSystem.cpp"
        "src/Aerial/Systems/InputSystem.cpp"

        "src/Aerial.h"
)

#sdl3
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
target_link_libraries(Aerial PUBLIC SDL3::SDL3-static)

#tracy
add_subdirectory(external/tracy EXCLUDE_FROM_ALL)
target_link_libraries(${ENGINE_NAME} PRIVATE Tracy::TracyClient)

#glm
add_subdirectory(external/glm EXCLUDE_FROM_ALL)
target_link_libraries(${ENGINE_NAME} PRIVATE glm)

target_include_directories(${ENGINE_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/tracy/public
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
)

target_compile_definitions(${ENGINE_NAME}
        PRIVATE

        AERIAL_BUILD_DLL

        PUBLIC

        SDL_MAIN_USE_CALLBACKS

        $<$<PLATFORM_ID:Windows>:AERIAL_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Linux>:AERIAL_PLATFORM_LINUX>
        $<$<PLATFORM_ID:Darwin>:AERIAL_PLATFORM_MACOS>

        $<$<CONFIG:Debug>:
            AERIAL_DEBUG_MODE
            TRACY_ENABLE
        >
        $<$<CONFIG:Release>:
            AERIAL_RELEASE_MODE
        >
)