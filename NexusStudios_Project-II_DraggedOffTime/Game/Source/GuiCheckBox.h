#pragma once

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

	GuiCheckBox(uint32 id, SDL_Rect bounds, SDL_Texture* tex, const char* text);
	virtual ~GuiCheckBox();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;

	SDL_Texture* tex;
	SDL_Rect rect;

	bool crossed;

	bool debug;

	uint buttonHovering;
	bool hoverOnce;

	uint buttonPressed;
	bool pressedOnce;

};
