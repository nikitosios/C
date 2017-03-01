cmake_minimum_required (VERSION 2.8)
project (red_triangle)

find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)

include_directories (${GLEW_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set (SOURCE_FILES src/main.c src/shaders.c)
add_executable (red_triangle ${SOURCE_FILES})

target_link_libraries (red_triangle glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARIES}
	${OPENGL_LIBRARY})
