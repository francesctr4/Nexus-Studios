#pragma once

#include "Module.h"
#include "Scene.h"

struct SDL_Texture;

class SceneManager : public Module
{
public:

	SceneManager(bool startEnabled);

	// Destructor
	virtual ~SceneManager();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node& load);

	bool SaveState(pugi::xml_node& save);

private:

	Scene* current;
	Scene* menu;
	Scene* next;

	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;

};