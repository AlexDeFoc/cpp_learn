#!/bin/bash

# Src paths
include="src/include"
lib="src/lib"
bin="bin/"
exe="$bin/main.exe"

# Third-party libs
LIB_GLFW="glfw3dll"

# Third-party dlls
DLL_GLFW="src/glfw3.dll"

# Source files
main="src/main.cpp"
sources=($main)

# Create bin directory if it doesn't exist
mkdir -p $bin

# Compile & link command (compiling all source files into one executable)
clang++ -o $exe "${sources[@]}" -L $lib -l$LIB_GLFW -I $include

# Create compile_commands.json for clangd
cat <<EOL > compile_commands.json
[
    {
        "directory": "$(pwd)",
        "command": "clang++ -o $exe ${sources[*]} -L $lib -l$LIB_GLFW -I $include",
        "file": "$main"
    }
]
EOL

# Copy dlls to exe dir
cp $DLL_GLFW $bin
