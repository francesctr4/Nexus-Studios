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

struct PlayerStats {

	int level;
	int currentXP;
	int next;
	int hp;
	int atk;
	int def;
	int ap;

};

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake() override;

	bool Start() override;

	bool Update() override;

	bool CleanUp() override;

	void OnCollision(PhysBody* physA, PhysBody* physB) override;

	void OnCollisionEnd(PhysBody* physA, PhysBody* physB) override;

	// Player Movement Functions
	void KeyboardMovementManagement();
	void GamepadMovementManagement();

	// Player Progression Functions
	void AddXP(int xp, int playerIndex);
	void PlayerLevelManagement();

	void Death();

	void Teleport(int x, int y);

public:

	int playerChange;
	uint changeFX;

	// Player Progession (Levels) variables

	PlayerStats playerStats[4];
	SDL_Rect xpAccumulatedRect[4] = { SDL_Rect({ 793,321,243,13 }) , SDL_Rect({ 793,321,243,13 }), SDL_Rect({ 793,321,243,13 }), SDL_Rect({ 793,321,243,13 }) };
	float fillPercentage[4] = { 0,0,0,0 };
	int fillWidth[4] = { 0,0,0,0 };
	uint levelUp;

	bool godMode;

	int speedX;
	int speedY;

	int speedValue;

	b2Vec2 vel;

	// Declare player parameters
	SDL_Texture* texture[4];

	const char* texturePath;
	const char* texturePath2;
	const char* texturePath3;
	const char* texturePath4;

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

	bool executeTeleportLobby = false;
	bool executeTeleportLobby_Infierno = false;
	bool executeTeleportLobby_Prehistoria = false;
	bool executeTeleportLobby_Medieval = false;

	bool executeTeleportInfierno = false;
	bool executeTeleportInfiernoReversa = false;
	bool executeTeleportInfiernoJovani = false;

	bool executeTeleportPrehistoria = false;
	bool executeTeleportPrehistoriaReversa = false;
	bool executeTeleportPrehistoriaJovani = false;

	bool executeTeleportMedieval = false;
	bool executeTeleportMedievalReversa = false;
	bool executeTeleportMedievalJovani = false;


};

#endif // __PLAYER_H__