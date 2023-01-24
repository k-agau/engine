# CMakeList.txt : CMake project for AcornEngine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (AcornEngine "AcornEngine.cpp" "AcornEngine.h" "Shader.cpp" "Shader.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AcornEngine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(AcornEngine glfw ${GLFW_LIBRARIES} myLib)

# TODO: Add tests and install targets if needed.
