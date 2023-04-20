#pragma once

#include "Player.h"
#include "NPC.h"
#include "Enemy.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

struct SDL_Texture;

class SceneGameplay : public Module
{
public:

	SceneGameplay(bool startEnabled);

	// Destructor
	virtual ~SceneGameplay();

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

	bool showPause;
	bool showSettings;

public:

	Player* player;
	bool map_selector = false;
	int actually = 0;

	List<Enemy*> enemies;

	SDL_Texture* Fondo;

	//Pause UI

	SDL_Texture* PauseTitle;

	SDL_Texture* resume;
	GuiButton* Resume;

	SDL_Texture* settings;
	GuiButton* Settings;

	SDL_Texture* backTitle;
	GuiButton* BackTitle;

	SDL_Texture* exit;
	GuiButton* Exit;

	//Settings UI

	SDL_Texture* SettingsTitle;

	SDL_Texture* checkBox;

	SDL_Texture* checkBoxFullscreen;
	GuiCheckBox* CheckBoxFullscreen;

	SDL_Texture* checkBoxVsync;
	GuiCheckBox* CheckBoxVsync;

	SDL_Texture* framecap;
	SDL_Texture* FPS;
	SDL_Texture* framecapUP;
	GuiButton* FramecapUP;
	SDL_Texture* framecapDOWN;
	GuiButton* FramecapDOWN;

	SDL_Texture* slider;
	SDL_Texture* SlideBar;

	SDL_Texture* Music;
	GuiSlider* SliderMusic;

	SDL_Texture* SFX;
	GuiSlider* SliderFX;

	SDL_Texture* back;
	GuiButton* Back;

	//SFX
	uint OpenPause;
	uint ClosePause;

};