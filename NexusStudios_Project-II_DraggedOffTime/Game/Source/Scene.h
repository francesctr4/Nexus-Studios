#pragma once

#include "Log.h"
#include "PugiXml/src/pugixml.hpp"

class GuiControl;
struct SDL_Texture;

enum class SceneType
{
	NONE,
	LOGO,
	TITLE,
	GAMEPLAY,
	BATTLE
};

class Scene
{
public:

	// Constructor
	Scene() 
	{
		active = false;
		transitionRequired = false;
		nextScene = SceneType::NONE;
		showColliders = false;
	} 

	// Destructor
	virtual ~Scene() {}

	// Called before the first frame
	virtual bool Start() = 0;

	// Called before all Updates
	virtual bool PreUpdate() = 0;

	// Called each loop iteration
	virtual bool Update(float dt) = 0;

	// Called after all Updates
	virtual bool PostUpdate() = 0;

	// Called before quitting
	virtual bool CleanUp() = 0;

	// Define multiple Gui Event methods
	virtual bool OnGuiMouseClickEvent(GuiControl* control) = 0;

	bool LoadState(pugi::xml_node&) {}

	bool SaveState(pugi::xml_node&) const {}

	void TransitionToScene(SceneType scene) 
	{
		LOG("Changing Scene");

		transitionRequired = true;
		nextScene = scene;
	}

public:

	SString name;
	bool active;

	bool transitionRequired;
	SceneType nextScene;

	bool showColliders;

};