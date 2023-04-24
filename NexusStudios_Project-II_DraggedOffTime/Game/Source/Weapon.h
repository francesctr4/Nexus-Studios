#pragma once

#include "Animation.h"

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

	SDL_Texture* texture;
	int damage;
	Animation* currentAnimation;
	Animation idle;

};