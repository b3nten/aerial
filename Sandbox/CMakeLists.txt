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

# Include directories
target_include_directories(${SANDBOX_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)