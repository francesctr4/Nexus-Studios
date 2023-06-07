#include "EntityManager.h"
#include "Player.h"
#include "Item.h"
#include "NPC.h"
#include "Enemy.h"
#include "App.h"
#include "Textures.h"
#include "Physics.h"
#include "Input.h"
#include "SceneGameplay.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("entitymanager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	bool ret = true;

	//Iterates over the entities and calls the Awake
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Awake();
	}

	return ret;
}

bool EntityManager::Start() {

	bool ret = true; 

	//Iterates over the entities and calls Start
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Start();
	}

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;
	
	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		RELEASE(item->data);
		item = item->prev;
	}

	entities.Clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type)
{
	OPTICK_EVENT();
	Entity* entity = nullptr; 

	// Instantiate entity according to the type and add the new entoty it to the list of Entities

	switch (type)
	{

	case EntityType::PLAYER:
		entity = new Player();
		break;
		
	case EntityType::ITEM:
		entity = new Item();
		break;

	case EntityType::ENEMY:
		entity = new Enemy();
		break;

	case EntityType::NPC:
		entity = new NPC();
		break;

	default: 
		break;
	}

	// Created entities are added to the list
	AddEntity(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity)
		{
			item->data->CleanUp();
			RELEASE(item->data);
			entities.Del(item);
			break;
		}
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if ( entity != nullptr) entities.Add(entity);
	
}

bool EntityManager::Update(float dt)
{
	OPTICK_EVENT();
	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false)
		{
			continue;
		}

		ret = item->data->Update();
	}

	return ret;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	OPTICK_EVENT();

	// Load Player

	float x = data.child("player").attribute("x").as_int();
	float y = data.child("player").attribute("y").as_int();

	app->sceneGameplay->player->pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);

	// Load Enemies

	ListItem<Enemy*>* item;

	pugi::xml_node enemyNode = data.child("enemy");

	for (auto& item : app->sceneGameplay->enemies)
	{
		float x = enemyNode.attribute("x").as_int();
		float y = enemyNode.attribute("y").as_int();

		item->pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);

		enemyNode = enemyNode.next_sibling("enemy");

	}

	// Load Items

	ListItem<Item*>* it;

	for (pugi::xml_node itemNode = data.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		if (SString(itemNode.attribute("isPicked").as_string()) == SString("False")) {

			float x = itemNode.attribute("x").as_int();
			float y = itemNode.attribute("y").as_int();
			std::string iconPath = itemNode.attribute("iconpath").as_string();
			std::string texturePath = itemNode.attribute("texturepath").as_string();
			ItemType type;
			ColliderType ctype;

			if (SString(itemNode.attribute("type").as_string()) == SString("Potion"))
			{
				type = ItemType::POTION;
				ctype = ColliderType::ITEM_POTION;

				Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
				item->Restart(type, ctype, x, y, iconPath, texturePath);

				app->sceneGameplay->items.push_back(item);
			}
			else if (SString(itemNode.attribute("type").as_string()) == SString("Mango"))
			{
				type = ItemType::MANGO;
				ctype = ColliderType::ITEM_MANGO;

				Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
				item->Restart(type, ctype, x, y, iconPath, texturePath);

				app->sceneGameplay->items.push_back(item);

			}
			else if (SString(itemNode.attribute("type").as_string()) == SString("Gem"))
			{
				type = ItemType::GEM;
				ctype = ColliderType::ITEM_GEM;

				Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
				item->Restart(type, ctype, x, y, iconPath, texturePath);

				app->sceneGameplay->items.push_back(item);
			}
			else if (SString(itemNode.attribute("type").as_string()) == SString("Battery"))
			{
				type = ItemType::BATTERY;
				ctype = ColliderType::ITEM_BATTERY;

				Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
				item->Restart(type, ctype, x, y, iconPath, texturePath);

				app->sceneGameplay->items.push_back(item);
			}

			//it->pbody->body->SetTransform({ PIXEL_TO_METERS(x),PIXEL_TO_METERS(y) }, 0);

		}

	}

	return true;
}

bool EntityManager::SaveState(pugi::xml_node& data)
{
	OPTICK_EVENT();

	// Save Player

	pugi::xml_node player = data.append_child("player");

	player.append_attribute("x") = app->sceneGameplay->player->position.x + 16;
	player.append_attribute("y") = app->sceneGameplay->player->position.y + 16;

	playerX = app->sceneGameplay->player->position.x;
	playerY = app->sceneGameplay->player->position.y;

	// Save Enemies

	ListItem<Enemy*>* item;

	for (auto& item : app->sceneGameplay->enemies)
	{
		pugi::xml_node enemy = data.append_child("enemy");

		int x, y;
		item->pbody->GetPosition(x, y);

		switch (item->etype)
		{
		case EnemyType::DAMAGE:
			enemy.append_attribute("type") = "damage";
			break;
		case EnemyType::SUPPORT:
			enemy.append_attribute("type") = "support";
			break;
		case EnemyType::TANK:
			enemy.append_attribute("type") = "tank";
			break;
		case EnemyType::BOSS_MEDIEVAL:
			enemy.append_attribute("type") = "bossMedieval";
			break;
		case EnemyType::BOSS_PREHISTORIC:
			enemy.append_attribute("type") = "bossPrehistoric";
			break;
		case EnemyType::BOSS_CYBERPUNK:
			enemy.append_attribute("type") = "bossCyberpunk";
			break;
		case EnemyType::BOSS_APOCALYPSE:
			enemy.append_attribute("type") = "bossApocalypse";
			break;
		case EnemyType::UNKNOWN:
			break;
		default:
			break;
		}

		enemy.append_attribute("x") = x + 16;
		enemy.append_attribute("y") = y + 16;

		enemy.append_attribute("texturepath") = item->texturePath;
		enemy.append_attribute("battletexturepath") = item->texturePathBattle;

		enemy.append_attribute("map") = item->enemyMap;

		if (item->isAlive) {

			enemy.append_attribute("isAlive") = "True";

		}
		else {

			enemy.append_attribute("isAlive") = "False";

		}

	}

	// Save Items

	ListItem<Item*>* it;

	for (auto& it : app->sceneGameplay->items)
	{
		pugi::xml_node item = data.append_child("item");

		int x, y;
		it->pbody->GetPosition(x, y);
		
		switch (it->itype)
		{
		case ItemType::POTION:
			item.append_attribute("type") = "Potion";
			break;
		case ItemType::MANGO:
			item.append_attribute("type") = "Mango";
			break;
		case ItemType::GEM:
			item.append_attribute("type") = "Gem";
			break;
		case ItemType::BATTERY:
			item.append_attribute("type") = "Battery";
			break;
		case ItemType::ITEM_6:
			break;
		case ItemType::TELEPORT_JOVANI:
			break;
		case ItemType::TELEPORT_COFRE:
			break;
		default:
			break;
		}

		item.append_attribute("x") = x + 16;
		item.append_attribute("y") = y + 16;

		item.append_attribute("texturepath") = it->texturePath;
		item.append_attribute("iconpath") = it->iconPath;

		item.append_attribute("map") = it->itemMap;

		if (it->isPicked) {

			item.append_attribute("isPicked") = "True";

		}
		else {

			item.append_attribute("isPicked") = "False";

		}

	}

	return true;
}