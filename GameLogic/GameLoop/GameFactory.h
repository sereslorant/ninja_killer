#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

#include <IGameLoop.h>

#include "GameLoop.h"

class GameFactory : public IGameFactory
{
public:
	
	virtual IGameLoop *CreateGame(const IController &p_test_controller,IEntityObserverFactory &p_observer_factory) override
	{
		return new GameLoop(p_test_controller,p_observer_factory);
	}
	
	GameFactory()
	{}
	
	virtual ~GameFactory() override
	{}
};

#endif // GAME_FACTORY_H
