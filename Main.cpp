
#include <GameLogic/IGameLoop.h>

#include "OgreView/OgreView.h"
#include "OisController.h"

#include "OgreWrapper.h"

#include <OIS/OIS.h>

class OisWrapper
{
private:
	OIS::InputManager *input_manager;
	
public:
	
	OIS::Keyboard *GetKeyboard()
	{
		return static_cast<OIS::Keyboard*>(input_manager->createInputObject(OIS::OISKeyboard,false));
	}
	
	OIS::Mouse *GetMouse()
	{
		return static_cast<OIS::Mouse*>(input_manager->createInputObject(OIS::OISMouse,false));
	}
	
	OisWrapper(std::size_t window_handle)
	{
		OIS::ParamList input_params;
		input_params.insert(std::make_pair(std::string("WINDOW"),std::to_string(window_handle)));
		
		input_manager = OIS::InputManager::createInputSystem(input_params);
	}
	
	~OisWrapper()
	{
		OIS::InputManager::destroyInputSystem(input_manager);
	}
};

int main(int argc,char *argv[])
{
	try
	{
		OgreSettings settings;
		
		OgreWrapper wrapper(settings);
		
		if(wrapper.InitSuccessful())
		{
			OgreView test_view(*wrapper.GetRoot(),*wrapper.GetWindow());
			
			OisWrapper ois_wrapper(wrapper.GetWindowHandle());
			
			OIS::Keyboard	*keyboard	= ois_wrapper.GetKeyboard();
			OIS::Mouse		*mouse		= ois_wrapper.GetMouse();
			
			OisController test_controller(keyboard,mouse);
			
			keyboard->capture();
			
			std::unique_ptr<IGameFactory> test_factory(CreateGameFactory());
			std::unique_ptr<IGameLoop> test_loop(test_factory->CreateGame(test_controller,test_view));
			
			while(!wrapper.GetWindow()->isClosed() && (!keyboard->isKeyDown(OIS::KC_ESCAPE)))
			{
				test_controller.UpdateInput();
				
				test_loop->Loop();
				
				test_view.Update();
				wrapper.Render();
			}
		}
	}
	catch(Ogre::Exception &e)
	{
		Ogre::LogManager::getSingleton().logMessage(std::string("Ogre exception: ") + e.what());
	}
	catch(std::exception &e)
	{
		Ogre::LogManager::getSingleton().logMessage(std::string("std exception: ") + e.what());
	}
	
	return 0;
}
