#ifndef IGAME_LOOP_H
#define IGAME_LOOP_H

#include "IGameObserver.h"
#include "IController.h"

class IGameLoop
{
public:
	
	virtual void Loop() = 0;
	
	IGameLoop()
	{}
	
	virtual ~IGameLoop()
	{}
};

class IGameFactory
{
public:
	
	virtual IGameLoop *CreateGame(const IController &p_test_controller,IEntityObserverFactory &observer_factory) = 0;
	
	IGameFactory()
	{}
	
	virtual ~IGameFactory()
	{}
};

IGameFactory *CreateGameFactory();

#endif // IGAME_LOOP_H
