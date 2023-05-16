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
	coin = app->tex->Load("Assets/Textures/Puzzles/Puzzle3_Coin.png");

}

void Puzzle3::Update()
{

	if (createSensorClock) {

		sensor = app->physics->CreateRectangleSensor(posRelojArena.x + 8, posRelojArena.y + 8, 16, 16, bodyType::KINEMATIC, ColliderType::SENSOR_CLOCK_PUZZLE3);
		createSensorClock = false;

	}

	if (!clockPicked) {

		app->render->DrawTexture(relojArena, posRelojArena.x, posRelojArena.y);
		
	}
	else {

		if (!timerStarted) {

			coinTimer.Start();
		
			for (int i = 0; i < 4; i++) {
				
				sensors.push_back(app->physics->CreateRectangleSensor(posRelojArena.x + 100 * (i + 1) + 8, posRelojArena.y + 8, 16, 16, bodyType::KINEMATIC, ColliderType::SENSOR_COIN_PUZZLE3));

			}

			app->physics->DestroyBody(sensor);

			timerStarted = true;

		}

		if (coinTimer.ReadSec() < 2) {

			for (int i = 0; i < 4; i++) {

				app->render->DrawTexture(coin, posRelojArena.x + 100 * (i + 1), posRelojArena.y, &SDL_Rect({ 0,0,16,18 }));

			}

		}
		else {

			clockPicked = false;
			timerStarted = false;

			createSensorClock = true;

			if (coinCount < 4) {

				for (auto& sensor : sensors) {

					app->physics->DestroyBody(sensor);

				}

				sensors.clear();

				coinCount = 0;

			}
			else {

				completed = true;

			}

		}
		
	}

	if (coinPicked) {

		coinCount++;
		coinPicked = false;

	}

}
