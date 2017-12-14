#ifndef IGAME_OBSERVER_H
#define IGAME_OBSERVER_H

#include <string>

class IVisibleObserver
{
public:
	
	virtual void OnLabelChanged(const std::string &name) = 0;
	
	virtual void OnPositionChanged(float x,float y,float z) = 0;
	virtual void OnOrientationChanged(float w,float x,float y,float z) = 0;
	
	IVisibleObserver()
	{}
	virtual ~IVisibleObserver()
	{}
};

class ICharacterObserver : public IVisibleObserver
{
public:
	virtual void OnStanding() = 0;
	virtual void OnMoving() = 0;
	
	virtual void OnAiming() = 0;
	virtual void OnAimReleased() = 0;
	
	virtual void OnMelee() = 0;
	virtual void OnMeleeReleased() = 0;
	
	virtual void OnShooting() = 0;
	virtual void OnShootingReleased() = 0;
	
	virtual void OnDying() = 0;
	
	ICharacterObserver()
	{}
	virtual ~ICharacterObserver()
	{}
};

class ICameraObserver
{
public:
	virtual void OnPositionChanged(float x,float y,float z) = 0;
	virtual void OnLookAtChanged(float x,float y,float z) = 0;
	
	ICameraObserver()
	{}
	virtual ~ICameraObserver()
	{}
};

class IEntityObserverFactory
{
public:
	
	virtual ICameraObserver *CreateCameraObserver() = 0;
	virtual IVisibleObserver *CreateEntityObserver() = 0;
	virtual ICharacterObserver *CreateCharacterObserver() = 0;
	
	IEntityObserverFactory()
	{}
	virtual ~IEntityObserverFactory()
	{}
};

#endif // IGAME_OBSERVER_H
