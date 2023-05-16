#pragma once

#include "Animation.h"

struct SDL_Texture;

class SceneEnding : public Module
{
public:

	SceneEnding(bool startEnabled);

	// Destructor
	virtual ~SceneEnding();

	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

public:

	bool enableMusic;

private:

	SDL_Texture* endingScreen;

	Animation ending;
	Animation* currentAnimation;

};