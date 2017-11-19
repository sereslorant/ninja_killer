
#include <GameLogic/IGameLoop.h>

#include "OgreView/OgreView.h"
#include "OisController.h"

#include <memory>

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreWindowEventUtilities.h>

#include <OIS/OIS.h>

struct OgreSettings
{
	Ogre::String plugins_file	= "plugins.cfg";
	Ogre::String config_file		= "";
	Ogre::String log_file		= "Ogre.log";
	
	Ogre::String window_title = "OgreTest";
};

class OgreGame
{
private:
	std::unique_ptr<Ogre::Root> root;
	Ogre::RenderWindow *window = nullptr;
	
	OIS::InputManager *input_manager;
	
	bool init_successful = false;
	
public:
	
	bool InitSuccessful()
	{
		return init_successful;
	}
	
	void Loop()
	{
		OgreView test_view(*root,*window);
		
		OIS::Keyboard	*keyboard	= static_cast<OIS::Keyboard*>(input_manager->createInputObject(OIS::OISKeyboard,false));
		OIS::Mouse		*mouse		= static_cast<OIS::Mouse*>(input_manager->createInputObject(OIS::OISMouse,false));
		
		OisController test_controller(keyboard,mouse);
		
		keyboard->capture();
		
		std::unique_ptr<IGameFactory> test_factory(CreateGameFactory());
		std::unique_ptr<IGameLoop> test_loop(test_factory->CreateGame(test_controller,test_view));
		
		while(!window->isClosed() && (!keyboard->isKeyDown(OIS::KC_ESCAPE)))
		{
			test_controller.UpdateInput();
			
			test_loop->Loop();
			
			test_view.Update();
			
			window->update(false);
			window->swapBuffers();
			
			root->renderOneFrame();
			
			Ogre::WindowEventUtilities::messagePump();
		}
	}
	
	OgreGame(const OgreSettings &settings)
		:root(new Ogre::Root(settings.plugins_file,settings.config_file,settings.log_file))
	{
		/*
		 * Setting up RenderSystem
		 */
		
		const Ogre::RenderSystemList &render_systems = root->getAvailableRenderers();
		
		if(render_systems.size() == 0)
		{
			Ogre::LogManager::getSingleton().logMessage("Failed to initialize render system");
			return;
		}
		
		Ogre::RenderSystem *render_system = render_systems[0];
		root->setRenderSystem(render_system);
		
		/*
		 * Setting up window
		 */
		
		bool create_window = false;
		Ogre::String customCapacities = "";
		
		root->initialise(create_window,settings.window_title,customCapacities);
		
		unsigned int window_width = 800;
		unsigned int window_height = 600;
		bool fullscreen = false;
		Ogre::NameValuePairList window_params;
		window_params["FSAA"] = "0";
		window_params["vsync"] = "true";
		
		window = root->createRenderWindow(settings.window_title,window_width,window_height,fullscreen,&window_params);
		
		/*
		 * Setting up input manager
		 */
		
		OIS::ParamList input_params;
		
		size_t window_handle = 0;
		window->getCustomAttribute("WINDOW",&window_handle);
		input_params.insert(std::make_pair(std::string("WINDOW"),std::to_string(window_handle)));
		
		input_manager = OIS::InputManager::createInputSystem(input_params);
		
		/*
		 * Setting up flags
		 */
		
		init_successful = true;
	}
	
	~OgreGame()
	{
		OIS::InputManager::destroyInputSystem(input_manager);
	}
};

int main(int argc,char *argv[])
{
	//try
	//{
		OgreSettings settings;
		
		OgreGame game(settings);
		
		if(game.InitSuccessful())
		{
			game.Loop();
		}
	/*}
	catch(Ogre::Exception &e)
	{
		Ogre::LogManager::getSingleton().logMessage(std::string("Ogre exception: ") + e.what());
	}
	catch(std::exception &e)
	{
		Ogre::LogManager::getSingleton().logMessage(std::string("std exception: ") + e.what());
	}*/
	
	return 0;
}
