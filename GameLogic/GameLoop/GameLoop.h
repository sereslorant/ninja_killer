#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <Entities/Camera.h>
#include <Entities/VisibleObjects/Character.h>

#include <Entities/VisibleObjects/SimpleVisibleObjectState.h>

#include <Physics/BulletWorldWrapper.h>

#include <Entities/PhysicsObjects/BulletVisibleObjectState.h>
#include <Entities/PhysicsObjects/BulletControllable.h>

#include "IGameLoop.h"

#include <EntityBehaviors/BehaviorTree/IBehavior.h>

#include <EntityBehaviors/Character/AIController/AIContext.h>

#include <EntityBehaviors/Character/AIController/AIMovementController.h>
#include <EntityBehaviors/Character/AIController/AIWeaponController.h>

class AIController
{
private:
	Character &character;
	IBehavior<AIContext> *default_behavior = nullptr;
	
public:
	
	AIMovementController movement_controller;
	AIWeaponController weapon_controller;
	
	void SetBehavior(IBehavior<AIContext> *behavior)
	{
		default_behavior = behavior;
	}
	
	void Step()
	{
		if(default_behavior != nullptr)
		{
			AIContext context(character,movement_controller);
			
			default_behavior->Run(context);
		}
	}
	
	AIController(Character &p_character,IControllable &p_controllable)
		:character(p_character),movement_controller(p_controllable)
	{
		character.SetMovementController(&movement_controller);
		character.SetWeaponController(&weapon_controller);
	}
};

#include <PlayerController/PlayerMovementController.h>
#include <PlayerController/PlayerLookController.h>
#include <PlayerController/PlayerWeaponController.h>
#include <PlayerController/PlayerCameraController.h>

class PlayerController
{
public:
	PlayerMovementController movement_controller;
	PlayerLookController look_controller;
	PlayerWeaponController weapon_controller;
	
	PlayerCameraController camera_controller;
	
	void Step()
	{
		camera_controller.Step();
	}
	
	PlayerController(IControllable &p_controllable,Character &p_tracked_entity,Camera &p_camera,const IController &p_controller)
		:movement_controller(p_controllable,p_controller),
		 look_controller(p_controller),
		 weapon_controller(p_controller),
		 camera_controller(p_tracked_entity,p_camera,p_controller)
	{
		Character &character = p_tracked_entity;
		
		character.SetMovementController(&movement_controller);
		character.SetLookController(&look_controller);
		character.SetWeaponController(&weapon_controller);
	}
};

#include <GameLoop/BehaviorManager/BehaviorTreeLoader/ParallelBehaviorLoader.h>

#include <GameLoop/BehaviorManager/AIBehaviorLoader/AIFollowCharacterLoader.h>
#include <GameLoop/BehaviorManager/AIBehaviorLoader/AITurnTowardsCharacterLoader.h>


#include "EntityManager/EntityManager.h"


class GameLoop : public IGameLoop
{
private:
	BulletWorldWrapper world;
	
	EntityManager entity_manager;
	
	BehaviorManager behavior_loader;
	
	Camera test_camera;
	
	std::unique_ptr<PlayerController> test_player_controller;
	std::unique_ptr<AIController> ai;
	
	btRigidBody *AddSphere(const btVector3 &position,const btVector3 &velocity,btScalar mass,btScalar radius,const btVector3 &angular_factor)
	{
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);
		
		btSphereShape *sphere = new btSphereShape(radius);
		btMotionState *motion_state = new btDefaultMotionState(transform);
		
		btVector3 local_inertia(0.0,0.0,0.0);
		if(mass > 0.0)
		{
			sphere->calculateLocalInertia(mass,local_inertia);
		}
		
		btRigidBody::btRigidBodyConstructionInfo ConstructionInfo(mass,motion_state,sphere,local_inertia);
		btRigidBody *rigid_body = world.createBody(ConstructionInfo);
		rigid_body->setLinearVelocity(velocity);
		
		rigid_body->setAngularFactor(angular_factor);
		
		return rigid_body;
	}

	void Init()
	{
		btTransform Transform;
		Transform.setIdentity();
		Transform.setOrigin(btVector3(0.0,0.0,0.0));
		
		btStaticPlaneShape *Plane = new btStaticPlaneShape(btVector3(0.0,1.0,0.0),0.0);
		btMotionState *MotionState = new btDefaultMotionState(Transform);
		
		btRigidBody::btRigidBodyConstructionInfo ConstructionInfo(0.0,MotionState,Plane);
		btRigidBody *rigid_body = world.createBody(ConstructionInfo);
	}
	
public:
	
	virtual void Loop() override
	{
		world.stepSimulation(1.0/60.0);
		
		entity_manager.UpdateEntities();
		
		test_camera.Step();
		
		test_player_controller->Step();
		ai->Step();
	}
	
	GameLoop(const IController &p_test_controller,IEntityObserverFactory &observer_factory)
	{
		test_camera.AddObserver(observer_factory.CreateCameraObserver());
		
		new ParallelBehaviorLoader(behavior_loader);
		new AIFollowCharacterLoader(behavior_loader,entity_manager);
		new AITurnTowardsCharacterLoader(behavior_loader,entity_manager);
		
		/*
		 * Adding simple stuff
		 */
		
		for(int i=0;i < 7;i++)
		{
			SimpleVisibleObjectState *visible_state = new SimpleVisibleObjectState({0.0f,0.0f,-100.0f - i * 50.0f},{{0.0,1.0,0.0},0.0});
			VisibleObject *visible = new VisibleObject(visible_state,"Archway.mesh");
			
			visible->AddObserver(observer_factory.CreateEntityObserver());
			
			if(i == 5)
			{visible->SetLabel("Athene.mesh");}
			
			if(i == 6)
			{visible->SetLabel("ninja.mesh");}
			
			//simple_stuff.emplace_back(visible);
			entity_manager.AddEntity(visible);
		}
		
		SimpleVisibleObjectState *visible_state = new SimpleVisibleObjectState({0.0f,0.0f,0.0f},{{0.0,1.0,0.0},0.0});
		VisibleObject *visible = new VisibleObject(visible_state,"level1.mesh");
		
		visible->AddObserver(observer_factory.CreateEntityObserver());
		//simple_stuff.emplace_back(visible);
		entity_manager.AddEntity(visible);
		
		/*
		 * Adding test phys mesh
		 */
		
		BulletVisibleObjectState *test_visible_state = new BulletVisibleObjectState(AddSphere({0.0,0.0,20.0},{0.0,0.0,0.0},5.0,5.0,{1.0,1.0,1.0}));
		
		VisibleObject *test_visible = new VisibleObject(test_visible_state,"explosive.mesh");
		test_visible->AddObserver(observer_factory.CreateEntityObserver());
		
		entity_manager.AddEntity(test_visible);
		
		btRigidBody *test_rigid_body = AddSphere({0.0,0.0,0.0},{0.0,0.0,0.0},5.0,5.0,{0.0,1.0,0.0});
		BulletVisibleObjectState *test_character_visible = new BulletVisibleObjectState(test_rigid_body);
		BulletControllable *test_character_controllable = new BulletControllable(test_rigid_body);
		
		Character *test_character = new Character(test_character_visible,"soldier.mesh",test_character_controllable);
		test_character->AddObserver(observer_factory.CreateCharacterObserver());
		
		entity_manager.AddNamedCharacter("player_character",test_character);
		
		test_player_controller = std::unique_ptr<PlayerController>(new PlayerController(*test_character_controllable,*test_character,test_camera,p_test_controller));
		
		btRigidBody *ai_rigid_body = AddSphere({-50.0,0.0,-50.0},{0.0,0.0,0.0},5.0,5.0,{0.0,1.0,0.0});
		BulletVisibleObjectState *ai_character_visible = new BulletVisibleObjectState(ai_rigid_body);
		BulletControllable *ai_character_controllable = new BulletControllable(ai_rigid_body);
		
		Character *ai_test_character = new Character(ai_character_visible,"soldier.mesh",ai_character_controllable);
		ai_test_character->AddObserver(observer_factory.CreateCharacterObserver());
		
		entity_manager.AddEntity(ai_test_character);
		
		ai = std::unique_ptr<AIController>(new AIController(*ai_test_character,*ai_character_controllable));
		ai->SetBehavior(behavior_loader.GetBehavior("squadmate_behavior"));
		
		behavior_loader.LoadBehaviors();
		
		Init();
	}
	
	virtual ~GameLoop() override
	{}
};

#endif // GAME_LOOP_H
