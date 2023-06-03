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
	TANK,
	UNKNOWN
};

class Enemy : public Entity
{
public:

	explicit Enemy();

	virtual ~Enemy();

	bool Awake() override;

	bool Start() override;

	bool Update() override;

	bool CleanUp() override;

	void OnCollision(PhysBody* physA, PhysBody* physB) override;

	void OnCollisionEnd(PhysBody* physA, PhysBody* physB) override;

	void Death();
	
	void AddEnemy(Enemy* enemy, EnemyType type, int x, int y);

public:

	SDL_Texture* texture;
	const char* texturePath;

	SDL_Texture* textureBattle;
	const char* texturePathBattle;

public:

	EnemyType etype;

	int hp;
	int atk;
	int def;
 
	int width = 32;
	int height = 32;

	bool playerInteraction;

	List<Enemy*> enemies;

	PhysBody* pbody;
	PhysBody* enemySensor;

	Animation* currentAnimation;
	Animation idle_right;

	int enemyMap;

};