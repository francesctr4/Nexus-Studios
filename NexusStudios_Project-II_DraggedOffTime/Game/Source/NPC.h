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
	PLAYER_SELECTOR,
	NPC

};

// NPC Types

enum class NPC_Types {

	ROGUE,
	WIWI,
	SKIPPY,
	JOVANI,
	UNKNOWN

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

	bool Awake() override;

	bool Start() override;

	bool Update() override;

	bool CleanUp() override;

	void OnCollision(PhysBody* physA, PhysBody* physB) override;

	void OnCollisionEnd(PhysBody* physA, PhysBody* physB) override;

	// Function to create the dialogues related to a given conversation

	void DialogueGenerator(Conversation conversation);

	void Death();

public:

	// NPC Conversations

	int dialogueIterator;

	Conversation firstConversation;
	Dialogue* firstDialogue;

	Conversation secondConversation;
	Dialogue* secondDialogue;

	Conversation thirdConversation;
	Dialogue* thirdDialogue;

	// Sample Text for Conversations

	SDL_Texture* playerSampleText;
	SDL_Texture* loremIpsum;

	// Dialogue UI

	SDL_Texture* dialogueUI_npc_medieval;
	SDL_Texture* dialogueUI_npc_prehistoric;
	SDL_Texture* dialogueUI_npc_cyberpunk;
	SDL_Texture* dialogueUI_npc_apocalypse;

	SDL_Texture* dialogueUI_player_medieval;
	SDL_Texture* dialogueUI_player_prehistoric;
	SDL_Texture* dialogueUI_player_cyberpunk;
	SDL_Texture* dialogueUI_player_apocalypse;

	// Dialogue Names

	SDL_Texture* name_npc;
	SDL_Texture* name_player;
	SDL_Texture* name_npc_transparent;
	SDL_Texture* name_player_transparent;

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
	SDL_Texture* interactButtonGamepad;

	// NPC Texture and Type

	SDL_Texture* texture;
	const char* texturePath;

	NPC_Types ntype;

	// NPC Physics

	PhysBody* pbody;
	PhysBody* npcSensor;

	// NPC Animation

	Animation* currentAnimation;
	Animation idle_right;

	uint openDialogue;
	uint closeDialogue;
	uint dialogueOptions;
	uint npcTalking;

	// Maps

	int npcMap;

	// Jovani Skins
	int skinIterator;

};