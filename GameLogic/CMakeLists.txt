
include_directories(./)

set(ENTITIES_SRC	Entities/VisibleObjects/Character.cpp
					)

set(PHYSICS_SRC		Physics/BulletWorldWrapper.cpp
					)

add_library(GameLogic ${ENTITIES_SRC} ${PHYSICS_SRC} GameLoop/GameFactory.cpp Utils/AngleUtils.cpp)
target_link_libraries(GameLogic lJSON ${BULLET_LIBRARIES})

