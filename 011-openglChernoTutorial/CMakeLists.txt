cmake_minimum_required(VERSION 3.30.3)
project(LOGL) # Learn opengl
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Grab latest git modules
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout modules")
        endif()
    endif()
endif()

# Check all modules
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/dependencies/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed.")
endif()

# Add subdirectories of libs containing CMakeLists.txt
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)

# Include directories for headers
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/glad/include
    PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/glfw/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} glad glfw)
