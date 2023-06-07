#pragma once

#include "Animation.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "Tweening.h"

struct SDL_Texture;

class SceneEnding : public Module
{
public:

	explicit SceneEnding(bool startEnabled);

	// Destructor
	virtual ~SceneEnding();

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

	bool OnGuiMouseClickEvent(GuiControl* control) override;

public:

	bool enableMusic;
	bool enteredEnding;

private:

	// Ending Screen

	SDL_Texture* endingScreen;

	Animation ending;
	Animation* currentAnimation;

	// UI

	SDL_Texture* resume;
	GuiButton* Resume;

	SDL_Texture* backTitle;
	GuiButton* BackTitle;

	// Tween

	int offset = 808;

	Tween Animation_Resume;
	float point_Resume;

	Tween Animation_BackTitle;
	float point_BackTitle;

};