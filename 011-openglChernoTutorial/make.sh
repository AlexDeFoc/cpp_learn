#!/bin/bash

# Macros
glew_macro="GLEW_STATIC"

# Headers
headers="./dependencies/headers/"

# Libraries
glfw="./dependencies/libraries/GLFW/glfw3dll.lib"
glfw_dll="./dependencies/libraries/GLFW/glfw3.dll"

# Sources
main="./src/main.cpp"
glad="./src/glad.c"

# Cleanup and make bin dir
rm -rf "./bin/"
mkdir "./bin/"

# Copy dll to bin
cp "$glfw_dll" "./bin/"

# Compile
clang++ -o "./bin/main.exe" $main $glad -I "$headers" "$glfw" -Wno-deprecated
