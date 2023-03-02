#pragma once

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, SDL_Rect bounds, SDL_Texture* tex, const char* text);
	virtual ~GuiButton();

	bool Update(float dt);
	bool Draw(Render* render);

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

};