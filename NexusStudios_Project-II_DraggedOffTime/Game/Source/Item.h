#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

enum class ItemType {

	POTION,
	MANGO,
	GEM,
	BATTERY,
	ITEM_5,
	ITEM_6,
	TELEPORT_JOVANI,
	TELEPORT_COFRE

};

class Item : public Entity
{
public:

	Item();
	virtual ~Item();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:

	bool isPicked = false;

private:

	SDL_Texture* texture;
	const char* texturePath;
	const char* audioPath;

	PhysBody* pbody;
	ItemType type;
	ColliderType ctype;

	Animation idle;
	Animation* currentAnimation;

};

#endif // __ITEM_H__