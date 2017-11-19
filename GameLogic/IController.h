#ifndef ICONTROLLER_H
#define ICONTROLLER_H

class IController
{
public:
	
	virtual bool MoveForward() const = 0;
	virtual bool MoveBackward() const = 0;
	virtual bool MoveLeft() const = 0;
	virtual bool MoveRight() const = 0;
	
	virtual bool Aim() const = 0;
	virtual bool Shoot() const = 0;
	
	virtual float GetYaw() const = 0;
	virtual float GetPitch() const = 0;
	
	IController()
	{}
	virtual ~IController()
	{}
};

class IControllerRepository
{
public:
	
	virtual unsigned int GetNumControllers() const = 0;
	virtual IController *GetController(unsigned int id) const = 0;
	
	IControllerRepository()
	{}
	virtual ~IControllerRepository()
	{}
};

#endif // ICONTROLLER_H
