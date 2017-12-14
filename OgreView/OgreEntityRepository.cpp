
#include <fstream>

#include "OgreEntityRepository.h"

#include <lJSON/lJSON_Util.h>
#include <lJSON/lJSON_TypeRetriever.h>

Ogre::Vector3 VectorFromJSON(const liJSON_Array *array)
{
	float values[3] = {0.0,0.0,0.0};
	
	for(int i=0;i < std::min<int>(array->Size(),3);i++)
	{
		values[i] = lJSON_Util::FloatFromJSON(array->GetElement(i));
	}
	
	return Ogre::Vector3(values);
}

Ogre::Quaternion QuaternionFromJSON(const liJSON_Object *object)
{
	float angle = lJSON_Util::FloatFromJSON(object->GetVariable("Angle"));
	Ogre::Vector3 axis = VectorFromJSON(ToConstArray(object->GetVariable("Axis")));
	
	return Ogre::Quaternion(Ogre::Radian(angle),axis);
}


void OgreEntityRepository::LoadAnimators()
{
	{
		PrimitiveAnimation leg_run_anim = {"leg_run",2.0,true};
		PrimitiveAnimation leg_stand_anim = {"leg_stand",2.0,true};
		
		CharacterAnimator soldier_leg_animator;
		soldier_leg_animator.AddAnimation("LegRunning",leg_run_anim);
		soldier_leg_animator.AddAnimation("LegStanding",leg_stand_anim);
		
		leg_animator_records.insert({"Soldier",soldier_leg_animator});
	}
	{
		PrimitiveAnimation up_run_anim = {"up_run",2.0,true};
		PrimitiveAnimation up_stand_anim = {"up_stand",2.0,true};
		PrimitiveAnimation up_weapon_hold_anim = {"up_weapon_hold",2.0,true};
		PrimitiveAnimation up_shoot_anim = {"up_shoot",5.0,true};
		PrimitiveAnimation up_death_anim = {"death",1.0,false};
		
		CharacterAnimator soldier_up_animator;
		soldier_up_animator.AddAnimation("UpRunning",up_run_anim);
		soldier_up_animator.AddAnimation("UpStanding",up_stand_anim);
		soldier_up_animator.AddAnimation("UpAiming",up_weapon_hold_anim);
		soldier_up_animator.AddAnimation("UpShooting",up_shoot_anim);
		soldier_up_animator.AddAnimation("Dead",up_death_anim);
		
		body_animator_records.insert({"Soldier",soldier_up_animator});
	}
	{
		PrimitiveAnimation ninja_idle = {"Idle2",1.0,true};
		PrimitiveAnimation ninja_stealth = {"Stealth",2.0,true};
		PrimitiveAnimation ninja_death = {"Death2",0.5,false};
		PrimitiveAnimation ninja_retard = {"Backflip",2.0,true};
		PrimitiveAnimation ninja_melee = {"Attack2",2.0,true};
		
		CharacterAnimator ninja_up_animator;
		ninja_up_animator.AddAnimation("Standing",ninja_idle);
		ninja_up_animator.AddAnimation("Running",ninja_stealth);
		ninja_up_animator.AddAnimation("Dead",ninja_death);
		ninja_up_animator.AddAnimation("Shooting",ninja_retard);
		ninja_up_animator.AddAnimation("Melee",ninja_melee);
		
		body_animator_records.insert({"Ninja",ninja_up_animator});
	}
}

void OgreEntityRepository::LoadAnimationStates()
{
	{
		PrimitiveAnimationState leg_moving_state = {"LegRunning","LegRunning"};
		PrimitiveAnimationState leg_standing_state = {"LegStanding","LegStanding"};
		PrimitiveAnimationState leg_dead_state = {"LegDead","NO_ANIM"};
		CompositeAnimationState leg_state = {"LegRoot"};
		
		leg_moving_state.AddNextState("OnStanding",&leg_standing_state);
		leg_standing_state.AddNextState("OnMoving",&leg_moving_state);
		
		leg_moving_state.AddNextState("OnDying",&leg_dead_state);
		leg_standing_state.AddNextState("OnDying",&leg_dead_state);
		
		leg_state.SetInitialState(&leg_standing_state);
		
		IAnimationState *soldier_leg_root = leg_state.Clone(leg_children);
		leg_anim_state_records.insert({"Soldier",soldier_leg_root});
	}
	{
		PrimitiveAnimationState up_moving_state = {"UpRunning","UpRunning"};
		PrimitiveAnimationState up_standing_state = {"UpStanding","UpStanding"};
		CompositeAnimationState up_idle_state = {"UpIdle"};
		
		PrimitiveAnimationState up_aiming_state = {"UpAiming","UpAiming"};
		CompositeAnimationState up_not_shooting_state = {"UpNotShooting"};
		
		PrimitiveAnimationState up_shooting_state = {"UpShooting","UpShooting"};
		PrimitiveAnimationState up_dead_state = {"UpDead","Dead"};
		CompositeAnimationState up_state = {"UpRoot"};
		
		up_moving_state.AddNextState("OnStanding",&up_standing_state);
		up_standing_state.AddNextState("OnMoving",&up_moving_state);
		
		up_idle_state.SetInitialState(&up_standing_state);
		
		up_idle_state.AddNextState("OnAiming",&up_aiming_state);
		up_aiming_state.AddNextState("OnAimReleased",&up_idle_state);
		
		up_not_shooting_state.SetInitialState(&up_idle_state);
		
		up_not_shooting_state.AddNextState("OnShooting",&up_shooting_state);
		up_shooting_state.AddNextState("OnShootingReleased",&up_not_shooting_state);
		
		up_not_shooting_state.AddNextState("OnDying",&up_dead_state);
		up_shooting_state.AddNextState("OnDying",&up_dead_state);
		
		up_state.SetInitialState(&up_not_shooting_state);
		
		IAnimationState *soldier_body_root = up_state.Clone(up_children);;
		body_anim_state_records.insert({"Soldier",soldier_body_root});
	}
	{
		PrimitiveAnimationState moving_state = {"Running","Running"};
		PrimitiveAnimationState standing_state = {"Standing","Standing"};
		
		CompositeAnimationState idle = {"Idle"};
		PrimitiveAnimationState shooting = {"Shooting","Shooting"};
		PrimitiveAnimationState melee = {"Melee","Melee"};
		
		CompositeAnimationState alive = {"Alive"};
		PrimitiveAnimationState dead_state = {"Dead","Dead"};
		
		CompositeAnimationState ninja_state = {"Root"};
		
		
		idle.AddNextState("OnShooting",&shooting);
		shooting.AddNextState("OnShootingReleased",&idle);
		
		idle.AddNextState("OnMelee",&melee);
		melee.AddNextState("OnMeleeReleased",&idle);
		
		moving_state.AddNextState("OnStanding",&standing_state);
		standing_state.AddNextState("OnMoving",&moving_state);
		
		idle.SetInitialState(&standing_state);
		
		alive.AddNextState("OnDying",&dead_state);
		alive.SetInitialState(&idle);
		
		ninja_state.SetInitialState(&alive);
		
		IAnimationState *ninja_root = ninja_state.Clone(up_children);
		body_anim_state_records.insert({"Ninja",ninja_root});
	}
}

OgreEntityRepository::OgreEntityRepository(Ogre::SceneManager &p_scene_manager,const std::string &filename)
		:scene_manager(p_scene_manager)
{
	LoadAnimators();
	LoadAnimationStates();
	
	std::ifstream fin(filename.c_str());
	
	if(fin.is_open())
	{
		liJSON_Value *value;
		lJSON_Util::Parse(fin,value);
		
		const liJSON_Object *root = ToConstObject(value);
		if(root != nullptr)
		{
			root->Forall([this](const std::string &key,const liJSON_Value *value)
				{
					std::cout << key << std::endl;
					const liJSON_Object *mesh = ToConstObject(value);
					
					Ogre::Vector3 displacement = VectorFromJSON(ToConstArray(mesh->GetVariable("Displacement")));
					Ogre::Vector3 scale = VectorFromJSON(ToConstArray(mesh->GetVariable("Scale")));
					Ogre::Quaternion orientation = QuaternionFromJSON(ToConstObject(mesh->GetVariable("Orientation")));
					
					const std::string &mesh_name = ToConstString(mesh->GetVariable("MeshName"))->GetValue();
					
					mesh_records.insert({key,MeshRecord(displacement,scale,orientation,mesh_name)});
				}
			);
		}
		
		delete value;
	}
}
