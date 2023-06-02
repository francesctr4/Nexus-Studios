#pragma once

#include "Animation.h"
#include "SString.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"

struct SDL_Texture;

enum class WeaponType 
{
	MELEE,
	MID_RANGE,
	LONG_RANGE
};

class Weapon 
{
public:

	explicit Weapon(int width);

	virtual ~Weapon();

	void Load(const char* path);

	void Draw(int posX, int posY);

private:	

	SDL_Texture* texture;
	int width;

	int damage;
	Animation* currentAnimation;
	Animation idle;

};