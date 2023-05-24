#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"
#include "Point.h"

#include "SDL/include/SDL.h"
#include "SDL_ttf/include/SDL_ttf.h"
#include <algorithm>

class Render : public Module
{
public:

	Render(bool startEnabled);

	// Destructor
	virtual ~Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();

	// Drawing
	bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawText(std::string text, int posx, int posy, int w, int h, SDL_Color color);

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	// Declare Load / Save methods
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	// Center camera to player
	void CenterCamera();

public:

	SDL_Renderer* renderer;
	SDL_Rect camera;
	SDL_Rect viewport;
	SDL_Color background;
	TTF_Font* font;

};

#endif // __RENDER_H__