#pragma once

#include "Scene.h"

struct SDL_Texture;

class SceneLogo : public Scene
{
public:

	SceneLogo();

	// Destructor
	virtual ~SceneLogo();

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

private:



};