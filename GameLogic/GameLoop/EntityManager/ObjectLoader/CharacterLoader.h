#ifndef CHARACTER_LOADER_H
#define CHARACTER_LOADER_H

#include "VisibleLoader.h"

#include "../BulletLoader/BulletBodyLoader.h"

#include <Entities/VisibleObjects/Character.h>

#include <Entities/PhysicsObjects/BulletVisibleObjectState.h>
#include <Entities/PhysicsObjects/BulletControllable.h>

class CharacterLoader
{
private:
	VisibleLoader visible_loader;
	PhysBodyBuilder phys_body_builder;
	BulletBodyLoader phys_body_loader;
	
	IProjectileFactory &projectile_factory;
	
	unsigned int species = 0;
	
public:
	
	void SetPosition(const btVector3 &new_position)
	{
		phys_body_builder.SetPosition(new_position);
	}
	
	void SetOrientation(const btQuaternion &new_orientation)
	{
		phys_body_builder.SetOrientation(new_orientation);
	}
	
	void SetSpecies(unsigned int new_species)
	{
		species = new_species;
	}
	
	virtual void Load(const liJSON_Object *object)
	{
		object->Forall([this](const std::string &key,const liJSON_Value *value)
			{
				if(key == "visible")
				{
					visible_loader.Load(ToConstObject(value));
				}
				if(key == "body")
				{
					phys_body_loader.Load(ToConstObject(value));
				}
			}
		);
	}
	
	Character *Build()
	{
		Character *new_character = nullptr;
		
		btRigidBody *body = phys_body_builder.Build();
		if(body != nullptr)
		{
			IVisibleObjectState *visible_state = new BulletVisibleObjectState(body);
			IControllable *controllable = new BulletControllable(body);
			
			new_character = new Character(visible_state,visible_loader.GetLabel(),controllable,species,projectile_factory);
			
			ICollisionCallback *character_callback = new_character;
			body->setUserPointer(character_callback);
			
			std::cout << "Character registered: " << character_callback << ";" << body->getUserPointer() << std::endl;
		}
		
		return new_character;
	}
	
	CharacterLoader(PhysWorld &world,IProjectileFactory &p_projectile_factory)
		:phys_body_builder(world),phys_body_loader(phys_body_builder),projectile_factory(p_projectile_factory)
	{}
};

#endif // CHARACTER_LOADER_H
