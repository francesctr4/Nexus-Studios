#pragma once

#include "Animation.h"
#include "SString.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Animation.h"

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

	void WeaponAnimationDeclaration();

public:

	WeaponEra wEra;
	WeaponType wType;
	int damage;

private:

	// Animations

	float weaponIdleSpeed = 0.06f;

	Animation rusticStoneAxe_idle;
	int rusticStoneAxe_idle_width = 0;
	int rusticStoneAxe_idle_height = 0;
	Animation rusticStoneAxe_attack;
	int rusticStoneAxe_attack_width = 480;
	int rusticStoneAxe_attack_height = 288;
	float rusticStoneAxe_attack_speed = 0.4f;

	Animation tribalLance_idle;
	int tribalLance_idle_width = 288;
	int tribalLance_idle_height = 288;
	Animation tribalLance_attack;
	int tribalLance_attack_width = 480;
	int tribalLance_attack_height = 288;
	float tribalLance_attack_speed = 0.4f;

	Animation chiefsBow_idle;
	int chiefsBow_idle_width = 192;
	int chiefsBow_idle_height = 198;
	Animation chiefsBow_attack;
	int chiefsBow_attack_width = 510;
	int chiefsBow_attack_height = 198;
	float chiefsBow_attack_speed = 0.4f;

		// -------------------------

	Animation fallenBlade_idle;
	int fallenBlade_idle_width = 192;
	int fallenBlade_idle_height = 192;
	Animation fallenBlade_attack;
	int fallenBlade_attack_width = 474;
	int fallenBlade_attack_height = 336;
	float fallenBlade_attack_speed = 0.4f;

	Animation ascendantTwins_idle;
	int ascendantTwins_idle_width = 192;
	int ascendantTwins_idle_height = 192;
	Animation ascendantTwins_attack;
	int ascendantTwins_attack_width = 1002;
	int ascendantTwins_attack_height = 282;
	float ascendantTwins_attack_speed = 0.4f;

	Animation mrFlail_idle;
	int mrFlail_idle_width = 0;
	int mrFlail_idle_height = 0;
	Animation mrFlail_attack;
	int mrFlail_attack_width = 0;
	int mrFlail_attack_height = 0;
	float mrFlail_attack_speed = 0.4f;

		// -------------------------

	Animation chainsword_idle;
	int chainsword_idle_width = 288;
	int chainsword_idle_height = 216;
	Animation chainsword_attack;
	int chainsword_attack_width = 540;
	int chainsword_attack_height = 390;
	float chainsword_attack_speed = 0.4f;

	Animation uraniumshell_idle;
	int uraniumshell_idle_width = 192;
	int uraniumshell_idle_height = 192;
	Animation uraniumshell_attack;
	int uraniumshell_attack_width = 480;
	int uraniumshell_attack_height = 204;
	float uraniumshell_attack_speed = 0.4f;

	Animation ionizedRifle_idle;
	int ionizedRifle_idle_width = 288;
	int ionizedRifle_idle_height = 192;
	Animation ionizedRifle_attack;
	int ionizedRifle_attack_width = 480;
	int ionizedRifle_attack_height = 234;
	float ionizedRifle_attack_speed = 0.4f;

		// -------------------------

	Animation graftedClaws_idle;
	int graftedClaws_idle_width = 192;
	int graftedClaws_idle_height = 180;
	Animation graftedClaws_attack;
	int graftedClaws_attack_width = 768;
	int graftedClaws_attack_height = 188;
	float graftedClaws_attack_speed = 0.4f;

	Animation agony_idle;
	int agony_idle_width = 0;
	int agony_idle_height = 0;
	Animation agony_attack;
	int agony_attack_width = 576;
	int agony_attack_height = 324;
	float agony_attack_speed = 0.4f;

	Animation eyebull_idle;
	int eyebull_idle_width = 0;
	int eyebull_idle_height = 0;
	Animation eyebull_attack;
	int eyebull_attack_width = 0;
	int eyebull_attack_height = 0;
	float eyebull_attack_speed = 0.4f;

};