#pragma once

#include "Scene.h"

struct SDL_Texture;

class SceneBattle : public Scene
{
public:

	SceneBattle();
	
	// Destructor
	virtual ~SceneBattle();

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

	//Variables a cambiar por las del player y las del enemigo
	//Player
	int p_HP = 100;
	int p_DEF = 10;
	int p_DMG = 50;

	//Enemy
	int e_HP = 60;
	int e_DEF = 10;
	int e_DMG = 20;


};