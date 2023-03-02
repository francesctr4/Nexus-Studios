#pragma once

#include "Module.h"
#include "SDL/include/SDL_pixels.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font
{
	// Lookup table. All characters displayed in the same order as the texture
	char table[MAX_FONT_CHARS];

	int a = 8;

	SDL_Rect pos_coord[MAX_FONT_CHARS] = {
	{0, 0, 8, a},
	{9, 0, 8, a},
	{18, 0, 8, a},
	{27, 0, 8, a},
	{36, 0, 8, a},
	{45, 0, 8, a},
	{54, 0, 8, a},
	{63, 0, 8, a},
	{72, 0, 5, a},
	{78, 0, 8, a},
	{87, 0, 8, a},
	{96, 0, 7, a},
	{104, 0, 8, a},
	{113, 0, 8, a},
	{122, 0, 8, a},
	{131, 0, 8, a},
	{140, 0, 8, a},
	{149, 0, 8, a},
	{158, 0, 8, a},
	{167, 0, 7, a},
	{175, 0, 8, a},
	{184, 0, 8, a},
	{193, 0, 8, a},
	{202, 0, 8, a},
	{211, 0, 7, a},
	{219, 0, 8, a},
	{228, 0, 7, a},
	{236, 0, 7, a},
	{244, 0, 7, a},
	{252, 0, 7, a},
	{260, 0, 7, a},
	{268, 0, 6, a},
	{275, 0, 7, a},
	{283, 0, 7, a},
	{291, 0, 5, a},
	{297, 0, 7, a},
	{305, 0, 7, a},
	{313, 0, 5, a},
	{319, 0, 8, a},
	{328, 0, 7, a},
	{336, 0, 7, a},
	{344, 0, 7, a},
	{352, 0, 7, a},
	{360, 0, 7, a},
	{368, 0, 7, a},
	{376, 0, 6, a},
	{383, 0, 7, a},
	{391, 0, 6, a},
	{398, 0, 8, a},
	{407, 0, 8, a},
	{416, 0, 6, a},
	{423, 0, 7, a},
	{431, 0, 8, a},
	{440, 0, 5, a},
	{446, 0, 8, a},
	{455, 0, 8, a},
	{464, 0, 8, a},
	{473, 0, 8, a},
	{482, 0, 8, a},
	{491, 0, 8, a},
	{500, 0, 8, a},
	{509, 0, 8, a},
	{518, 0, 3, a},
	{522, 0, 3, a},
	{526, 0, 6, a},
	{533, 0, 6, a},
	{540, 0, 3, a},
	{544, 0, 7, a},
	{552, 0, 3, a},
	{556, 0, 7, a},
	{564, 0, 8, a},
	{573, 0, 8, a},
	{582, 0, 8, a},
	{591, 0, 5, a},
	{597, 0, 5, a},
	{603, 0, 6, a},
	{610, 0, 7, a},
	{618, 0, 6, a},
	{625, 0, 3, a},
	{629, 0, 3, a},
	{633, 0, 6, a},
	{640, 0, 7, a},
	{648, 0, 6, a},
	{655, 0, 5, a},
	{661, 0, 6, a},
	{668, 0, 5, a},
	{674, 0, 6, a},
	{681, 0, 5, a},
	{688, 0, 2, a},
	{691, 0, 6, a},
	{698, 0, 7, a},
	{706, 0, 7, a},
	{714, 0, 8, a} };

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;

};

class Fonts : public Module
{
public:

	// Constructor
	Fonts(bool startEnabled);

	// Destructor
	~Fonts();

	// Loads a font file from a texture
	// Returns a font index from the fonts array
	// Param texturePath	- The path to the texture file
	// Param characters		- The lookup table. All characters displayed in the same order as the texture
	// Param rows			- The amount of character rows in the texture
	int Load(const char* texturePath, const char* characters, uint rows = 1);

	// Removes a font by its index
	// Unloads the texture and removes it from the fonts array
	void UnLoad(int fontIndex);

	// Create a surface from text
	void BlitText(int x, int y, int fontIndex, const char* text) const;

public:

	int WindjammersFont = -1;

private:
	// An array to keep track and store all loaded fonts
	Font fonts[MAX_FONTS];
};