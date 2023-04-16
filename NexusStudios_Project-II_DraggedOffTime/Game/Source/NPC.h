#pragma once

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class NPC : public Entity
{
public:

	NPC();
	virtual ~NPC();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

private:

	SDL_Texture* texture;
	const char* texturePath;

	PhysBody* pbody;

	Animation* currentAnimation;
	Animation idle_right;

};