# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("AcornEngine")

# Include sub-projects.
add_compile_definitions(GLEW_STATIC)
add_subdirectory ("AcornEngine")
add_library(myLib "")
add_subdirectory("lib")

