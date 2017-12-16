

set(PHYSICS_SRC	PhysWorld.cpp
				PhysBuilder/PhysBodyBuilder.cpp
				PhysBuilder/PhysCompositeBuilder.cpp
)

add_library(BulletWrapper ${PHYSICS_SRC})
add_dependencies(BulletWrapper bullet3)
target_link_libraries(BulletWrapper BulletDynamics BulletCollision LinearMath)
