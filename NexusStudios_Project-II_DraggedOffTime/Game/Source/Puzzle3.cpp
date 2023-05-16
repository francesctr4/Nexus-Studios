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
	
	for (int i = 0; i < 6; i++) {

		idleCoin.PushBack({ 16 * (0 + i), 18 * 0, 16, 18 });

	}
	idleCoin.loop = true;
	idleCoin.speed = 0.15f;

	for (int i = 0; i < 4; i++) {

		idleClock.PushBack({ 16 * (0 + i), 18 * 0, 16, 18 });

	}
	idleClock.loop = true;
	idleClock.speed = 0.1f;

	currentAnimationCoin = &idleCoin;
	currentAnimationClock = &idleClock;

	fail = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/Puzzle1_Fail.wav");
	correct = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/Puzzle1_Correct.wav");
	coinFX = app->audio->LoadFx("Assets/Audio/Fx/Coin.wav");
	clockFX = app->audio->LoadFx("Assets/Audio/Fx/Clock.wav");


}

void Puzzle3::Update()
{

	if (!completed) {

		currentAnimationCoin->Update();
		currentAnimationClock->Update();

		if (createSensorClock) {

			sensor = app->physics->CreateRectangleSensor(posRelojArena.x + 8, posRelojArena.y + 8, 16, 16, bodyType::KINEMATIC, ColliderType::SENSOR_CLOCK_PUZZLE3);
			createSensorClock = false;

		}

		if (!clockPicked) {

			SDL_Rect rect = currentAnimationClock->GetCurrentFrame();

			app->render->DrawTexture(relojArena, posRelojArena.x, posRelojArena.y, &rect);

		}
		else {

			if (!timerStarted) {

				coinTimer.Start();

				app->audio->PlayFx(clockFX);

				for (int i = 0; i < 4; i++) {

					sensors.push_back(app->physics->CreateRectangleSensor(posRelojArena.x + 100 * (i + 1) + 8, posRelojArena.y + 8, 16, 16, bodyType::KINEMATIC, ColliderType::SENSOR_COIN_PUZZLE3));

				}

				app->physics->DestroyBody(sensor);

				timerStarted = true;

			}

			if (coinTimer.ReadSec() < 3) {

				SDL_Rect rect = currentAnimationCoin->GetCurrentFrame();

				if (coinCount < 1) app->render->DrawTexture(coin, posRelojArena.x + 100 * (0 + 1), posRelojArena.y, &rect);

				if (coinCount < 2) app->render->DrawTexture(coin, posRelojArena.x + 100 * (1 + 1), posRelojArena.y, &rect);

				if (coinCount < 3) app->render->DrawTexture(coin, posRelojArena.x + 100 * (2 + 1), posRelojArena.y, &rect);

				if (coinCount < 4) app->render->DrawTexture(coin, posRelojArena.x + 100 * (3 + 1), posRelojArena.y, &rect);

				/*if (coinCount == 1) app->physics->DestroyBody(sensors.at(0));

				if (coinCount == 2) app->physics->DestroyBody(sensors.at(1));

				if (coinCount == 3) app->physics->DestroyBody(sensors.at(2));

				if (coinCount == 4) app->physics->DestroyBody(sensors.at(3));*/

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

					app->audio->PlayFx(fail);

				}
				else {

					completed = true;

					for (auto& sensor : sensors) {

						app->physics->DestroyBody(sensor);

					}

					sensors.clear();

					coinCount = 0;

					app->audio->PlayFx(correct);

				}

			}

		}

		if (coinPicked) {

			coinCount++;
			coinPicked = false;

		}

	}

}
