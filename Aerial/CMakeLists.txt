# Engine library CMake configuration
set(ENGINE_NAME Aerial)

# Collect source files
file(GLOB_RECURSE ENGINE_SOURCES
        "src/**/*.cpp"
        "src/**/*.h"
)

# Create library
add_library(${ENGINE_NAME} STATIC
        ${ENGINE_SOURCES}
)

# Add compile definitions
add_compile_definitions(
        $<$<PLATFORM_ID:Windows>:AERIAL_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Linux>:AERIAL_PLATFORM_LINUX>
        $<$<PLATFORM_ID:Darwin>:AERIAL_PLATFORM_MACOS>
)

# Add DLL export definition only when building the engine
target_compile_definitions(${ENGINE_NAME}
        PRIVATE
        AERIAL_BUILD_DLL
        PUBLIC
        AERIAL_ENABLE_LOGGING
)

target_include_directories(${ENGINE_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# GLM
include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${ENGINE_NAME} PUBLIC glm::glm)
