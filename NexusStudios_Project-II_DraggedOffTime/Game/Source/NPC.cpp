#include "NPC.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

NPC::NPC() : Entity(EntityType::NPC)
{
	name.Create("npc");
}

NPC::~NPC() {}

bool NPC::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	for (int i = 0; i < 4; i++) {

		idle_right.PushBack({ 32 * (0 + i), 32 * 0, 32, 32 });

	}
	idle_right.loop = true;
	idle_right.speed = 0.06f;

	return true;
}

bool NPC::Start() {

	texture = app->tex->Load(texturePath);

	int width = 32;
	int height = 32;

	pbody = app->physics->CreateRectangle(position.x, position.y, width, height, bodyType::STATIC);

	pbody->listener = this;

	currentAnimation = &idle_right;

	return true;
}

bool NPC::Update()
{

	b2Transform transform = pbody->body->GetTransform();
	b2Vec2 pos = transform.p;

	position.x = METERS_TO_PIXELS(pos.x) - 16;
	position.y = METERS_TO_PIXELS(pos.y) - 18;

	currentAnimation->Update();

	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	return true;
}

bool NPC::CleanUp()
{
	return true;
}

void NPC::OnCollision(PhysBody* physA, PhysBody* physB) {



}