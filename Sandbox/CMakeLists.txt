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

if(WIN32)
    add_custom_command(TARGET ${SANDBOX_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:${SANDBOX_NAME}>
    )
endif()