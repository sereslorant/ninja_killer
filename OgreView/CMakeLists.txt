
set(OGRE_VIEW_SRC OgreEntityRepository.cpp)

add_library(OgreView ${OGRE_VIEW_SRC})
target_link_libraries(OgreView ${OGRE_LIBRARIES})
