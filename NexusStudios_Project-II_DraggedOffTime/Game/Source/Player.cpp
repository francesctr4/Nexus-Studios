#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "FadeToBlack.h"
#include "Point.h"
#include "Physics.h"
#include "SceneBattle.h"
#include <iostream>

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	// Initialize Player parameters from XML
	
	texturePath = parameters.attribute("texturepath").as_string();
	texturePath2 = parameters.attribute("texturepath2").as_string();

	for (int i = 0; i < 4; i++) {

		idle_right.PushBack({ 32 * (0 + i), 32 * 0, 32, 32 });

	}
	idle_right.loop = true;
	idle_right.speed = 0.06f;

	return true;
}

bool Player::Start() {
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	//initilize textures.
	texture = app->tex->Load(texturePath);
	texture2 = app->tex->Load(texturePath2);

	// Add physics to the player.
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);

	// Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method.
	pbody->listener = this;

	// Assign collider type.
	pbody->ctype = ColliderType::PLAYER;

	currentAnimation = &idle_right;

	godMode = false;

	textureChange = false;

	return true;
}

bool Player::Update()
{
	// Add physics to the player and update player position using physics.
	
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y);

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) godMode = !godMode;

	speed = 5;

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, -speed);
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, speed);
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) vel = b2Vec2(-speed, -GRAVITY_Y);
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) vel = b2Vec2(speed, -GRAVITY_Y);

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

	if (godMode && app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) textureChange = !textureChange;

	if (!textureChange) {

		app->sceneBattle->selected_player = 0;
		app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	}

	else {

		app->sceneBattle->selected_player = 1;
		app->render->DrawTexture(texture2, position.x, position.y, &playerRect);

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

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	

}

void Player::Death()
{
	

}
