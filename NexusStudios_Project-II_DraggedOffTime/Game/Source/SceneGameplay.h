#pragma once

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "Scene.h"

struct SDL_Texture;

class SceneGameplay : public Scene
{
public:

	SceneGameplay();

	// Destructor
	virtual ~SceneGameplay();

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