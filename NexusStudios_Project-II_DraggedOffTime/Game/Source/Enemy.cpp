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
#include "EntityManager.h"

#include <iostream>

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");

	texture = nullptr;
	texturePath = nullptr;
	textureBattle = nullptr;
	texturePathBattle = nullptr;

	etype = EnemyType::UNKNOWN;

	hp = NULL;
	atk = NULL;
	def = NULL;
	playerInteraction = false;
	pbody = nullptr;
	enemySensor = nullptr;
	currentAnimation = nullptr;
	enemyMap = NULL;
	isAlive = true;

}

Enemy::~Enemy() {

}

bool Enemy::Awake() {

	if (SString(parameters.attribute("type").as_string()) == SString("damage")) {

		etype = EnemyType::DAMAGE;
		hp = 80;
		atk = 20;
		def = 10;

	}

	if (SString(parameters.attribute("type").as_string()) == SString("support")) {

		etype = EnemyType::SUPPORT;
		hp = 80;
		atk = 20;
		def = 10;

	}
		
	if (SString(parameters.attribute("type").as_string()) == SString("tank")) {

		etype = EnemyType::TANK;
		hp = 80;
		atk = 20;
		def = 10;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("bossMedieval")) {

		etype = EnemyType::BOSS_MEDIEVAL;
		hp = 160;
		atk = 40;
		def = 20;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("bossPrehistoric")) {

		etype = EnemyType::BOSS_PREHISTORIC;
		hp = 160;
		atk = 40;
		def = 20;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("bossCyberpunk")) {

		etype = EnemyType::BOSS_CYBERPUNK;
		hp = 160;
		atk = 40;
		def = 20;
	}

	if (SString(parameters.attribute("type").as_string()) == SString("bossApocalypse")) {

		etype = EnemyType::BOSS_APOCALYPSE;
		hp = 160;
		atk = 40;
		def = 20;
	}
		
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	texturePathBattle = parameters.attribute("battletexturepath").as_string();
	enemyMap = parameters.attribute("map").as_int();
	aparicion = enemyMap;

	width = parameters.attribute("w").as_int();
	height = parameters.attribute("h").as_int();

	for (int i = 0; i < 4; i++) {

		idle_right.PushBack({ width * (0 + i), height * 0, width, height });

	}
	idle_right.loop = true;
	idle_right.speed = 0.06f;
	
	return true;
}

bool Enemy::Start() {

	texture = app->tex->Load(texturePath);
	textureBattle = app->tex->Load(texturePathBattle);

	if (etype == EnemyType::BOSS_PREHISTORIC || etype == EnemyType::BOSS_MEDIEVAL || etype == EnemyType::BOSS_CYBERPUNK || etype == EnemyType::BOSS_APOCALYPSE) {

		pbody = app->physics->CreateRectangle(position.x, position.y, widthBoss, heightBoss, bodyType::STATIC);

		enemySensor = app->physics->CreateCircleSensor(position.x, position.y, 40, bodyType::KINEMATIC, ColliderType::ENEMY_SENSOR);

	}
	else {

		pbody = app->physics->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);

		enemySensor = app->physics->CreateCircleSensor(position.x, position.y, 25, bodyType::KINEMATIC, ColliderType::ENEMY_SENSOR);

	}

	//pbody->listener = this;

	enemySensor->listener = this;

	currentAnimation = &idle_right;

	return true;
}

bool Enemy::Update()
{
	b2Transform transform = pbody->body->GetTransform();
	b2Vec2 pos = transform.p;

	if (etype == EnemyType::BOSS_PREHISTORIC || etype == EnemyType::BOSS_MEDIEVAL || etype == EnemyType::BOSS_CYBERPUNK || etype == EnemyType::BOSS_APOCALYPSE) {
	
		position.x = METERS_TO_PIXELS(pos.x) - 32;
		position.y = METERS_TO_PIXELS(pos.y) - 30;

		app->render->DrawTexture(texture, position.x, position.y);
	
	}
	else {

		position.x = METERS_TO_PIXELS(pos.x) - width/2;
		position.y = METERS_TO_PIXELS(pos.y) - height/2 + 2;

		currentAnimation->Update();

		SDL_Rect enemyRect = currentAnimation->GetCurrentFrame();

		app->render->DrawTexture(texture, position.x, position.y, &enemyRect);

	}
	
	if (playerInteraction == true)
	{
		//app->fadeToBlack->Fade((Module*)app->sceneGameplay, (Module*)app->sceneBattle);
		app->fadeToBlack->Fade(reinterpret_cast<Module*>(app->sceneGameplay), reinterpret_cast<Module*>(app->sceneBattle));
		//app->sceneGameplay->player->Teleport(position.x,position.y + 50);
		playerInteraction = false;
		Death();

	}

	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		Death();
	}
	
	
	return true;

}

bool Enemy::CleanUp()
{
	app->physics->DestroyBody(pbody);
	app->physics->DestroyBody(enemySensor);

	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:
		

		break;
	case ColliderType::UNKNOWN:
		

		break;

	case ColliderType::PLAYER:

		playerInteraction = true;
		app->sceneBattle->enemyInCombat = textureBattle;
		app->sceneBattle->widthEnemyCombat = width;
		app->sceneBattle->heightEnemyCombat = height;

		//Pasar variables
		app->sceneBattle->e_HP = this->hp;
		app->sceneBattle->e_max_HP = this->hp;

		app->sceneBattle->e_DMG = this->atk;
		app->sceneBattle->e_base_DMG = this->atk;

		app->sceneBattle->e_DEF = this->def;
		app->sceneBattle->e_base_DEF = this->def;

		break;

	}

}

void Enemy::OnCollisionEnd(PhysBody* physA, PhysBody* physB) {

	playerInteraction = false;

}

void Enemy::Death() 
{
	isAlive = false;
	active = false;
	pbody->body->SetActive(false);
	enemySensor->body->SetActive(false);
}

void Enemy::AddEnemy(Enemy* enemy, EnemyType type, int x, int y)
{
	/*if (enemy != nullptr) enemies.Add(enemy);
	if (type == EnemyType::DAMAGE)
	{
		enemy->type = EnemyType::DAMAGE;
	}
	*/

}

