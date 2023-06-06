#pragma once

#include "Animation.h"

struct SDL_Texture;

class SceneLore : public Module
{
public:

	explicit SceneLore(bool startEnabled);

	// Destructor
	virtual ~SceneLore();

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


};