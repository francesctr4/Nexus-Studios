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
#include "Infierno.h"
#include "Physics.h"
#include "SceneBattle.h"
#include "SceneGameplay.h"
#include <iostream>

#define SPEED_VALUE 5

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() 
{

}

bool Player::Awake() {

	// Initialize Player parameters from XML

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	texturePath = parameters.attribute("texturepath").as_string();
	texturePath2 = parameters.attribute("texturepath2").as_string();
	texturePath3 = parameters.attribute("texturepath3").as_string();
	texturePath4 = parameters.attribute("texturepath4").as_string();

	// Player animations

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

	playerStats[0] = {1,0,200,12,7,5,25};
	playerStats[1] = {1,0,200,20,5,10,15};
	playerStats[2] = {1,0,200,15,10,7,15};
	playerStats[3] = {1,0,200,10,12,2,20};

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

	levelUp = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/LevelUp.wav");

	speedValue = SPEED_VALUE;

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
	
	// God Mode Management

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) godMode = !godMode;

	if (godMode)
	{

		speedValue = SPEED_VALUE * 2;

	}
	else {

		speedValue = SPEED_VALUE;

	}

	// Player Movement Management

	if (!app->sceneGameplay->pause.showPause && 
		!app->sceneGameplay->pause.showSettings &&
		!app->sceneGameplay->featureMenu.statsEnabled && 
		!app->sceneGameplay->npcs.at(0)->dialogueActivated && 
		!app->sceneGameplay->npcs.at(1)->dialogueActivated && 
		!app->sceneGameplay->npcs.at(2)->dialogueActivated) {

		if (app->input->activeControllers.Count()) {

			GamepadMovementManagement();

		}
		else {

			KeyboardMovementManagement();

		}

	}
	else {

		vel = b2Vec2(0, 0);

		idleDirection ? currentAnimation = &idle_left : currentAnimation = &idle_right;

	}
		
	// Set the velocity of the pbody of the player.
	pbody->body->SetLinearVelocity(vel);

	// Update player position in pixels.
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	// Draw player texture according to animation and selected player

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

	// Player Teleport
	
	if (newPos.t == true)
	{
		b2Vec2 resetPos = b2Vec2(PIXEL_TO_METERS(newPos.posX), PIXEL_TO_METERS(newPos.posY));
		pbody->body->SetTransform(resetPos, 0);

		newPos.t = false;
	}

	// Player Progession (Levels) 

	// XP Required to go from lvl 1 to lvl 100: 165330

	if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {

		AddXP(500, 0);

	}

	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {

		AddXP(500, 1);

	}

	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {

		AddXP(500, 2);

	}

	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {

		AddXP(500, 3);

	}

	PlayerLevelManagement();

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

	//Box Puzzle

	app->sceneGameplay->puzzle2.top_collision1 = false;
	app->sceneGameplay->puzzle2.bottom_collision1 = false;

	app->sceneGameplay->puzzle2.top_collision2 = false;
	app->sceneGameplay->puzzle2.bottom_collision2 = false;

	app->sceneGameplay->puzzle2.top_collision3 = false;
	app->sceneGameplay->puzzle2.bottom_collision3 = false;

	app->sceneGameplay->puzzle2.top_collision4 = false;
	app->sceneGameplay->puzzle2.bottom_collision4 = false;

	app->sceneGameplay->puzzle2.top_collision5 = false;
	app->sceneGameplay->puzzle2.bottom_collision5 = false;
}

void Player::KeyboardMovementManagement()
{
	// Player Idle Management

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE &&
		app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
		app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
		app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {

		idleDirection ? currentAnimation = &idle_left : currentAnimation = &idle_right;

		vel = b2Vec2(0, 0);

	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE &&
		app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE) {

		speedY = 0;

	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
		app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {

		speedX = 0;

	}

	// Movement Up

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {

		speedY = -speedValue;

		idleDirection ? currentAnimation = &walk_left : currentAnimation = &walk_right;

	}

	// Movement Down

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {

		speedY = speedValue;

		idleDirection ? currentAnimation = &walk_left : currentAnimation = &walk_right;

	}

	// Movement Left

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

		speedX = -speedValue;
		currentAnimation = &walk_left;
		idleDirection = true;

	}

	// Movement Right

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

		speedX = speedValue;
		currentAnimation = &walk_right;
		idleDirection = false;

	}

	// Speed update

	if (app->input->GetKey(SDL_SCANCODE_W) != KEY_IDLE ||
		app->input->GetKey(SDL_SCANCODE_A) != KEY_IDLE ||
		app->input->GetKey(SDL_SCANCODE_S) != KEY_IDLE ||
		app->input->GetKey(SDL_SCANCODE_D) != KEY_IDLE) {

		vel = b2Vec2(speedX, speedY);

	}

}

void Player::GamepadMovementManagement()
{
	// Player Idle Management

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) == 0 &&
		app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) == 0) {

		idleDirection ? currentAnimation = &idle_left : currentAnimation = &idle_right;

		vel = b2Vec2(0, 0);

	}

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) == 0) {

		speedY = 0;

	}

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) == 0) {

		speedX = 0;

	}

	// Movement Up

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) < 0) {

		speedY = -speedValue;

		idleDirection ? currentAnimation = &walk_left : currentAnimation = &walk_right;

	}

	// Movement Down

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) > 0) {

		speedY = speedValue;

		idleDirection ? currentAnimation = &walk_left : currentAnimation = &walk_right;

	}

	// Movement Left

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) < 0) {

		speedX = -speedValue;
		currentAnimation = &walk_left;
		idleDirection = true;

	}

	// Movement Right

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) > 0) {

		speedX = speedValue;
		currentAnimation = &walk_right;
		idleDirection = false;

	}

	// Speed update

	if (app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) != 0 ||
		app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) != 0) {

		vel = b2Vec2(speedX, speedY);

	}

}

void Player::AddXP(int xp, int playerIndex)
{
	playerStats[playerIndex].currentXP += xp;
}

void Player::PlayerLevelManagement()
{
	for (int i = 0; i < 4; i++) {

		fillPercentage[i] = static_cast<float>(playerStats[i].currentXP) / playerStats[i].next;
		fillWidth[i] = static_cast<int>(fillPercentage[i] * 243);

		xpAccumulatedRect[i].w = fillWidth[i];

		if (playerStats[i].currentXP == playerStats[i].next) {

			playerStats[i].currentXP = 0;

			playerStats[i].level++;
			playerStats[i].hp += 3;
			playerStats[i].atk += 3;
			playerStats[i].def += 3;
			playerStats[i].ap += 3;
			playerStats[i].next += 30;

			//app->audio->PlayFx(levelUp);

		}
		else if (playerStats[i].currentXP > playerStats[i].next) {

			int xpExcess = playerStats[i].currentXP - playerStats[i].next;

			playerStats[i].currentXP = xpExcess;

			playerStats[i].level++;
			playerStats[i].hp += 3;
			playerStats[i].atk += 3;
			playerStats[i].def += 3;
			playerStats[i].ap += 3;
			playerStats[i].next += 30;

			//app->audio->PlayFx(levelUp);

		}

	}

}

void Player::TeleportCofre()
{
}

void Player::TeleportJovani()
{
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {
	
	switch (physB->ctype)
	{
	case ColliderType::SENSOR_COIN_PUZZLE3:

		app->sceneGameplay->puzzle3.coinPicked = true;
		app->audio->PlayFx(app->sceneGameplay->puzzle3.coinFX);

		break;

	case ColliderType::SENSOR_TOP_BOX1_PUZZLE2:

		app->sceneGameplay->puzzle2.top_collision1 = true;

		break;

	case ColliderType::SENSOR_BOTTOM_BOX1_PUZZLE2:

		app->sceneGameplay->puzzle2.bottom_collision1 = true;

		break;

	case ColliderType::SENSOR_TOP_BOX2_PUZZLE2:

		app->sceneGameplay->puzzle2.top_collision2 = true;

		break;

	case ColliderType::SENSOR_BOTTOM_BOX2_PUZZLE2:

		app->sceneGameplay->puzzle2.bottom_collision2 = true;

		break;

	case ColliderType::SENSOR_TOP_BOX3_PUZZLE2:

		app->sceneGameplay->puzzle2.top_collision3 = true;

		break;

	case ColliderType::SENSOR_BOTTOM_BOX3_PUZZLE2:

		app->sceneGameplay->puzzle2.bottom_collision3 = true;

		break;

	case ColliderType::SENSOR_TOP_BOX4_PUZZLE2:

		app->sceneGameplay->puzzle2.top_collision4 = true;

		break;

	case ColliderType::SENSOR_BOTTOM_BOX4_PUZZLE2:

		app->sceneGameplay->puzzle2.bottom_collision4 = true;

		break;

	case ColliderType::SENSOR_TOP_BOX5_PUZZLE2:

		app->sceneGameplay->puzzle2.top_collision5 = true;

		break;

	case ColliderType::SENSOR_BOTTOM_BOX5_PUZZLE2:

		app->sceneGameplay->puzzle2.bottom_collision5 = true;

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
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_0);
		app->sceneGameplay->trigger_3 = true;

		app->map->CleanUp();
		app->map->actualmap = 1;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(650, 671);

		//Move Npcs Map_1
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(220) }, 0);

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
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_1);
		app->map->CleanUp();
		app->map->actualmap = 2;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(1265, 560);
		
		//Move Npcs Map_2
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(956),PIXEL_TO_METERS(220) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(956),PIXEL_TO_METERS(220) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		//Move Enemies Map_2
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(490),PIXEL_TO_METERS(400) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(490),PIXEL_TO_METERS(400) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		
		break;

	case 2:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_2);
		app->map->CleanUp();
		app->map->actualmap = 3;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(1255, 106);
		
		//Move Npcs Map_3
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


		//Move Enemies Map_3
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(700),PIXEL_TO_METERS(500) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(700),PIXEL_TO_METERS(500) }, 0);
		
		break;
	case 3:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_3);
		app->map->CleanUp();
		app->map->actualmap = 6;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(10, 300);
		
		//Move Npcs Map_3
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(450),PIXEL_TO_METERS(350) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(450),PIXEL_TO_METERS(350) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		//Move Enemies Map_3
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(275) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(275) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		break;
	case 4:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_4);
		app->map->CleanUp();
		app->map->actualmap = 5;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(640, 700);
		
		//Move Npcs Map_2
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);

		//Move Enemies Map_2
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		break;
	case 5:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_5);
		app->map->CleanUp();
		app->map->actualmap = 0;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(200, 671);
		
		//Move Npcs Map_2
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);

		//Move Enemies Map_2
		//Move Enemies Map_1
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(95),PIXEL_TO_METERS(555) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(95),PIXEL_TO_METERS(555) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		break;
	case 6:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.Tp_Puzzle1);
		app->map->CleanUp();
		app->map->actualmap = 7;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(12, 600);
		
		//Move Npcs Map_3
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(550) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(550) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		//Move Enemies Map_3
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(600),PIXEL_TO_METERS(200) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(600),PIXEL_TO_METERS(200) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		
		break;
	case 7:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.Tp_Puzzle2);
		app->map->CleanUp();
		app->map->actualmap = 8;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(640, 700);
		
		//Move Npcs Map_3
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(642),PIXEL_TO_METERS(600) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(642),PIXEL_TO_METERS(600) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		//Move Enemies Map_3
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		break;
	
	case 8:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.Tp_Puzzle3);
		app->map->CleanUp();
		app->map->actualmap = 4;
		app->map->Load();
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(637, 700);
		
		//Move Npcs Map_3
		app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		//Move Enemies Map_3
		app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(735),PIXEL_TO_METERS(310) }, 0);
		app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(735),PIXEL_TO_METERS(310) }, 0);

		app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		break;
	
	default:
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
