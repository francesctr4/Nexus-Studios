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

enum class WeaponEra
{
	UNKNOWN,

	PREHISTORIC,
	MEDIEVAL,
	CYBERPUNK,
	APOCALYPSE,

	MAX

};

class Weapon 
{
public:

	Weapon(WeaponEra wEra, WeaponType wType, int damage) {

		this->wEra = wEra;
		this->wType = wType;
		this->damage = damage;

	}

	virtual ~Weapon() {}

public:

	WeaponEra wEra;
	WeaponType wType;
	int damage;

};