#pragma once

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "Physics.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

// Dialogue Types

enum class DialogueType {

	PLAYER,
	NPC

};

// NPC Types

enum class NPC_Types {

	ROGUE,
	WIZARD,
	ORC

};

// Struct Dialogue represents each piece of text

struct Dialogue {

	SDL_Texture* text;
	DialogueType whoIsTalking;

};

// Struct Conversation represents a set of dialogues

struct Conversation {

	int id;
	int size;
	Dialogue* dialogues = new Dialogue[size];

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

	// Function to create the dialogues related to a given conversation

	void DialogueGenerator(Conversation conversation);

	void Death();

private:

	// NPC Conversations

	int dialogueIterator;

	Conversation firstConversation;
	Dialogue* firstDialogue;

	Conversation secondConversation;
	Dialogue* secondDialogue;

	// Sample Text for Conversations

	SDL_Texture* playerSampleText;
	SDL_Texture* loremIpsum;

	// Dialogue UI

	SDL_Texture* dialogueUI_npc;
	SDL_Texture* dialogueUI_player;

	// Player Dialogue Selector

	int selectorIterator;
	b2Vec2 selectorPositions[4] = { b2Vec2(232, 539), b2Vec2(639,539), b2Vec2(232,603), b2Vec2(639,603) };

	SDL_Texture* selector;

	// NPC Dialogue Icon

	SDL_Texture* npcIcon;
	SDL_Texture* npcIcon_Transparent;

	// NPC Sensor Booleans and Texture

	bool playerInteraction;
	bool dialogueActivated;

	SDL_Texture* interactButton;

	// NPC Texture and Type

	SDL_Texture* texture;
	const char* texturePath;

	NPC_Types type;

	// NPC Physics

	PhysBody* pbody;
	PhysBody* npcSensor;

	// NPC Animation

	Animation* currentAnimation;
	Animation idle_right;


};