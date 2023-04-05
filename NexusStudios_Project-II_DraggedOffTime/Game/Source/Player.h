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

private:

	// Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// Add physics to the player 
	PhysBody* pbody;

};

#endif // __PLAYER_H__