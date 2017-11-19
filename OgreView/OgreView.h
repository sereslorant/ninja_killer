#ifndef OGRE_VIEW_H
#define OGRE_VIEW_H

#include "OgreEntityView.h"
#include "OgreCharacterView.h"
#include "OgreCameraView.h"

#include <GameLogic/IGameObserver.h>

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderWindow.h>


class OgreView : public IEntityObserverFactory
{
private:
	Ogre::Root &root;
	Ogre::RenderWindow &window;
	
	Ogre::SceneManager *scene;
	
	std::unique_ptr<OgreEntityRepository> entity_repository;
	
	Ogre::SceneNode *root_node;
	
	Ogre::Viewport *viewport;
	
	Ogre::Camera *camera;
	
	std::list<std::unique_ptr<OgreEntityView> > entity_views;
	std::list<std::unique_ptr<OgreCharacterView> > character_views;
	std::list<std::unique_ptr<OgreCameraView> > camera_views;
	/*
	void CreateTestScene()
	{
		camera = scene->createCamera("PlayerCamera");
		
		float viewport_width = 1.0f;
		float viewport_height = 1.0f;
		float viewport_left	= (1.0f - viewport_width) * 0.5f;
		float viewport_top = (1.0f - viewport_height) * 0.5f;
		unsigned short viewport_z_order = 100;
		viewport = window.addViewport(camera, viewport_z_order, viewport_left, viewport_top, viewport_width, viewport_height);
		
		viewport->setAutoUpdated(true);
		
		viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
		
		float ratio = float(viewport->getActualWidth()) / float(viewport->getActualHeight());
		camera->setAspectRatio(ratio);
		
		camera->setNearClipDistance(1.5f);
		camera->setFarClipDistance(3000.0f);
		
		window.setActive(true);
		
		window.setAutoUpdated(false);
	}
	*/
public:
	
	virtual ICameraObserver *CreateCameraObserver() override
	{
		OgreCameraView *new_view = new OgreCameraView(*camera);
		camera_views.emplace_back(new_view);
		
		return new_view;
	}
	
	virtual IVisibleObserver *CreateEntityObserver() override
	{
		//Ogre::Entity *entity = scene->createEntity("explosive.mesh");
		
		Ogre::SceneNode *entity_node = root_node->createChildSceneNode();
		//entity_node->attachObject(entity);
		
		OgreEntityView *new_view = new OgreEntityView(*entity_repository,*entity_node);
		entity_views.emplace_back(new_view);
		
		return new_view;
	}
	
	virtual ICharacterObserver *CreateCharacterObserver() override
	{
		Ogre::SceneNode *character_node = root_node->createChildSceneNode();
		
		OgreCharacterView *new_view = new OgreCharacterView(*entity_repository,*character_node);
		character_views.emplace_back(new_view);
		
		return new_view;
	}
	
	void Update()
	{
		for(auto &character : character_views)
		{
			character->Update();
		}
	}
	
	/*
	Ogre::SceneNode &GetCameraNode()
	{
		return *camera_node;
	}
	*/
	OgreView(Ogre::Root &p_root,Ogre::RenderWindow &p_window)
		:root(p_root),window(p_window)
	{
		scene = root.createSceneManager(Ogre::ST_GENERIC,"SceneManager");
		root_node = scene->getRootSceneNode();
		
		camera = scene->createCamera("PlayerCamera");
		
		float viewport_width = 1.0f;
		float viewport_height = 1.0f;
		float viewport_left	= (1.0f - viewport_width) * 0.5f;
		float viewport_top = (1.0f - viewport_height) * 0.5f;
		unsigned short viewport_z_order = 100;
		viewport = window.addViewport(camera, viewport_z_order, viewport_left, viewport_top, viewport_width, viewport_height);
		
		viewport->setAutoUpdated(true);
		
		viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
		
		float ratio = float(viewport->getActualWidth()) / float(viewport->getActualHeight());
		camera->setAspectRatio(ratio);
		
		camera->setNearClipDistance(1.5f);
		camera->setFarClipDistance(3000.0f);
		
		window.setActive(true);
		
		window.setAutoUpdated(false);
		
		Ogre::ResourceGroupManager &resourceGroupManager = Ogre::ResourceGroupManager::getSingleton();
		
		Ogre::String resourceGroupName = "ResGroup";
		
		resourceGroupManager.createResourceGroup(resourceGroupName);
		
		resourceGroupManager.addResourceLocation("Content/Textures","FileSystem",resourceGroupName,false);
		resourceGroupManager.addResourceLocation("Content/Materials","FileSystem",resourceGroupName,false);
		resourceGroupManager.addResourceLocation("Content/Meshes","FileSystem",resourceGroupName,false);
		
		resourceGroupManager.initialiseResourceGroup(resourceGroupName);
		resourceGroupManager.loadResourceGroup(resourceGroupName);
		
		Ogre::Light *light = scene->createLight();
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		
		light->setDiffuseColour(1.0,1.0,1.0);
		light->setSpecularColour(1.0,1.0,1.0);
		
		Ogre::SceneNode *lightNode = root_node->createChildSceneNode();
		lightNode->attachObject(light);
		
		scene->setAmbientLight(Ogre::ColourValue(0.75,0.75,0.75,1.0));
		
		entity_repository = std::unique_ptr<OgreEntityRepository>(new OgreEntityRepository(*scene,"Content/Prefabs.json"));
	}
	
	virtual ~OgreView() override
	{
		root.destroySceneManager(scene);
	}
};

#endif // OGRE_VIEW_H
