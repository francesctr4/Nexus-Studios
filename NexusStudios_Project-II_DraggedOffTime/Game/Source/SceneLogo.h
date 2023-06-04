#pragma once

#include "Animation.h"

struct SDL_Texture;

class SceneLogo : public Module
{
public:

	explicit SceneLogo(bool startEnabled);

	// Destructor
	virtual ~SceneLogo();

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

	SDL_Texture* nexusStudiosLogo;

	SDL_Texture* nexusSpritesheet1;
	Animation nexus1;

	SDL_Texture* nexusSpritesheet2;
	Animation nexus2;

	Animation* currentAnimation;

	uint logoFX;
	bool FX_played;

};