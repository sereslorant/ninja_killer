#ifndef OGRE_CAMERA_VIEW_H
#define OGRE_CAMERA_VIEW_H

#include <GameLogic/IGameObserver.h>

#include <OGRE/OgreCamera.h>

class OgreCameraView : public ICameraObserver
{
private:
	Ogre::Camera &camera;
	
public:
	
	virtual void OnPositionChanged(float x,float y,float z) override
	{
		camera.setPosition(x,y,z);
	}
	
	virtual void OnLookAtChanged(float x,float y,float z) override
	{
		camera.lookAt(x,y,z);
	}
	
	OgreCameraView(Ogre::Camera &p_camera)
		:camera(p_camera)
	{}
	
	virtual ~OgreCameraView() override
	{}
};

#endif // OGRE_CAMERA_VIEW_H
