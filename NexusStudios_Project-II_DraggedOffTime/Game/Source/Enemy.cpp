#include "Enemy.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "PathFinding.h"
#include "Map.h"
#include "FadeToBlack.h"
#include "SceneBattle.h"
#include "SceneGameplay.h"

#include <iostream>

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");
}

Enemy::~Enemy() {

}

bool Enemy::Awake() {

	if (SString(parameters.attribute("type").as_string()) == SString("damage")) {

		type = EnemyType::DAMAGE;
		hp = 5;
		atk = 10;
		def = 5;

	}

	if (SString(parameters.attribute("type").as_string()) == SString("support")) {

		type = EnemyType::SUPPORT;
		hp = 10;
		atk = 5;
		def = 5;

	}
		
	if (SString(parameters.attribute("type").as_string()) == SString("tank")) {

		type = EnemyType::TANK;
		hp = 5;
		atk = 5;
		def = 10;
	}
		
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	texturePathBattle = parameters.attribute("battletexturepath").as_string();

	for (int i = 0; i < 4; i++) {

		idle_right.PushBack({ 32 * (0 + i), 32 * 0, 32, 32 });

	}
	idle_right.loop = true;
	idle_right.speed = 0.06f;
	
	return true;
}

bool Enemy::Start() {

	Restart();
	/*if(){}*/
	return true;
}

bool Enemy::Update()
{
	b2Transform transform = pbody->body->GetTransform();
	b2Vec2 pos = transform.p;

	position.x = METERS_TO_PIXELS(pos.x) - 16;
	position.y = METERS_TO_PIXELS(pos.y) - 18;

	currentAnimation->Update();

	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	if (playerInteraction)
	{
		app->fadeToBlack->Fade((Module*)app->sceneGameplay,	(Module*)app->sceneBattle);
		//app->sceneGameplay->player->Teleport(position.x,position.y + 50);
		playerInteraction = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		Death();
	}
	
	return true;

}

bool Enemy::CleanUp()
{
	
	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {

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
		app->sceneBattle->enemyInCombat = textureBattle;

		break;

	}

}

void Enemy::OnCollisionEnd(PhysBody* physA, PhysBody* physB) {

	playerInteraction = false;

}

void Enemy::Death() 
{
	Disable();
	pbody->body->DestroyFixture(pbody->body->GetFixtureList());
	enemySensor->body->DestroyFixture(enemySensor->body->GetFixtureList());
}

void Enemy::Restart()
{
	texture = app->tex->Load(texturePath);
	textureBattle = app->tex->Load(texturePathBattle);

	int width = 32;
	int height = 32;

	pbody = app->physics->CreateRectangle(position.x, position.y, width, height, bodyType::STATIC);

	enemySensor = app->physics->CreateCircleSensor(position.x, position.y, 25, bodyType::KINEMATIC, ColliderType::ENEMY_SENSOR);

	//pbody->listener = this;

	enemySensor->listener = this;

	currentAnimation = &idle_right;

	playerInteraction = false;
}
