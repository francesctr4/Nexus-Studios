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

	if (SString(parameters.attribute("type").as_string()) == SString("rogue"))
		type = NPC_Types::ROGUE;
	if (SString(parameters.attribute("type").as_string()) == SString("wizard"))
		type = NPC_Types::WIZARD;
	if (SString(parameters.attribute("type").as_string()) == SString("orc"))
		type = NPC_Types::ORC;

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
	dialogue = app->tex->Load("Assets/Textures/Dialogue.png");
	UIdialogue = app->tex->Load("Assets/Textures/DialogueUI.png");

	if (type == NPC_Types::ROGUE) npcIcon = app->tex->Load("Assets/Textures/RogueIcon.png");
	if (type == NPC_Types::WIZARD) npcIcon = app->tex->Load("Assets/Textures/WizardIcon.png");
	if (type == NPC_Types::ORC) npcIcon = app->tex->Load("Assets/Textures/OrcIcon.png");

	int width = 32;
	int height = 32;

	pbody = app->physics->CreateRectangle(position.x, position.y, width, height, bodyType::STATIC);

	npcSensor = app->physics->CreateCircleSensor(position.x, position.y, 40, bodyType::KINEMATIC, ColliderType::NPC_SENSOR);

	//pbody->listener = this;

	npcSensor->listener = this;

	currentAnimation = &idle_right;

	playerInteraction = false;

	dialogueActivated = false;

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

	if (playerInteraction) {

		app->render->DrawTexture(dialogue, position.x + 8, position.y - 25);

		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == KEY_DOWN) dialogueActivated = true;

	}

	if (dialogueActivated) {

		app->render->DrawTexture(UIdialogue, 202, 389);

		if (type == NPC_Types::ROGUE) app->render->DrawTexture(npcIcon, 876, 409);
		if (type == NPC_Types::WIZARD) app->render->DrawTexture(npcIcon, 869, 407);
		if (type == NPC_Types::ORC) app->render->DrawTexture(npcIcon, 863, 400);

	}

	return true;
}

bool NPC::CleanUp()
{
	return true;
}

void NPC::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");

		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");

		break;

	case ColliderType::PLAYER:
		LOG("Collision PLAYER");

		playerInteraction = true;

		break;

	}

}

void NPC::OnCollisionEnd(PhysBody* physA, PhysBody* physB) {

	playerInteraction = false;
	dialogueActivated = false;

}