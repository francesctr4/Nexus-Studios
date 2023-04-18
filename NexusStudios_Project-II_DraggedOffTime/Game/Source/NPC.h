#pragma once

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "Physics.h"
#include "SDL/include/SDL.h"

enum class DialogueType {

	PLAYER,
	NPC

};

enum class NPC_Types {

	ROGUE,
	WIZARD,
	ORC

};

struct SDL_Texture;

struct Dialogue {

	SDL_Texture* text;
	DialogueType whoIsTalking;

};

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

	int i;
	const int firstDialogueDuration = 5;
	Dialogue firstDialogue[5];

	int iteradorDialogos;
	SDL_Texture* dialogos[3];

	NPC_Types type;

	SDL_Texture* dialogue;

	SDL_Texture* UIdialogue;
	SDL_Texture* dialogueUI_player;

	SDL_Texture* selector;
	SDL_Texture* text;
	SDL_Texture* textoNPC;

	int selectorIterator;
	b2Vec2 selectorPositions[4] = { b2Vec2(232, 539), b2Vec2(639,539), b2Vec2(232,603), b2Vec2(639,603) };

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