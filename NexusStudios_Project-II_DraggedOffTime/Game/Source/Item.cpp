#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "SceneGameplay.h"
#include "Inventory.h"

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");

	texture = nullptr;
	icon = nullptr;

	iconPath = nullptr;
	texturePath = nullptr;

	pbody = nullptr;
	itype = ItemType::UNKNOWN;
	ctype = ColliderType::UNKNOWN;

	currentAnimation = nullptr;

	itemMap = NULL;

}

Item::~Item() 
{

}

bool Item::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	iconPath = parameters.attribute("iconpath").as_string();
	texturePath = parameters.attribute("texturepath").as_string();
	itemMap = parameters.attribute("map").as_int();
	aparicion = itemMap;

	if (SString(parameters.attribute("type").as_string()) == SString("Potion"))
	{
		itype = ItemType::POTION;
		ctype = ColliderType::ITEM_POTION;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Mango"))
	{
		itype = ItemType::MANGO;
		ctype = ColliderType::ITEM_MANGO;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Gem"))
	{
		itype = ItemType::GEM;
		ctype = ColliderType::ITEM_GEM;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Battery"))
	{
		itype = ItemType::BATTERY;
		ctype = ColliderType::ITEM_BATTERY;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Teleport_Jovani")) 
	{
		itype = ItemType::TELEPORT_JOVANI;
		ctype = ColliderType::TELEPORT_JOVANI;
	}
		

	if (SString(parameters.attribute("type").as_string()) == SString("Teleport_Cofre")) 
	{
		itype = ItemType::TELEPORT_COFRE;
		ctype = ColliderType::TELEPORT_COFRE;
	}

	for (int i = 0; i < 6; i++) {

		idle.PushBack({ 16 * (0 + i), 18 * 0, 16, 18 });

	}
	idle.loop = true;
	idle.speed = 0.1f;

	return true;
}

bool Item::Start() {

	texture = app->tex->Load(texturePath);
	icon = app->tex->Load(iconPath);

	int width = 16;
	int height = 16;

	if (itype == ItemType::TELEPORT_COFRE || itype == ItemType::TELEPORT_JOVANI) {

		pbody = app->physics->CreateRectangleSensor(position.x, position.y, 40, 20, bodyType::KINEMATIC, ctype);

	}
	else {

		pbody = app->physics->CreateRectangleSensor(position.x, position.y, width, height, bodyType::KINEMATIC, ctype);

	}

	pbody->listener = this;

	currentAnimation = &idle;

	return true;
}

bool Item::Update()
{
	b2Transform transform = pbody->body->GetTransform();
	b2Vec2 pos = transform.p;

	position.x = METERS_TO_PIXELS(pos.x) - 8;
	position.y = METERS_TO_PIXELS(pos.y) - 8;

	currentAnimation->Update();

	SDL_Rect itemRect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x, position.y, &itemRect);

	return true;
}

bool Item::CleanUp()
{
	app->physics->DestroyBody(pbody);
	app->tex->UnLoad(texture);
	return true;
}

void Item::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		{
		
			isPicked = true;
			if (itype == ItemType::TELEPORT_COFRE)
			{

			}
			else
			{ 
				Collected();
				
			}
			
			if (physA->ctype == ColliderType::ITEM_BATTERY || physA->ctype == ColliderType::ITEM_GEM || physA->ctype == ColliderType::ITEM_MANGO || physA->ctype == ColliderType::ITEM_POTION)
			{
				app->sceneGameplay->trigger_2++;
			}
			
			app->sceneGameplay->featureMenu.inventoryManager.AddItem(*this);
			break;
		}

	}

}

void Item::OnCollisionEnd(PhysBody* physA, PhysBody* physB)
{

	

}

void Item::Restart(ItemType type, ColliderType ctype, int x, int y, std::string iconPath, std::string texturePath)
{
	this->itype = type;
	this->ctype = ctype;
	this->position.x = x;
	this->position.y = y;
	this->iconPath = iconPath.c_str();
	this->texturePath = texturePath.c_str();

	texture = app->tex->Load(this->texturePath);
	icon = app->tex->Load(this->iconPath);

	int width = 16;
	int height = 16;

	if (type == ItemType::TELEPORT_COFRE || type == ItemType::TELEPORT_JOVANI) {

		pbody = app->physics->CreateRectangleSensor(position.x, position.y, 40, 20, bodyType::KINEMATIC, ctype);

	}
	else {

		pbody = app->physics->CreateRectangleSensor(position.x, position.y, width, height, bodyType::KINEMATIC, ctype);

	}

	pbody->listener = this;

	currentAnimation = &idle;

}

void Item::Collected()
{
	active = false;
	pbody->body->SetActive(false);
	isPicked = true;
}
