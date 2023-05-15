#include "Puzzle1.h"
#include "Textures.h"
#include "App.h"
#include "Render.h"
#include "Audio.h"

Puzzle1::Puzzle1()
{
}

Puzzle1::~Puzzle1()
{
}

void Puzzle1::Load()
{
	texture = app->tex->Load("Assets/Textures/Puzzles/Puzzle1_Buttons.png");
	buttonPressed = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/ClickButton_Puzzle1.wav");

	sensor1 = app->physics->CreateRectangleSensor(posButton1.x + 16, posButton1.y + 16, 32, 32, bodyType::KINEMATIC, ColliderType::SENSOR_BUTTON1_PUZZLE1);

	sensor2 = app->physics->CreateRectangleSensor(posButton2.x + 16, posButton2.y + 16, 32, 32, bodyType::KINEMATIC, ColliderType::SENSOR_BUTTON2_PUZZLE1);

	sensor3 = app->physics->CreateRectangleSensor(posButton3.x + 16, posButton3.y + 16, 32, 32, bodyType::KINEMATIC, ColliderType::SENSOR_BUTTON3_PUZZLE1);

	sensor4 = app->physics->CreateRectangleSensor(posButton4.x + 16, posButton4.y + 16, 32, 32, bodyType::KINEMATIC, ColliderType::SENSOR_BUTTON4_PUZZLE1);

	fail = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/Puzzle1_Fail.wav");

	correct = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/Puzzle1_Correct.wav");

}

void Puzzle1::Update()
{

	if (!sensor1Pressed) {
		app->render->DrawTexture(texture, posButton1.x, posButton1.y, &SDL_Rect({ 32 * 0, 32 * 0,32,32 }));
	}
	else {
		app->render->DrawTexture(texture, posButton1.x, posButton1.y, &SDL_Rect({ 32 * 1, 32 * 0,32,32 }));
	}

	if (!sensor2Pressed) {
		app->render->DrawTexture(texture, posButton2.x, posButton2.y, &SDL_Rect({ 32 * 0, 32 * 1,32,32 }));
	}
	else {
		app->render->DrawTexture(texture, posButton2.x, posButton2.y, &SDL_Rect({ 32 * 1, 32 * 1,32,32 }));
	}

	if (!sensor3Pressed) {
		app->render->DrawTexture(texture, posButton3.x, posButton3.y, &SDL_Rect({ 32 * 0, 32 * 2,32,32 }));
	}
	else {
		app->render->DrawTexture(texture, posButton3.x, posButton3.y, &SDL_Rect({ 32 * 1, 32 * 2,32,32 }));
	}

	if (!sensor4Pressed) {
		app->render->DrawTexture(texture, posButton4.x, posButton4.y, &SDL_Rect({ 32 * 0, 32 * 3,32,32 }));
	}
	else {
		app->render->DrawTexture(texture, posButton4.x, posButton4.y, &SDL_Rect({ 32 * 1, 32 * 3,32,32 }));
	}

	if (sensor1Pressed && sensor2Pressed && sensor3Pressed && sensor4Pressed && !everySensorPressed) {

		combination = std::to_string(order.at(0)) + std::to_string(order.at(1)) + std::to_string(order.at(2)) + std::to_string(order.at(3));

		if (combination == "1234" && !completed) {

			app->audio->PlayFx(correct);
			completed = true;

		}
		else {

			failTimer.Start();
			failed = true;

		}

		everySensorPressed = true;

	}

	if (everySensorPressed && failTimer.ReadSec() < 2 && failed) {

		app->render->DrawTexture(texture, posButton1.x, posButton1.y, &SDL_Rect({ 32 * 2, 32 * 0,32,32 }));
		app->render->DrawTexture(texture, posButton2.x, posButton2.y, &SDL_Rect({ 32 * 2, 32 * 1,32,32 }));
		app->render->DrawTexture(texture, posButton3.x, posButton3.y, &SDL_Rect({ 32 * 2, 32 * 2,32,32 }));
		app->render->DrawTexture(texture, posButton4.x, posButton4.y, &SDL_Rect({ 32 * 2, 32 * 3,32,32 }));

		if (!failedFX) {

			app->audio->PlayFx(fail);

			failedFX = true;

		}
		
	}
	else if (everySensorPressed && failTimer.ReadSec() >= 2 && failed) {

		everySensorPressed = false;
		sensor1Pressed = false;
		sensor2Pressed = false;
		sensor3Pressed = false;
		sensor4Pressed = false;
		failedFX = false;
		failed = false;
		order.clear();

	}
	else if (everySensorPressed && completed && !failed) {

		app->render->DrawTexture(texture, posButton1.x, posButton1.y, &SDL_Rect({ 32 * 3, 32 * 0,32,32 }));
		app->render->DrawTexture(texture, posButton2.x, posButton2.y, &SDL_Rect({ 32 * 3, 32 * 1,32,32 }));
		app->render->DrawTexture(texture, posButton3.x, posButton3.y, &SDL_Rect({ 32 * 3, 32 * 2,32,32 }));
		app->render->DrawTexture(texture, posButton4.x, posButton4.y, &SDL_Rect({ 32 * 3, 32 * 3,32,32 }));

	}

}