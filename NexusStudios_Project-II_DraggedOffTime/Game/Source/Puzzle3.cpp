#include "Puzzle3.h"
#include "Textures.h"
#include "App.h"
#include "Render.h"
#include "Audio.h"

Puzzle3::Puzzle3()
{
}

Puzzle3::~Puzzle3()
{
}

void Puzzle3::Load()
{
	relojArena = app->tex->Load("Assets/Textures/Puzzles/Puzzle3_RelojArena.png");
	sensor = app->physics->CreateRectangleSensor(posRelojArena.x + 8, posRelojArena.y + 8, 16, 16, bodyType::KINEMATIC, ColliderType::SENSOR_CLOCK_PUZZLE3);

}

void Puzzle3::Update()
{
	if (!clockPicked) {

		app->render->DrawTexture(relojArena, posRelojArena.x, posRelojArena.y);
		
	}
	else {

		for (int i = 0; i < 4; i++) {

			app->physics->CreateRectangleSensor(posRelojArena.x + 30 * i, posRelojArena.y + 8, 16, 16, bodyType::KINEMATIC, ColliderType::SENSOR_COIN_PUZZLE3);

		}
		
	}

	if (coinPicked) {

	}

}