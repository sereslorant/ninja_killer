
include_directories(./)

set(ENTITIES_SRC		Entities/VisibleObjects/Character.cpp
					)

set(ENTITY_LOADER_SRC	GameLoop/EntityManager/BulletLoader/BulletLoaderUtil.cpp
					)

add_library(GameLogic ${ENTITIES_SRC} ${ENTITY_LOADER_SRC} GameLoop/GameFactory.cpp Utils/AngleUtils.cpp)
add_dependencies(GameLogic bullet3)
target_link_libraries(GameLogic lJSON BulletWrapper BulletDynamics BulletCollision LinearMath)

add_subdirectory(Physics)
