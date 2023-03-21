#pragma once

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "Scene.h"

struct SDL_Texture;

class SceneTitle : public Scene
{
public:

	SceneTitle();

	// Destructor
	virtual ~SceneTitle();

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