#ifndef BULLET_CONTROLLABLE_H
#define BULLET_CONTROLLABLE_H

#include <Entities/MovingObject.h>

#include <btBulletDynamicsCommon.h>

class BulletControllable : public IControllable
{
private:
	btRigidBody *wrapped_body;
	
public:
	
	virtual const btVector3 &GetVelocity() override
	{
		return wrapped_body->getLinearVelocity();
	}
	
	virtual float GetYaw() override
	{
		const btVector3 &up = {0.0,1.0,0.0};
		return up.dot(wrapped_body->getOrientation().getAxis()) * wrapped_body->getOrientation().getAngle();
	}
	
	virtual void ApplyForce(const btVector3 &force) override
	{
		//wrapped_body->setLinearVelocity((displacement) * direction);
		wrapped_body->applyCentralForce(force);
		/*
		std::cout << wrapped_body->getInvMass() << std::endl;
		std::cout << wrapped_body->getAngularFactor()[0] << ";" << wrapped_body->getAngularFactor()[1] << ";" << wrapped_body->getAngularFactor()[2] << std::endl;
		std::cout << wrapped_body->getAngularVelocity()[0] << ";" << wrapped_body->getAngularVelocity()[1] << ";" << wrapped_body->getAngularVelocity()[2] << std::endl;
		std::cout << wrapped_body->getLocalInertia()[0] << ";" << wrapped_body->getLocalInertia()[1] << ";" << wrapped_body->getLocalInertia()[2] << std::endl;
		std::cout << wrapped_body->getTotalForce()[0] << ";" << wrapped_body->getTotalForce()[1] << ";" << wrapped_body->getTotalForce()[2] << std::endl;
		*/
	}
	
	virtual void SetOrientation(const btVector3 &d_axis,btScalar d_orientation) override
	{
		wrapped_body->setAngularVelocity((d_orientation) * d_axis);
		//wrapped_body->applyTorque((d_orientation) * d_axis);
	}
	
	BulletControllable(btRigidBody *p_wrapped_body)
		:wrapped_body(p_wrapped_body)
	{
		wrapped_body->forceActivationState(DISABLE_DEACTIVATION);
	}
	
	virtual ~BulletControllable() override
	{}
};

#endif // BULLET_CONTROLLABLE_H
