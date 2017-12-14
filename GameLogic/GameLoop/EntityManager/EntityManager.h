#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <IGameObserver.h>

#include <map>

#include <Entities/IEntity.h>
#include <Entities/VisibleObjects/Character.h>
#include <Entities/VisibleObjects/Projectile.h>

class EntityManager
{
private:
	std::list<std::unique_ptr<IEntity> > entities;
	
	std::map<std::string,Character *> named_characters;
	
	std::list<Character *> characters;
	std::list<std::function<void(Character *)> > character_filters;
	
	IEntityObserverFactory &observer_factory;
	
public:
	
	void AddEntity(IEntity *entity)
	{
		entities.emplace_back(entity);
	}
	
	void AddVisibleObject(VisibleObject *visible_object)
	{
		entities.emplace_back(visible_object);
		
		visible_object->AddObserver(observer_factory.CreateEntityObserver());
	}
	
	void AddProjectile(Projectile *projectile)
	{
		entities.emplace_back(projectile);
		
		projectile->AddObserver(observer_factory.CreateEntityObserver());
	}
	
	void AddCharacter(Character *character)
	{
		entities.emplace_back(character);
		characters.emplace_back(character);
		
		character->AddObserver(observer_factory.CreateCharacterObserver());
	}
	
	void AddNamedCharacter(const std::string &name,Character *character)
	{
		AddCharacter(character);
		
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
	
	void AddCharacterFilter(std::function<void(Character *)> new_filter)
	{
		character_filters.push_back(new_filter);
	}
	
	void UpdateEntities()
	{
		for(Character *character : characters)
		{
			for(auto &filter : character_filters)
			{
				filter(character);
			}
		}
		
		for(auto &entity : entities)
		{
			entity->Step();
		}
	}
	
	EntityManager(IEntityObserverFactory &p_observer_factory)
		:observer_factory(p_observer_factory)
	{}
};

#endif // ENTITY_MANAGER_H
