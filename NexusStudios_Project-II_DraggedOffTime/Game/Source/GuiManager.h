#pragma once

#include "Module.h"
#include "GuiControl.h"

#include "List.h"

class GuiManager : public Module
{
public:

	// Constructor
	explicit GuiManager(bool startEnabled);

	// Destructor
	virtual ~GuiManager();

	// Called before the first frame
	bool Start() override;

	bool Update(float dt) override;

	bool Draw();

	// Called before quitting
	bool CleanUp() override;

	// Additional methods
	GuiControl* CreateGuiControl(GuiControlType type, int id, SDL_Texture* tex, const char* text, SDL_Rect bounds, Module* observer, SDL_Rect sliderBounds = { 0,0,0,0 });

public:

	List<GuiControl*> guiControlsList;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	SDL_Texture* texture;

};