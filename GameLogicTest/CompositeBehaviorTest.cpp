
#include <iostream>

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/BehaviorTree/Composites/SelectorBehavior.h>
#include <EntityBehaviors/BehaviorTree/Composites/SequenceBehavior.h>

#include <list>

class DummyContext
{
private:
	std::list<unsigned int> behavior_path;
	
public:
	
	std::list<unsigned int> &GetBehaviorPath()
	{
		return behavior_path;
	}
};

#include <EntityBehaviors/BehaviorTree/Decorators/LiarBehavior.h>

template<class ContextType_T>
class ConstBehavior : public LiarBehavior<ContextType_T>
{
public:
	
	void SetValue(BehaviorState new_value)
	{
		this->value = new_value;
	}
	
	ConstBehavior(BehaviorState p_value)
		:LiarBehavior<ContextType_T>(p_value)
	{}
	virtual ~ConstBehavior() override
	{}
};

void PrintList(const std::list<unsigned int> &list)
{
	for(unsigned int element : list)
	{
		std::cout << element << ";";
	}
	
	std::cout << "|" << std::endl;
}

void TestSequence1()
{
	std::cout << "Test sequence 1" << std::endl;
	
	ConstBehavior<DummyContext> behavior1 = {RUNNING};
	ConstBehavior<DummyContext> behavior2 = {RUNNING};
	ConstBehavior<DummyContext> behavior3 = {RUNNING};
	SequenceBehavior<DummyContext> sequence = {&behavior1,&behavior2,&behavior3};
	
	DummyContext context;
	PrintList(context.GetBehaviorPath());
	
	sequence.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior1.SetValue(SUCCEEDED);
	sequence.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior2.SetValue(SUCCEEDED);
	sequence.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior3.SetValue(SUCCEEDED);
	sequence.Run(context);
	PrintList(context.GetBehaviorPath());
}

void TestSequence2()
{
	std::cout << "Test sequence 2" << std::endl;
	
	ConstBehavior<DummyContext> behavior1 = {RUNNING};
	ConstBehavior<DummyContext> behavior2 = {RUNNING};
	ConstBehavior<DummyContext> behavior3 = {RUNNING};
	ConstBehavior<DummyContext> behavior4 = {RUNNING};
	SequenceBehavior<DummyContext> sequence1 = {&behavior3,&behavior4};
	SequenceBehavior<DummyContext> sequence2 = {&behavior1,&behavior2,&sequence1};
	
	DummyContext context;
	PrintList(context.GetBehaviorPath());
	
	behavior1.SetValue(SUCCEEDED);
	sequence2.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior2.SetValue(SUCCEEDED);
	sequence2.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior3.SetValue(SUCCEEDED);
	sequence2.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior4.SetValue(SUCCEEDED);
	sequence2.Run(context);
	PrintList(context.GetBehaviorPath());
}

void TestSequence3()
{
	std::cout << "Test sequence 3" << std::endl;
	
	ConstBehavior<DummyContext> behavior1 = {RUNNING};
	ConstBehavior<DummyContext> behavior2 = {RUNNING};
	SequenceBehavior<DummyContext> sequence = {&behavior1,&behavior2};
	
	DummyContext context;
	PrintList(context.GetBehaviorPath());
	
	//sequence.Run(context);
	//PrintList(context.GetBehaviorPath());
	
	behavior1.SetValue(FAILED);
	sequence.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior1.SetValue(SUCCEEDED);
	sequence.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior2.SetValue(SUCCEEDED);
	sequence.Run(context);
	PrintList(context.GetBehaviorPath());
}

void TestSelector1()
{
	std::cout << "Test selector 1" << std::endl;
	
	ConstBehavior<DummyContext> behavior1 = {RUNNING};
	ConstBehavior<DummyContext> behavior2 = {RUNNING};
	ConstBehavior<DummyContext> behavior3 = {RUNNING};
	SelectorBehavior<DummyContext> selector = {&behavior1,&behavior2,&behavior3};
	
	DummyContext context;
	PrintList(context.GetBehaviorPath());
	
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior1.SetValue(FAILED);
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior2.SetValue(FAILED);
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior3.SetValue(FAILED);
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
}

void TestSelector2()
{
	std::cout << "Test selector 2" << std::endl;
	
	ConstBehavior<DummyContext> behavior1 = {RUNNING};
	ConstBehavior<DummyContext> behavior2 = {RUNNING};
	ConstBehavior<DummyContext> behavior3 = {RUNNING};
	ConstBehavior<DummyContext> behavior4 = {RUNNING};
	SelectorBehavior<DummyContext> selector1 = {&behavior3,&behavior4};
	SelectorBehavior<DummyContext> selector2 = {&behavior1,&behavior2,&selector1};
	
	DummyContext context;
	PrintList(context.GetBehaviorPath());
	
	behavior1.SetValue(FAILED);
	selector2.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior2.SetValue(FAILED);
	selector2.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior3.SetValue(FAILED);
	selector2.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior4.SetValue(FAILED);
	selector2.Run(context);
	PrintList(context.GetBehaviorPath());
}

void TestSelector3()
{
	std::cout << "Test selector 3" << std::endl;
	
	ConstBehavior<DummyContext> behavior1 = {RUNNING};
	ConstBehavior<DummyContext> behavior2 = {RUNNING};
	ConstBehavior<DummyContext> behavior3 = {RUNNING};
	SelectorBehavior<DummyContext> selector = {&behavior1,&behavior2,&behavior3};
	
	DummyContext context;
	PrintList(context.GetBehaviorPath());
	
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior1.SetValue(FAILED);
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior2.SetValue(FAILED);
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
	
	behavior3.SetValue(FAILED);
	selector.Run(context);
	PrintList(context.GetBehaviorPath());
}

int main(int argc, char *argv[])
{
	TestSequence1();
	TestSequence2();
	TestSequence3();
	
	TestSelector1();
	TestSelector2();
	//TestSelector3();
	
	return 0;
}
