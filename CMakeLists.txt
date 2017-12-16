cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake/)

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(bullet3	DOWNLOAD_COMMAND git clone --depth 1 https://github.com/bulletphysics/bullet3
							INSTALL_DIR ${PROJECT_BINARY_DIR}
							CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

include_directories(./ ${OIS_INCLUDE_DIRS} ${OGRE_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/include/bullet)
link_directories(${CMAKE_BINARY_DIR}/lib)

file(COPY ${CMAKE_SOURCE_DIR}/plugins.cfg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Content DESTINATION ${CMAKE_BINARY_DIR})

add_executable(NinjaKiller OisController.cpp Main.cpp)
target_link_libraries(NinjaKiller OgreView ${OGRE_LIBRARIES} ${OIS_LIBRARIES} GameLogic)

add_subdirectory(GameLogic)

add_subdirectory(Test)
add_subdirectory(lJSON)

add_subdirectory(OgreView)

