
#include "GameFactory.h"

IGameFactory *CreateGameFactory()
{
	return new GameFactory;
}
