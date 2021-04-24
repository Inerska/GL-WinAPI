cmake_minimum_required(VERSION 2.6)

project(WINGLAPI C)

file(GLOB_RECURSE SRC
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

file(GLOB_RECURSE HEAD
		${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${HEAD} ${SRC})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE opengl32)