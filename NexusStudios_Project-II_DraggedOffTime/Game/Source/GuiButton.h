#pragma once

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, SDL_Rect bounds, SDL_Texture* tex, const char* text);
	virtual ~GuiButton();

	bool Update(float dt) override;
	bool Draw(Render* render) override;

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;

	SDL_Texture* tex;
	SDL_Rect rect;

	bool debug;

	uint buttonHovering;
	bool hoverOnce;

	uint buttonPressed;
	bool pressedOnce;

	// Gamepad UI

	int selectedButton = 0;
	int maxID = 4;
	int featureMenuID[5] = { 429,430,431,432,433 };
	int charactersIDStats[4] = {560,561,562,563};

};