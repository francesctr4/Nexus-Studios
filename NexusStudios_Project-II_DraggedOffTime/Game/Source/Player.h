#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"
#include "Timer.h"
#include "Physics.h"

struct SDL_Texture;

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

public:

	bool godMode;

	SDL_Texture* dialogueUI_player;

private:

	bool showDialogue;

	SDL_Texture* selector;
	SDL_Texture* text;

	int selectorIterator;
	b2Vec2 selectorPositions[4] = { b2Vec2(232, 539), b2Vec2(639,539), b2Vec2(232,603), b2Vec2(639,603) };

	int speed;

	// Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// Add physics to the player 
	PhysBody* pbody;

	Animation* currentAnimation;
	Animation idle_right;

};

#endif // __PLAYER_H__