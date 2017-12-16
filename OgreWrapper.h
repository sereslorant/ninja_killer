#ifndef OGRE_WRAPPER_H
#define OGRE_WRAPPER_H

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreWindowEventUtilities.h>

#include <memory>

struct OgreSettings
{
	Ogre::String plugins_file	= "plugins.cfg";
	Ogre::String config_file		= "";
	Ogre::String log_file		= "Ogre.log";
	
	Ogre::String window_title = "OgreTest";
};

class OgreWrapper
{
private:
	std::unique_ptr<Ogre::Root> root;
	Ogre::RenderWindow *window = nullptr;
	
	
	bool init_successful = false;
	
public:
	
	Ogre::Root *GetRoot()
	{
		return root.get();
	}
	
	Ogre::RenderWindow *GetWindow()
	{
		return window;
	}
	
	std::size_t GetWindowHandle()
	{
		std::size_t window_handle = 0;
		window->getCustomAttribute("WINDOW",&window_handle);
		
		return window_handle;
	}
	
	bool InitSuccessful()
	{
		return init_successful;
	}
	
	void Render()
	{
		window->update(false);
		window->swapBuffers();
		
		root->renderOneFrame();
		
		Ogre::WindowEventUtilities::messagePump();
	}
	
	OgreWrapper(const OgreSettings &settings)
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
		 * Setting up flags
		 */
		
		init_successful = true;
	}
	
	~OgreWrapper()
	{}
};

#endif // OGRE_WRAPPER_H
