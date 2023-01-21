add_subdirectory("GLFW")
add_subdirectory("GLAD")

target_include_directories(AcornEngine PUBLIC "GLAD/include/glad")
target_sources(myLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GLAD/src/glad.c")

#target_include_directories(AcornEngine PUBLIC "GLFW/include")