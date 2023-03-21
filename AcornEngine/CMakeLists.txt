
#Add includes
include_directories("./include")

# Add source
add_library(Core STATIC)
add_subdirectory(./src/Core)
add_subdirectory(./src/Entity)
add_subdirectory(./src/Events)
add_subdirectory(./src/Layers)
add_subdirectory(./src/Logs)

add_executable (${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

#glfw target by package's camke
target_link_libraries(${CMAKE_PROJECT_NAME} glfw Core)
