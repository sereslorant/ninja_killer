#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <Entities/Camera.h>

#include <Physics/BulletWorldWrapper.h>
#include <GameLoop/BehaviorManager/BehaviorManager.h>
#include <GameLoop/EntityManager/EntityManager.h>


#include <IGameLoop.h>

#include <EntityBehaviors/BehaviorTree/IBehavior.h>

#include <EntityBehaviors/Character/AIController/AIContext.h>

#include <EntityBehaviors/Character/AIController/AIMovementController.h>
#include <EntityBehaviors/Character/AIController/AILookController.h>
#include <EntityBehaviors/Character/AIController/AIWeaponController.h>

class AIEntity : public IEntity
{
private:
	std::list<unsigned int> behavior_path;
	
	Character &character;
	IBehavior<AIContext> *default_behavior = nullptr;
	
	AIMovementController movement_controller;
	AILookController look_controller;
	AIWeaponController weapon_controller;
	
public:
	
	class AIEntityPercept
	{
	private:
		AIEntity *entity;
		
	public:
		
		void CheckCharacter(Character *character)
		{
			if(character->GetSpecies() != entity->character.GetSpecies())
			{
				auto I = entity->labeled_characters.find("closest_enemy");
				if(I != entity->labeled_characters.end())
				{
					Character *closest_character = I->second;
					
					float current_distance = (closest_character->GetPosition() - entity->character.GetPosition()).length2();
					float new_distance = (character->GetPosition() - entity->character.GetPosition()).length2();
					if(new_distance < current_distance)
					{
						entity->labeled_characters["closest_enemy"] = character;
					}
				}
				else
				{
					entity->labeled_characters["closest_enemy"] = character;
				}
			}
		}
		
		AIEntityPercept(AIEntity *p_entity)
			:entity(p_entity)
		{}
	};
	
	AIEntityPercept percept;
	
	std::map<std::string,Character *> labeled_characters;
	
	void SetBehavior(IBehavior<AIContext> *behavior)
	{
		default_behavior = behavior;
	}
	
	virtual void Step() override
	{
		weapon_controller.SetState(false,false,false);
		
		if(default_behavior != nullptr)
		{
			AIContext context(behavior_path,labeled_characters,character,movement_controller,look_controller,weapon_controller);
			
			default_behavior->Run(context);
		}
	}
	
	AIEntity(Character &p_character)
		:character(p_character),percept(this)
	{
		character.SetMovementController(&movement_controller);
		character.SetLookController(&look_controller);
		character.SetWeaponController(&weapon_controller);
		
		movement_controller.SetYaw(character.GetYaw());
	}
};

#include <PlayerController/PlayerMovementController.h>
#include <PlayerController/PlayerLookController.h>
#include <PlayerController/PlayerWeaponController.h>
#include <PlayerController/PlayerCameraController.h>

class PlayerEntity : public IEntity
{
private:
	PlayerMovementController movement_controller;
	PlayerLookController look_controller;
	PlayerWeaponController weapon_controller;
	
	PlayerCameraController camera_controller;
	
public:
	
	virtual void Step() override
	{
		camera_controller.Step();
	}
	
	PlayerEntity(Character &character,Camera &p_camera,const IController &p_controller)
		:movement_controller(p_controller),
		 look_controller(p_controller),
		 weapon_controller(p_controller),
		 camera_controller(character,p_camera,p_controller)
	{
		character.SetMovementController(&movement_controller);
		character.SetLookController(&look_controller);
		character.SetWeaponController(&weapon_controller);
	}
};



#include "EntityManager/ObjectLoader/VisibleObjectLoader.h"
#include "EntityManager/ObjectLoader/CharacterLoader.h"



#include <GameLoop/BehaviorManager/BehaviorTreeLoader/CompositeLoader/ParallelBehaviorLoader.h>
#include <GameLoop/BehaviorManager/BehaviorTreeLoader/CompositeLoader/SequenceBehaviorLoader.h>
#include <GameLoop/BehaviorManager/BehaviorTreeLoader/CompositeLoader/SelectorBehaviorLoader.h>

#include <GameLoop/BehaviorManager/BehaviorTreeLoader/DecoratorLoader/LiarBehaviorLoader.h>


#include <GameLoop/BehaviorManager/AIBehaviorLoader/Conditions/AICharacterWithinRangeLoader.h>

#include <GameLoop/BehaviorManager/AIBehaviorLoader/LookActions/AILookAtCharacterLoader.h>
#include <GameLoop/BehaviorManager/AIBehaviorLoader/MovementActions/AIFollowCharacterLoader.h>
#include <GameLoop/BehaviorManager/AIBehaviorLoader/MovementActions/AITurnTowardsCharacterLoader.h>

#include <GameLoop/BehaviorManager/AIBehaviorLoader/WeaponActions/AIAimLoader.h>
#include <GameLoop/BehaviorManager/AIBehaviorLoader/WeaponActions/AIShootLoader.h>
#include <GameLoop/BehaviorManager/AIBehaviorLoader/WeaponActions/AIMeleeLoader.h>

#include <Entities/VisibleObjects/Projectile.h>

class ProjectileFactory : public IProjectileFactory
{
private:
	BulletWorldWrapper &world;
	EntityManager &entity_manager;
	
public:
	virtual void SpawnBullet(const btVector3 &position,const btVector3 &velocity,float radius,unsigned int species) override
	{
		BulletBodyBuilder body_builder(world);
		
		body_builder.CreateSphere().SetRadius(radius).Build();
		
		btRigidBody *projectile_body = body_builder.SetMass(0.25).SetPosition(position).SetVelocity(velocity).Build();
		
		IVisibleObjectState *visible_state = new BulletVisibleObjectState(projectile_body);
		Projectile *projectile = new Projectile(visible_state,"Projectile",species);
		
		ICollisionCallback *projectile_callback = projectile;
		projectile_body->setUserPointer(projectile_callback);
		
		//projectile_body->forceActivationState(DISABLE_DEACTIVATION);
		
		entity_manager.AddProjectile(projectile);
	}
	
	ProjectileFactory(BulletWorldWrapper &p_world,EntityManager &p_entity_manager)
		:world(p_world),entity_manager(p_entity_manager)
	{}
	virtual ~ProjectileFactory() override
	{}
};

class GameLoop : public IGameLoop
{
private:
	BulletWorldWrapper world;
	
	EntityManager entity_manager;
	BehaviorManager behavior_loader;
	
	ProjectileFactory projectile_factory;
	
	Camera test_camera;
	
	std::unique_ptr<PlayerEntity> test_player_controller;
	
public:
	
	virtual void Loop() override
	{
		world.stepSimulation(1.0/60.0);
		
		test_camera.Step();
		
		entity_manager.UpdateEntities();
		
		test_player_controller->Step();
	}
	
	GameLoop(const IController &p_test_controller,IEntityObserverFactory &observer_factory)
		:entity_manager(observer_factory),projectile_factory(world,entity_manager)
	{
		test_camera.AddObserver(observer_factory.CreateCameraObserver());
		
		new LiarBehaviorLoader(behavior_loader);
		
		new ParallelBehaviorLoader(behavior_loader);
		new SequenceBehaviorLoader(behavior_loader);
		new SelectorBehaviorLoader(behavior_loader);
		
		new AICharacterWithinRangeLoader(behavior_loader,entity_manager);
		
		new AILookAtCharacterLoader(behavior_loader,entity_manager);
		new AIFollowCharacterLoader(behavior_loader,entity_manager);
		new AITurnTowardsCharacterLoader(behavior_loader,entity_manager);
		
		new AIAimLoader(behavior_loader,entity_manager);
		new AIShootLoader(behavior_loader,entity_manager);
		new AIMeleeLoader(behavior_loader,entity_manager);
		
		/*
		 * Adding simple stuff
		 */
		/*
		for(int i=0;i < 5;i++)
		{
			SimpleVisibleObjectState *visible_state = new SimpleVisibleObjectState({0.0f,0.0f,50.0f - i * 50.0f},{{0.0,1.0,0.0},0.0});
			VisibleObject *visible = new VisibleObject(visible_state,"Archway");
			
			entity_manager.AddVisibleObject(visible);
		}
		*/
		{
			std::ifstream fin("Content/Entities/AtheneGhost.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				VisibleObjectLoader visible_loader(world);
				visible_loader.Load(ToConstObject(value.get()));
				
				visible_loader.SetPosition({0.0f,0.0f,-200.0f});
				
				VisibleObject *visible = visible_loader.Build();
				entity_manager.AddVisibleObject(visible);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/RoomEntity.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				VisibleObjectLoader visible_loader(world);
				visible_loader.Load(ToConstObject(value.get()));
				
				VisibleObject *visible = visible_loader.Build();
				
				entity_manager.AddVisibleObject(visible);
			}
		}
		
		/*
		 * Adding test phys mesh
		 */
		
		{
			std::ifstream fin("Content/Entities/Explosive.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				VisibleObjectLoader visible_loader(world);
				
				visible_loader.Load(ToConstObject(value.get()));
				
				visible_loader.SetPosition({0.0,0.0,20.0});
				
				VisibleObject *test_visible = visible_loader.Build();
				
				entity_manager.AddVisibleObject(test_visible);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Soldier.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({0.0,0.0,0.0});
				character_loader.SetSpecies(0);
				
				Character *test_character = character_loader.Build();
				
				test_player_controller = std::unique_ptr<PlayerEntity>(new PlayerEntity(*test_character,test_camera,p_test_controller));
				
				//entity_manager.AddEntity(test_player_controller);
				entity_manager.AddNamedCharacter("player_character",test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({ 110.0,0.0,0.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},-PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({130.0,0.0,0.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},-PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({150.0,0.0,0.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},-PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({-110.0,0.0,0.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({-130.0,0.0,0.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({-150.0,0.0,0.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({-150.0,0.0,10.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Ninja.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({-150.0,0.0,-10.0});
				character_loader.SetOrientation({{0.0,1.0,0.0},PI/2.0});
				character_loader.SetSpecies(1);
				
				Character *test_character = character_loader.Build();
				
				AIEntity *ninja_ai = new AIEntity(*test_character);
				ninja_ai->SetBehavior(behavior_loader.GetBehavior("enemy_behavior"));
				
				entity_manager.AddCharacterFilter([ninja_ai](Character *character)
					{
						ninja_ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ninja_ai);
				entity_manager.AddCharacter(test_character);
			}
		}
		
		{
			std::ifstream fin("Content/Entities/Soldier.json");
			
			liJSON_Value *json;
			lJSON_Util::Parse(fin,json);
			{
				std::unique_ptr<liJSON_Value> value(json);
				
				CharacterLoader character_loader(world,projectile_factory);
				
				character_loader.Load(ToConstObject(value.get()));
				
				character_loader.SetPosition({-30.0,0.0,-30.0});
				character_loader.SetSpecies(0);
				
				Character *ai_test_character  = character_loader.Build();
				
				AIEntity *ai = new AIEntity(*ai_test_character);
				ai->SetBehavior(behavior_loader.GetBehavior("squadmate_behavior"));
				
				entity_manager.AddCharacterFilter([ai](Character *character)
					{
						ai->percept.CheckCharacter(character);
					}
				);
				
				entity_manager.AddEntity(ai);
				entity_manager.AddCharacter(ai_test_character);
			}
		}
		
		behavior_loader.LoadBehaviors();
	}
	
	virtual ~GameLoop() override
	{}
};

#endif // GAME_LOOP_H
