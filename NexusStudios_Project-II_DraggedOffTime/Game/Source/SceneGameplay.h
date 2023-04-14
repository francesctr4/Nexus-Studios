#pragma once

#include "Scene.h"
#include "Player.h"

struct SDL_Texture;

class SceneGameplay : public Scene
{
public:

	SceneGameplay();

	// Destructor
	virtual ~SceneGameplay();

	bool Awake();

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

	Player* player;

};