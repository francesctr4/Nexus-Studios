#pragma once

#include "Animation.h"

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

private:

	SDL_Texture* endingScreen;

	Animation ending;
	Animation* currentAnimation;

};