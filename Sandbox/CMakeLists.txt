# Sandbox executable configuration
set(SANDBOX_NAME Sandbox)

# Collect source files
file(GLOB_RECURSE SANDBOX_SOURCES
        "src/*.cpp"
        "src/*.h"
)

# Create executable
add_executable(${SANDBOX_NAME}
        ${SANDBOX_SOURCES}
)

# Link with Aerial engine
target_link_libraries(${SANDBOX_NAME} PRIVATE Aerial)
target_link_libraries(Aerial PRIVATE SDL3::SDL3)

# Include directories
target_include_directories(${SANDBOX_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:Sandbox>
)