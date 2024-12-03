#!/bin/bash

BUILD_DIR="./.profiler"
EXECUTABLE="$BUILD_DIR/Release/tracy-profiler"

if [ -d "$BUILD_DIR" ]; then
    if [ -f "$EXECUTABLE" ]; then
        echo "Tracy build already exists, running executable..."
        "$EXECUTABLE"
        exit 0
    else
        echo "Build directory exists but executable not found. Rebuilding..."
    fi
else
    echo "Build directory not found. Starting fresh build..."
fi

# Configure CMake
cmake -B ./.profiler -S Aerial/external/Tracy/profiler -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build ./.profiler --config Release --parallel

if [ -f "$EXECUTABLE" ]; then
    echo "Build completed! Running executable..."
    "$EXECUTABLE"
else
    echo "Build completed but executable not found."
fi