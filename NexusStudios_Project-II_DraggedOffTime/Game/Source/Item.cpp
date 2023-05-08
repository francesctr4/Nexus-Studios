#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");
}

Item::~Item() 
{

}

bool Item::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	audioPath = parameters.attribute("audiopath").as_string();

	if (SString(parameters.attribute("type").as_string()) == SString("Potion"))
	{
		type = ItemType::POTION;
		ctype = ColliderType::ITEM_POTION;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Mango"))
	{
		type = ItemType::MANGO;
		ctype = ColliderType::ITEM_MANGO;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Gem"))
	{
		type = ItemType::GEM;
		ctype = ColliderType::ITEM_GEM;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Battery"))
	{
		type = ItemType::BATTERY;
		ctype = ColliderType::ITEM_BATTERY;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("Item_5"))
		type = ItemType::ITEM_5;

	if (SString(parameters.attribute("type").as_string()) == SString("Item_6"))
		type = ItemType::ITEM_6;

	return true;
}

bool Item::Start() {

	texture = app->tex->Load(texturePath);

	int width = 16;
	int height = 16;

	pbody = app->physics->CreateRectangleSensor(position.x, position.y, width, height, bodyType::KINEMATIC, ctype);
	pbody->listener = this;

	return true;
}

bool Item::Update()
{
	b2Transform transform = pbody->body->GetTransform();
	b2Vec2 pos = transform.p;

	position.x = METERS_TO_PIXELS(pos.x) - 8;
	position.y = METERS_TO_PIXELS(pos.y) - 8;

	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

bool Item::CleanUp()
{
	return true;
}

void Item::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
		case ColliderType::PLAYER: 
		{
			LOG("Collision PLAYER");

			Disable();
			pbody->body->DestroyFixture(pbody->body->GetFixtureList());

			break;
		}

	}

}