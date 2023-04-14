#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
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

	return true;
}

bool Player::Start() {

	//initilize textures.
	texture = app->tex->Load(texturePath);
	SDL_Rect prova;
	prova.x = position.x;
	prova.y = position.y;
	prova.w = 30;
	prova.h = 30;
	app->render->DrawRectangle(prova, 255, 255, 255, 0);

	if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
	{
		app->render->camera.x = position.x;
		app->render->camera.y = position.y;
	}
	// Add physics to the player.
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::KINEMATIC);

	// Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method.
	pbody->listener = this;

	// Assign collider type.
	pbody->ctype = ColliderType::PLAYER;

	return true;
}

bool Player::Update()
{
	// Add physics to the player and update player position using physics.
	int speed = 5;
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y);

	// TODO 2 - Split Screen: manage players movement according to active cameras, input keys and speed used.
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT /* || app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) > 0*/) vel = b2Vec2(GRAVITY_X, -speed);
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT /* || app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_y, 10000, 2) < 0*/) vel = b2Vec2(GRAVITY_X, speed);
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT /* || app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) < 0*/) vel = b2Vec2(-speed, -GRAVITY_Y);
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT /* || app->input->reduce_val(SDL_IsGameController(0), app->input->controllers[0].j1_x, 10000, 2) > 0*/) vel = b2Vec2(speed, -GRAVITY_Y);

	// Set the velocity of the pbody of the player.
	pbody->body->SetLinearVelocity(vel);

	// Update player position in pixels.
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	// Draw player texture.
	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

bool Player::CleanUp()
{

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	

}