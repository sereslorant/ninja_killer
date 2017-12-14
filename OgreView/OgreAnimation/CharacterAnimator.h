#ifndef CHARACTER_ANIMATOR_H
#define CHARACTER_ANIMATOR_H

#include "../AnimationState/IAnimationState.h"

#include "PrimitiveAnimation.h"

class CharacterAnimator
{
private:
	std::map<std::string,PrimitiveAnimation> animations;
	
	std::string current_anim_name;
	PrimitiveAnimation *current_animation = nullptr;
	
public:
	
	void Visit(const IAnimationState &anim_state,Ogre::Entity *character_entity)
	{
		if(current_anim_name != anim_state.GetAnimationName())
		{
			if(current_animation != nullptr)
			{
				current_animation->OnExit(character_entity);
				current_animation = nullptr;
			}
			
			auto I = animations.find(anim_state.GetAnimationName());
			if(I != animations.end())
			{
				current_anim_name = I->first;
				current_animation = &I->second;
				
				current_animation->OnEnter(character_entity);
			}
		}
	}
	
	void Animate(Ogre::Entity *character_entity)
	{
		if(current_animation != nullptr)
			{current_animation->Animate(character_entity);}
	}
	
	void AddAnimation(const std::string &anim_name,PrimitiveAnimation animation)
	{
		animations.insert({anim_name,animation});
	}
	
	CharacterAnimator()
	{}
};

#endif // CHARACTER_ANIMATOR_H
