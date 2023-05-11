#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"
#include "Timer.h"
#include "Physics.h"

struct SDL_Texture;

struct NewPosition {
	float posX;
	float posY;
	bool t;

};

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void TeleportCofre();

	void Death();

	void Teleport(int x, int y);

public:

	bool godMode;

	bool textureChange;

private:

	int speed;

	// Declare player parameters
	SDL_Texture* texture;
	SDL_Texture* texture2;

	const char* texturePath;
	const char* texturePath2;

	// Add physics to the player 
	PhysBody* pbody;

	Animation* currentAnimation;
	Animation idle_right;
	Animation idle_left;
	Animation walk_right;
	Animation walk_left;

	bool idleDirection;

	NewPosition newPos;

	// Items FX

	uint itemCollectedFx;

	bool executeTeleportCofre = false;

};

#endif // __PLAYER_H__