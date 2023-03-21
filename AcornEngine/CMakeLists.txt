
#Add includes
include_directories("./include")

# Add source
add_library(Core STATIC)
add_subdirectory("./src")

add_executable (${CMAKE_PROJECT_NAME})
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

#glfw target by package's camke
target_link_libraries(${CMAKE_PROJECT_NAME} glfw Core)
