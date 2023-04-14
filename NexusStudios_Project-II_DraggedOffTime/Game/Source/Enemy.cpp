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

#include <iostream>

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");

}

Enemy::~Enemy() {

}

bool Enemy::Awake() {

	

	return true;
}

bool Enemy::Start() {



	return true;
}

bool Enemy::Update()
{
	


	return true;
}

bool Enemy::CleanUp()
{

	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {

	

}

void Enemy::OnCollisionEnd(PhysBody* physA, PhysBody* physB) {

	

}

void Enemy::Death() {

	

}