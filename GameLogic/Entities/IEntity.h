#ifndef IENTITY_H
#define IENTITY_H

class IEntity
{
public:
	virtual void Step() = 0;
	
	IEntity()
	{}
	virtual ~IEntity()
	{}
};

#endif // IENTITY_H
