#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <GameLoop/BehaviorManager/BehaviorManager.h>

#include <map>

#include <Entities/IEntity.h>
#include <Entities/VisibleObjects/Character.h>

class EntityManager
{
private:
	std::list<std::unique_ptr<IEntity> > entities;
	
	std::map<std::string,Character *> named_characters;
	
public:
	
	void AddEntity(IEntity *entity)
	{
		entities.emplace_back(entity);
	}
	
	void AddNamedCharacter(const std::string &name,Character *character)
	{
		AddEntity(character);
		
		named_characters[name] = character;
	}
	
	Character *GetNamedCharacter(const std::string &name)
	{
		Character *ret_val = nullptr;
		
		auto I = named_characters.find(name);
		if(I != named_characters.end())
		{
			ret_val = I->second;
		}
		
		return ret_val;
	}
	
	void UpdateEntities()
	{
		for(auto &entity : entities)
		{
			entity->Step();
		}
	}
	
	EntityManager()
	{}
};

#endif // ENTITY_MANAGER_H
