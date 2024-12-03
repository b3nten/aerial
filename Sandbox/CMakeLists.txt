# Sandbox executable configuration
set(SANDBOX_NAME Sandbox)

# Create executable
add_executable(${SANDBOX_NAME}
        "src/main.cpp"
)

# Link with Aerial engine
target_link_libraries(${SANDBOX_NAME} PRIVATE Aerial)

# Include directories
target_include_directories(${SANDBOX_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(WIN32)
    set_target_properties(${SANDBOX_NAME} PROPERTIES
            WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>
    )
endif()