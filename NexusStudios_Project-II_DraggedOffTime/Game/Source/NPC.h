#pragma once

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

enum class NPC_Types {

	ROGUE,
	WIZARD,
	ORC

};

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

	void OnCollisionEnd(PhysBody* physA, PhysBody* physB);

private:

	NPC_Types type;

	SDL_Texture* dialogue;

	SDL_Texture* UIdialogue;

	SDL_Texture* npcIcon;
	SDL_Texture* npcIcon_Transparent;

	bool togglePlayerTalking;

	bool playerInteraction;
	bool dialogueActivated;

	SDL_Texture* texture;
	const char* texturePath;

	PhysBody* pbody;
	PhysBody* npcSensor;

	Animation* currentAnimation;
	Animation idle_right;

};