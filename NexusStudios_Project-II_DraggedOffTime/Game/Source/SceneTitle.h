#pragma once

#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

#include "Animation.h"
#include "Tweening.h"

struct SDL_Texture;

class SceneTitle : public Module
{
public:

	explicit SceneTitle(bool startEnabled);

	// Destructor
	virtual ~SceneTitle();

	bool Awake(pugi::xml_node& config) override;

	// Called before the first frame
	bool Start() override;

	// Called before all Updates
	bool PreUpdate() override;

	// Called each loop iteration
	bool Update(float dt) override;

	// Called after all Updates
	bool PostUpdate() override;

	// Called before quitting
	bool CleanUp() override;

	// Call
	bool OnGuiMouseClickEvent(GuiControl* control) override;

public:

	bool enableMusic;

	uint titleFX;
	bool FX_played;

	bool showSettings;

public:

	SDL_Texture* Fondo;

	SDL_Texture* titleScreen;
	SDL_Texture* draggedOffTime;

	SDL_Texture* newGame;
	GuiButton* NewGame;

	SDL_Texture* continue_;
	GuiButton* Continue_;
	bool continueEnabled;

	SDL_Texture* settings;
	GuiButton* Settings;

	SDL_Texture* credits;
	GuiButton* Credits;

	SDL_Texture* exit;
	GuiButton* Exit;

	SDL_Texture* back;
	GuiButton* Back;

	SDL_Texture* SettingsTitle;
	SDL_Texture* PauseTitle;

	SDL_Texture* slider;
	SDL_Texture* SlideBar;

	SDL_Texture* Music;
	GuiSlider* SliderMusic;

	SDL_Texture* SFX;
	GuiSlider* SliderFX;

	SDL_Texture* framecap;
	SDL_Texture* FPS;
	SDL_Texture* framecapUP;
	GuiButton* FramecapUP;
	SDL_Texture* framecapDOWN;
	GuiButton* FramecapDOWN;

	SDL_Texture* checkBox;

	SDL_Texture* checkBoxFullscreen;
	GuiCheckBox* CheckBoxFullscreen;

	SDL_Texture* checkBoxVsync;
	GuiCheckBox* CheckBoxVsync;

	SDL_Texture* titleSpritesheet;
	Animation title;
	Animation* currentAnimation;

	// Credits

	bool showCredits;
	GuiButton* BackCredits;

	SDL_Texture* bigCredits;

	SDL_Texture* people1;
	SDL_Texture* people2;

	// Tweens

	int offset = 808;

	Tween Animation_DraggedOffTime;
	float point_DraggedOffTime;

	Tween Animation_NewGame;
	float point_NewGame;

	Tween Animation_Continue;
	float point_Continue;

	Tween Animation_Settings;
	float point_Settings;

	Tween Animation_Credits;
	float point_Credits;

	Tween Animation_Exit;
	float point_Exit;

	// Tweens Settings

	Tween Animation_BigSettings;
	float point_BigSettings;

	Tween Animation_Back;
	float point_Back;

	// Tweens Credits

	Tween Animation_BigCredits;
	float point_BigCredits;

	Tween Animation_People1;
	float point_People1;

	Tween Animation_People2;
	float point_People2;

	Tween Animation_BackCredits;
	float point_BackCredits;

};