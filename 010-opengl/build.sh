#!/bin/bash

# Dependencies
headers="./dependencies/include/"

libraries_array=(
    "./dependencies/lib/GLFW/glfw3dll.lib"
    "./dependencies/src/glad.c"
)

libraries_dll_array=(
    "./dependencies/lib/GLFW/glfw3.dll"
)

shaders_array=(
    "./src/shaders/vertex.txt"
    "./src/shaders/fragment.txt"
)

libraries="${libraries_array[@]}"

# Copy dynamic libraries (DLLs)
for dll in ${libraries_dll_array[@]}; do
    cp "$dll" "./bin/"
done

# Make dir for shaders
mkdir "./bin/shaders"

# Copy shaders files
for file in ${shaders_array[@]}; do
    cp "$file" "./bin/shaders/"
done

# Compile & Link with suppressed warning
clang++ -o "./bin/main.exe" "./src/main.cpp" -I "$headers" $libraries -Wno-deprecated
