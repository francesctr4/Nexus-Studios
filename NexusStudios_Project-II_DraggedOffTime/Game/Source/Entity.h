#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"
#include "Input.h"
#include "Render.h"

struct Collider;

enum class EntityType
{
	PLAYER,
	ENEMY,
	ITEM,
	NPC,
	UNKNOWN
};

class Entity
{
public:

	explicit Entity(EntityType type) : type(type), active(true), aparicion(NULL) {}

	virtual bool Awake()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Update()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&)
	{
		return true;
	}

	void Entity::Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
		else {
			return;
		}
	}

	void Entity::Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
		else {
			return;
		}
	}

	virtual void OnCollision(PhysBody* c1, PhysBody* c2) {
	
	};

	virtual void OnCollisionEnd(PhysBody* c1, PhysBody* c2) {

	};

public:

	SString name;
	EntityType type;
	bool active = true;
	pugi::xml_node parameters;

	// Possible properties, it depends on how generic we
	// want our Entity class, maybe it's not renderable...
	iPoint position;     
	int aparicion;
	bool renderable = true;
};

#endif // __ENTITY_H__
