cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake/)

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

set(BULLET_INCLUDE_DIRS bullet3-master/src/)

set(BULLET_LIBRARIES	BulletDynamics
						BulletCollision
						LinearMath
						)

include_directories(./ ${OIS_INCLUDE_DIRS} ${OGRE_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS})

file(COPY ${CMAKE_SOURCE_DIR}/plugins.cfg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Content DESTINATION ${CMAKE_BINARY_DIR})

add_executable(NinjaKiller OisController.cpp Main.cpp)
target_link_libraries(NinjaKiller OgreView ${OGRE_LIBRARIES} ${OIS_LIBRARIES} GameLogic)

add_subdirectory(GameLogic)
add_subdirectory(OgreView)

add_subdirectory(GameLogicTest)

set(BUILD_BULLET3 FALSE)

add_subdirectory(lJSON)
add_subdirectory(bullet3-master)
