#pragma once

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "DynArray.h"
#include "Timer.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

enum class EnemyState
{
	IDLE,
	ROAMING,
	ATTACKING,
	DYING
};

enum class EnemyType
{
	DAMAGE,
	SUPPORT,
	TANK

};

class Enemy : public Entity
{
public:

	Enemy();

	virtual ~Enemy();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void OnCollisionEnd(PhysBody* physA, PhysBody* physB);

	void Death();

public:

	SDL_Texture* texture;
	const char* texturePath;

	SDL_Texture* textureBattle;
	const char* texturePathBattle;

private:

	EnemyType type;

	int hp;
	int atk;
	int def;

	bool playerInteraction;

	PhysBody* pbody;
	PhysBody* enemySensor;

	Animation* currentAnimation;
	Animation idle_right;

};