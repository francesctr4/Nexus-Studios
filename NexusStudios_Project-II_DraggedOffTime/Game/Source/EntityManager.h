#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "List.h"

class EntityManager : public Module
{
public:

	explicit EntityManager(bool startEnabled);

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node&) override;

	// Called after Awake
	bool Start() override;

	// Called every frame
	bool Update(float dt) override;

	// Called before quitting
	bool CleanUp() override;

	// Additional methods
	Entity* CreateEntity(EntityType type);

	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) override;

public:

	List<Entity*> entities;

	int playerX;
	int playerY;

};

#endif // __ENTITYMANAGER_H__
