#ifndef PRIMITIVE_ANIMATION_H
#define PRIMITIVE_ANIMATION_H

#include <OGRE/OgreEntity.h>

class PrimitiveAnimation
{
private:
	std::string anim_name;
	float anim_speed;
	bool loop;
	
public:
	
	void OnEnter(Ogre::Entity *character)
	{
		character->getAnimationState(anim_name)->setEnabled(true);
		character->getAnimationState(anim_name)->setWeight(1);
		character->getAnimationState(anim_name)->setTimePosition(0.0);
	}
	
	void OnExit(Ogre::Entity *character)
	{
		character->getAnimationState(anim_name)->setEnabled(false);
	}
	
	void Animate(Ogre::Entity *character)
	{
		float dt = 1.0/60.0;
		if(loop)
		{
			character->getAnimationState(anim_name)->addTime(dt*anim_speed);
		}
		else
		{
			if(character->getAnimationState(anim_name)->getLength() >
				(character->getAnimationState(anim_name)->getTimePosition() + anim_speed*dt))
			{
				character->getAnimationState(anim_name)->addTime(dt*anim_speed);
			}
		}
	}
	
	PrimitiveAnimation(const std::string &p_anim_name,float p_anim_speed,bool p_loop)
		:anim_name(p_anim_name),anim_speed(p_anim_speed),loop(p_loop)
	{}
};

#endif // PRIMITIVE_ANIMATION_H
