#pragma once

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"
#include "Textures.h"

class GuiSlider : public GuiControl
{
public:

	GuiSlider(uint32 id, SDL_Rect bounds, SDL_Texture* tex, const char* text);
	virtual ~GuiSlider();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;
	SDL_Texture* tex;
	SDL_Rect rect;

	int x;
	int y;
	int posx;
	int posy;
	int x1;
	int y1;
	int x2;
	int y2;

	bool debug;

	uint buttonHovering;
	bool hoverOnce;

};