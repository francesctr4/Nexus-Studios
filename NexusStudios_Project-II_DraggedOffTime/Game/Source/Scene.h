#pragma once

#include "Log.h"
#include "PugiXml/src/pugixml.hpp"

class GuiControl;
struct SDL_Texture;

enum class SceneType
{
	TITLE,
	GAMEPLAY
};

class Scene
{
public:

	// Constructor
	Scene() : active(false), transitionRequired(false) {}

	// Destructor
	virtual ~Scene() {}

	// Called before the first frame
	virtual bool Start() { return true; }

	// Called before all Updates
	virtual bool PreUpdate() { return true; }

	// Called each loop iteration
	virtual bool Update(float dt) { return true; }

	// Called after all Updates
	virtual bool PostUpdate() { return true; }

	// Called before quitting
	virtual bool CleanUp(){ return true; }

	virtual bool LoadState(pugi::xml_node&) { return true; }

	virtual bool SaveState(pugi::xml_node&) const { return true; }

	void TransitionToScene(SceneType scene) 
	{
		LOG("Changing Scene");

		transitionRequired = true;
		nextScene = scene;
	}

	// Define multiple Gui Event methods
	virtual bool OnGuiMouseClickEvent(GuiControl* control)
	{
		return true;
	}

public:

	SString name;
	bool active;

	bool transitionRequired;
	SceneType nextScene;

	bool showColliders;

};