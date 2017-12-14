#ifndef ICOLLISION_CALLBACK_H
#define ICOLLISION_CALLBACK_H

class ICollisionCallback
{
public:
	virtual unsigned int GetSpecies() = 0;
	
	virtual void TakeDamage(float damage) = 0;
	
	virtual void AcceptCollision(ICollisionCallback *callback) = 0;
	
	ICollisionCallback()
	{}
	virtual ~ICollisionCallback()
	{}
};

#endif // ICOLLISION_CALLBACK_H
