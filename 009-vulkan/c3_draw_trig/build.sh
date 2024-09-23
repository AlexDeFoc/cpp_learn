#!/bin/bash

# Paths
bin="bin/"
exe="$bin/main.exe"

# CXX Version
version="-std=c++17"

# Third-party headers
H_glm="C:/App/Libraries"
H_glfw="C:/App/Libraries/glfw/include"
H_vulkan="C:/App/Libraries/VulkanSDK/1.3.290.0/Include"

# Third-party libs
L_glfw="C:/App/Libraries/glfw/lib-static-ucrt"
l_glfw="glfw3dll"

L_vulkan="C:/App/Libraries/VulkanSDK/1.3.290.0/Lib"
l_vulkan="vulkan-1"

# Source files
main="src/main.cpp"

# Create bin directory if it doesn't exist
mkdir -p $bin

# Define macros
mode="" # Default to debug mode (no NDEBUG)

# Check if "release" is passed as an argument to trigger release mode
if [ "$1" == "release" ]; then
    mode="NDEBUG"
fi

# Compile & link command
if [ -n "$mode" ]; then
    clang++ -o $exe $main -I $H_glm -I $H_glfw -I $H_vulkan -L $L_glfw -l $l_glfw -L $L_vulkan -l $l_vulkan $version -D $mode
else
    clang++ -o $exe $main -I $H_glm -I $H_glfw -I $H_vulkan -L $L_glfw -l $l_glfw -L $L_vulkan -l $l_vulkan $version
fi
