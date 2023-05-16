#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Map.h"
#include "Log.h"
#include "FadeToBlack.h"
#include "Point.h"
#include "Physics.h"
#include "SceneBattle.h"
#include "SceneGameplay.h"
#include <iostream>

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	// Initialize Player parameters from XML
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	texturePath = parameters.attribute("texturepath").as_string();
	texturePath2 = parameters.attribute("texturepath2").as_string();
	texturePath3 = parameters.attribute("texturepath3").as_string();
	texturePath4 = parameters.attribute("texturepath4").as_string();

	for (int i = 0; i < 4; i++) {

		idle_right.PushBack({ 32 * (0 + i), 32 * 0, 32, 32 });

	}
	idle_right.loop = true;
	idle_right.speed = 0.06f;

	for (int i = 0; i < 4; i++) {

		idle_left.PushBack({ 32 * (0 + i), 32 * 1, 32, 32 });

	}
	idle_left.loop = true;
	idle_left.speed = 0.06f;

	for (int i = 0; i < 4; i++) {

		walk_right.PushBack({ 32 * (0 + i), 32 * 2, 32, 32 });

	}
	walk_right.loop = true;
	walk_right.speed = 0.1f;

	for (int i = 0; i < 4; i++) {

		walk_left.PushBack({ 32 * (0 + i), 32 * 3, 32, 32 });

	}
	walk_left.loop = true;
	walk_left.speed = 0.1f;

	return true;
}

bool Player::Start() {
	
	//initilize textures.
	texture[0] = app->tex->Load(texturePath);
	texture[1] = app->tex->Load(texturePath2);
	texture[2] = app->tex->Load(texturePath3);
	texture[3] = app->tex->Load(texturePath4);

	playerStats[0] = {1,200,12,7,5,25};
	playerStats[1] = {1,200,20,5,10,15};
	playerStats[2] = {1,200,15,10,7,15};
	playerStats[3] = {1,200,10,12,2,20};

	// Add physics to the player.
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);

	// Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method.
	pbody->listener = this;

	// Assign collider type.
	pbody->ctype = ColliderType::PLAYER;

	currentAnimation = &idle_right;

	godMode = false;

	playerChange = 0;

	itemCollectedFx = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/Item.wav");
	
	idleDirection = false;

	changeFX = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/ChangePlayer.wav");

	return true;
}

bool Player::Update()
{

	if (executeTeleportCofre) {
		TeleportCofre();
		executeTeleportCofre = false;
	}
	if (executeTeleportInfierno) {
		TeleportInfierno();
		executeTeleportInfierno = false;
	}
	if (executeTeleportMedieval) {
		TeleportCofre();
		executeTeleportMedieval = false;
	}
	if (executeTeleportPrehistoria) {
		TeleportCofre();
		executeTeleportPrehistoria = false;
	}
	if (executeTeleportFuturo) {
		TeleportCofre();
		executeTeleportFuturo = false;
	}




	// Add physics to the player and update player position using physics.
	
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y);
	
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) godMode = !godMode;

	speed = 5;

	if (godMode)
	{
		speed = 10;
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && 
		app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
		app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
		app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {

		if (idleDirection) {

			currentAnimation = &idle_left;

		}
		else {

			currentAnimation = &idle_right;

		}
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {

		vel = b2Vec2(GRAVITY_X, -speed);

		if (idleDirection) {

			currentAnimation = &walk_left;

		}
		else {

			currentAnimation = &walk_right;

		}

	}
		
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {

		vel = b2Vec2(GRAVITY_X, speed);

		if (idleDirection) {

			currentAnimation = &walk_left;

		}
		else {

			currentAnimation = &walk_right;

		}

	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

		vel = b2Vec2(-speed, -GRAVITY_Y);
		currentAnimation = &walk_left;
		idleDirection = true;

	}
		
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

		vel = b2Vec2(speed, -GRAVITY_Y);
		currentAnimation = &walk_right;
		idleDirection = false;

	}
		
	if (app->input->activeControllers.Count()) {

		if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) < 0) vel = b2Vec2(GRAVITY_X, -speed);
		if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) > 0) vel = b2Vec2(GRAVITY_X, speed);
		if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) < 0) vel = b2Vec2(-speed, -GRAVITY_Y);
		if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) > 0) vel = b2Vec2(speed, -GRAVITY_Y);

	}

	// Set the velocity of the pbody of the player.
	pbody->body->SetLinearVelocity(vel);

	// Update player position in pixels.
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	
	// Draw player texture.

	currentAnimation->Update();

	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();

	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {

		app->audio->PlayFx(changeFX);

		if (playerChange < 3) {

			playerChange++;

		}
		else {

			playerChange = 0;

		}

	}

	app->sceneBattle->selected_player = playerChange;
	app->render->DrawTexture(texture[playerChange], position.x, position.y, &playerRect);

	
	if (newPos.t == true)
	{
		b2Vec2 resetPos = b2Vec2(PIXEL_TO_METERS(newPos.posX), PIXEL_TO_METERS(newPos.posY));
		pbody->body->SetTransform(resetPos, 0);

		newPos.t = false;
	}

	return true;
}

void Player::Teleport(int x, int y)
{
	newPos.posX = x;
	newPos.posY = y;
	newPos.t = true;
}

bool Player::CleanUp()
{

	return true;
}

void Player::OnCollisionEnd(PhysBody* physA, PhysBody* physB) {

	//app->sceneGameplay->puzzles.sensor1Pressed = false;
	app->sceneGameplay->puzzle2.top_collision = false;
	app->sceneGameplay->puzzle2.bottom_collision = false;

}

void Player::TeleportCofre()
{
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {
	
	switch (physB->ctype)
	{
	case ColliderType::SENSOR_COIN_PUZZLE3:

		app->sceneGameplay->puzzle3.coinPicked = true;

		break;

	case ColliderType::SENSOR_TOP_BOX_PUZZLE2:

		app->sceneGameplay->puzzle2.top_collision = true;

		break;

	case ColliderType::SENSOR_BOTTOM_BOX_PUZZLE2:

		app->sceneGameplay->puzzle2.bottom_collision = true;

		break;

	case ColliderType::SENSOR_CLOCK_PUZZLE3:

		app->sceneGameplay->puzzle3.clockPicked = true;

		break;

	case ColliderType::SENSOR_BUTTON1_PUZZLE1:

		if (!app->sceneGameplay->puzzle1.sensor1Pressed) {

			app->sceneGameplay->puzzle1.order.push_back(1);
			app->audio->PlayFx(app->sceneGameplay->puzzle1.buttonPressed);
			app->sceneGameplay->puzzle1.sensor1Pressed = true;

		}
		
		break;

	case ColliderType::SENSOR_BUTTON2_PUZZLE1:

		if (!app->sceneGameplay->puzzle1.sensor2Pressed) {

			app->sceneGameplay->puzzle1.order.push_back(2);
			app->audio->PlayFx(app->sceneGameplay->puzzle1.buttonPressed);
			app->sceneGameplay->puzzle1.sensor2Pressed = true;

		}
		
		break;

	case ColliderType::SENSOR_BUTTON3_PUZZLE1:

		if (!app->sceneGameplay->puzzle1.sensor3Pressed) {

			app->sceneGameplay->puzzle1.order.push_back(3);
			app->audio->PlayFx(app->sceneGameplay->puzzle1.buttonPressed);
			app->sceneGameplay->puzzle1.sensor3Pressed = true;

		}

		break;

	case ColliderType::SENSOR_BUTTON4_PUZZLE1:

		if (!app->sceneGameplay->puzzle1.sensor4Pressed) {

			app->sceneGameplay->puzzle1.order.push_back(4);
			app->audio->PlayFx(app->sceneGameplay->puzzle1.buttonPressed);
			app->sceneGameplay->puzzle1.sensor4Pressed = true;

		}

		break;

	case ColliderType::ITEM_POTION:

		app->audio->PlayFx(itemCollectedFx);

		break;

	case ColliderType::ITEM_BATTERY:

		app->audio->PlayFx(itemCollectedFx);

		break;

	case ColliderType::ITEM_GEM:

		app->audio->PlayFx(itemCollectedFx);

		break;

	case ColliderType::ITEM_MANGO:

		app->audio->PlayFx(itemCollectedFx);

		break;

	case ColliderType::TELEPORT_COFRE:
		executeTeleportCofre = true;

		break;
	case ColliderType::TELEPORT_FUTURO:
		executeTeleportFuturo = true;

		break;
	case ColliderType::TELEPORT_INFIERNO:
		executeTeleportInfierno = true;

		break;
	case ColliderType::TELEPORT_MEDIEVAL:
		executeTeleportMedieval = true;

		break;
	case ColliderType::TELEPORT_PREHISTORIA:
		executeTeleportPrehistoria = true;
		break;

	case ColliderType::TELEPORT_JOVANI:
		executeTeleportJovani = true;
		break;
		
	}
	

}

void Player::TeleportInfierno() {
	//Quest
	switch (app->map->actualmap)
	{
	case 0:
		app->physics->DestroyBody(app->sceneGameplay->TP_Infierno_1);
		app->sceneGameplay->trigger_3 = true;

		app->map->CleanUp();
		app->map->actualmap = 1;
		app->map->Load();
		app->sceneGameplay->map_selector = false;
		app->sceneGameplay->player->Teleport(650, 671);

		//Move Npcs Map_1
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

		//Move Enemies Map_1
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		break;
	case 1:
		app->physics->DestroyBody(app->sceneGameplay->TP_Infierno_2);
		app->map->CleanUp();
		app->map->actualmap = 2;
		bool retLoad = app->map->Load();
		app->sceneGameplay->map_selector = false;
		app->sceneGameplay->player->Teleport(650, 700);

		//Move Npcs Map_1
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

		//Move Enemies Map_1
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		break;
	}

}

void Player::TeleportPrehistoria()
{
}

void Player::TeleportFuturo()
{
}

void Player::TeleportMedieval()
{
}

void Player::Death()
{
	

}
