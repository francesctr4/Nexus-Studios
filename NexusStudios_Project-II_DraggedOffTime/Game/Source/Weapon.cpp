#include "Weapon.h"

Weapon::Weapon(int width) {

	this->width = width;

	for (int i = 0; i < 4; i++) {

		idle.PushBack({ width * (0 + i), width * 0, width, width });

	}
	idle.loop = true;
	idle.speed = 0.06f;

	texture = nullptr;
	currentAnimation = nullptr;

	damage = NULL;

}

Weapon::~Weapon() {

}

void Weapon::Load(const char* path) {

	texture = app->tex->Load(path);

	currentAnimation = &idle;

}

void Weapon::Draw(int posX, int posY) {

	currentAnimation->Update();

	SDL_Rect weaponRect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, posX, posY, &weaponRect);

}